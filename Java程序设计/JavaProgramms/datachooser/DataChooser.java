package datachooser;
import java.util.Vector;
import java.io.File;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;

public class DataChooser{
    public DataChooser(String filein, String fileout){
        Vector<String> outData = new Vector<String>();
        //read data
        try{
            File afile = new File(filein);
            Scanner reader = new Scanner(afile);
            while(reader.hasNextLine()){
                String data = reader.nextLine();
                String[] items = data.split(",");
                outData.add(items[3]);
            }
            reader.close();
        } catch (FileNotFoundException e){
            System.out.println("File not found!");
            e.printStackTrace();
        }
        //write data
        try{
            FileWriter writer = new FileWriter(fileout);
            for(String str: outData){
                writer.write(str + "\r\n");
            }
            writer.close();
        } catch (IOException e) {
            System.out.println("Write File Error!");
            e.printStackTrace();
        }
    }
}
