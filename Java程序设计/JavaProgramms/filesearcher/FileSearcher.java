package filesearcher;
import java.util.Vector;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileSearcher{
    FileReader reader = null;
    BufferedReader bufferReader = null;
    String[] words;
    public FileSearcher(String filein){
        try{
            reader = new FileReader(filein);
            bufferReader = new BufferedReader(reader);
            String file = "", temp;
            while((temp = bufferReader.readLine()) != null){
                file += temp + " ";
            }
            words = file.toLowerCase().split("[^a-zA-Z]");
            reader.close();
        } catch (IOException e){
            System.out.println(e.toString());
        }
    }
    public int search(String str){
        int count = 0;
        for(String word: words){
            if(str.equals(word)){
                count++;
            }
        }
        return count;
    }
}