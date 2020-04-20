package datachooser;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class Test {
	public static void main(String[] args) {
		DataChooser dataChooser = new DataChooser("data.csv", "department.csv");
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("department.csv")));
			for (int i = 0; i < 5; i++) {
				String s = reader.readLine();
				switch (i) {
				case 0:
					System.out.println( s.equals("Department") ? "1 Correct!" : "Wrong!" );
					break;
				case 1:
					System.out.println( s.equals("Computer Science") ? "2 Correct!" : "Wrong!" );
					break;
				case 2:
					System.out.println( s.equals("Electronic Engineering") ? "3 Correct!" : "Wrong!" );
					break;
				case 3:
					System.out.println( s.equals("Software Engineering") ? "4 Correct!" : "Wrong!" );
					break;
				case 4:
					System.out.println( s.equals("Computer Science") ? "5 Correct!" : "Wrong!" );
					break;
				}
			}
			reader.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}
