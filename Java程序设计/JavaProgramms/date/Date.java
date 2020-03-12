package date;
import java.util.HashMap;
import java.util.Map;

public class Date{
    int year, month, day;
    private static Map<String, Integer> monthmap = new HashMap<>();
    static{
        monthmap.put("Jan.", 1);
        monthmap.put("Feb.", 2);
        monthmap.put("Mar.", 3);
        monthmap.put("Apr.", 4);
        monthmap.put("May.", 5);
        monthmap.put("Jun.", 6);
        monthmap.put("Jul.", 7);
        monthmap.put("Aug.", 8);
        monthmap.put("Sept.", 9);
        monthmap.put("Oct.", 10);
        monthmap.put("Nov.", 11);
        monthmap.put("Dec.", 12);
    }
    public Date(String d){
        String[] strbuf = d.split(" ");
        this.month = monthmap.get(strbuf[0]);
        this.day = Integer.parseInt(strbuf[1].substring(0, strbuf[1].length() - 1));
        this.year = Integer.parseInt(strbuf[2]);
    }
    public Date(String m, int d, int y){
        this.year = y;
        this.month = monthmap.get(m);
        this.day = d;
    }
    public Date(int y, int m, int d){
        this.year = y;
        this.month = m;
        this.day = d;
    }
    public String print(){
        return year + "/" + month + "/" + day;
    }
}