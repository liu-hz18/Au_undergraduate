package aplusb;

public class Test {
	public static void main(String[] args) {
		APlusB aPlusB = new APlusB();
		
		int c = aPlusB.plus(1, 2);
		if (c == 3) {
			System.out.println("Correct! 1+2=3");
		} else {
			System.out.println("Wrong! 1+2¡Ù" + c);
		}
		
		int d = aPlusB.plus(5, 11);
		if (d == 16) {
			System.out.println("Correct! 5+11=16");
		} else {
			System.out.println("Wrong! 5+11¡Ù" + d);
		}
	}
}
