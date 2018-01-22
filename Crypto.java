import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.spec.IvParameterSpec;
import java.util.Base64;
import java.util.Base64.Decoder;
import java.io.IOException;
import java.lang.ProcessBuilder;

public class Crypto {

   static void fileProcessor(int cipherMode,String key,String initVector,File inputFile,File outputFile){
     try {
           SecretKeySpec skeySpec = new SecretKeySpec(key.getBytes("UTF-8"), "AES");
           IvParameterSpec iv = new IvParameterSpec(initVector.getBytes("UTF-8"));
           Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
           //Cipher cipher = Cipher.getInstance("AES/CBC/NoPadding");
           cipher.init(cipherMode, skeySpec, iv);

           FileInputStream inputStream = new FileInputStream(inputFile);
           byte[] inputBytes = new byte[(int) inputFile.length()];
           inputStream.read(inputBytes);
           System.out.println("Size: " + inputFile.length());
           byte[] outputBytes = cipher.doFinal(inputBytes);

           FileOutputStream outputStream = new FileOutputStream(outputFile);
           outputStream.write(outputBytes);

           inputStream.close();
           outputStream.close();

        } catch (Exception e) {
        e.printStackTrace();
            }
     }
    
     public static void main(String[] args) {
    String key = "ABCDabcdABCD1234";
    String iv = "0123456789abcdef";
    File encryptedFile = new File("sj.out");
    File decryptedFile = new File("sjd.jpg");

    

    try {
        //ProcessBuilder p = new ProcessBuilder();
        //System.out.println("Started EXE");
        //p.command("/home/coki/Desktop/tiny-AES-c/a.out", "1" ,"sj.out", "sjd.jpg");   
        //p.start();
        //p.waitFor();https://stackoverflow.com/questions/29746304/processbuilder-and-process-waitfor-how-long-does-ist-wait
        Crypto.fileProcessor(Cipher.DECRYPT_MODE,key,iv,encryptedFile,decryptedFile);
        System.out.println("Sucess");
     } catch (Exception ex) {
         System.out.println(ex.getMessage());
             ex.printStackTrace();
     }
     }
    
}