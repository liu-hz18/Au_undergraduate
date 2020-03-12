package date;

public class Test {
	public static void main(String[] args) {
		Date date0 = new Date("Jan. 14, 2014");
		System.out.println( date0.print().equals("2014/1/14") ? "Correct!" : "Wrong!" );
		
		Date date1 = new Date("Oct.", 20, 2017);
		System.out.println( date1.print().equals("2017/10/20") ? "Correct!" : "Wrong!" );
		
		Date date2 = new Date(2018, 3, 31);
		System.out.println( date2.print().equals("2018/3/31") ? "Correct!" : "Wrong!" );
	}
}
