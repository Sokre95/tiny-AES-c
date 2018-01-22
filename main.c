#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "aes.h"

#define KEY_LEN	16


typedef struct {
	int decryption_requested;
	char *input_filename;
	char *output_filename;
	char *key;
	char *iv;
}paramst_t;

int main(int argc, char const *argv[])
{
	paramst_t* params;
	params = (paramst_t*)malloc(sizeof(paramst_t));

	params->input_filename = (char*)argv[argc - 2];
	params->output_filename = (char*)argv[argc - 1];
	params->key = "ABCDabcdABCD1234";
	params->iv = "0123456789abcdef";

	params->decryption_requested = atoi(argv[1]);

	uint8_t *buff;
	uint8_t *out_data;
	uint8_t i;

	FILE *in_f = NULL, *out_f = NULL,*out_f2;

	in_f = fopen(params->input_filename, "rb");
	if(in_f == NULL){
		fprintf(stderr, "Neuspjelo otvaranje file-a\n");
		exit(1);
	}

	out_f = fopen(params->output_filename, "wb");
	if(out_f == NULL){
		fprintf(stderr, "Neuspjelo otvaranje file-a\n");
		exit(1);
	}
	out_f2 = fopen("test.out", "wb");
	if(out_f2 == NULL){
		fprintf(stderr, "Neuspjelo otvaranje file-a\n");
		exit(1);
	}

	fseek(in_f, 0, SEEK_END);
	int f_size = ftell(in_f);
	fseek(in_f, 0, SEEK_SET);
	printf("File size: %d\n", f_size);
	int aligned_f_size = (f_size % KEY_LEN) != 0 ? f_size + KEY_LEN - f_size % KEY_LEN : f_size + KEY_LEN;

	buff = malloc(aligned_f_size);
	f_size = fread(buff, 1, aligned_f_size, in_f);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, params->key, params->iv);

	memset(buff + f_size, (uint8_t*)(aligned_f_size - f_size), aligned_f_size - f_size);

	fwrite(buff, aligned_f_size, 1, out_f2);

	printf("Padded size: %d\n", aligned_f_size -f_size);

	if(params->decryption_requested){
		fprintf(stderr, "Dekriptiranje...\n");
		AES_CBC_encrypt_buffer(&ctx, buff, aligned_f_size);
	} else {
		fprintf(stderr, "Kriptiranje...\n");
		AES_CBC_decrypt_buffer(&ctx, buff, aligned_f_size);
	}
	fprintf(stderr, "Gotovo.\n");
	fwrite(buff, aligned_f_size, 1, out_f);

	return 0;
}