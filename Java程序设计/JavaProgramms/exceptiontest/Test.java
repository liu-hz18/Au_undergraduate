package exceptiontest;
import java.util.Random;

public class Test {
	private static Random random;
	private static int validInt = -1;
	
	private static ExceptionTest et;
	private static int cnt = 0;
	
	public static void main(String[] args) {
		random = new Random(12345);
		
		et = new ExceptionTest();
		int ans0 = et.getFirstValidInt();
		System.out.println( (ans0 == validInt) ? (++cnt) + " Correct!" : (++cnt) + " Wrong!");
		
		double ans1 = et.solve(2);
		System.out.println( Math.abs(ans1 - 0.6931471805599453) < 1e-5 ? (cnt) + " Correct!" : (cnt) + " Wrong! Incorrect answer!" );
		
		double ans2 = et.solve(0.5);
		System.out.println( (ans2 == -1) ? (cnt) + " Correct!" : (cnt) + " Wrong! Incorrect answer!" );
		
		double ans3 = et.solve(3);
		System.out.println( (ans3 == -2) ? (cnt) + " Correct!" : (cnt) + " Wrong! Incorrect answer!" );
	}
	
	public static String getRandomString() {
		int now = random.nextInt(10);
		switch (now) {
		case 0:
			validInt = random.nextInt();
			return "" + validInt;
		case 1:
			return "" + random.nextFloat();
		case 2:
			return "" + random.nextDouble();
		case 3:
			return "" + random.nextGaussian();
		case 4: case 5:
			return "" + random.nextBoolean();
		case 6:
			return "" + random.nextLong();
		case 7: case 8: case 9:
			byte[] bytes = new byte[10];
			random.nextBytes(bytes);
			return bytes.toString();
		}
		return "xxx";
	}
	
	public static int readInt() {
		return Integer.parseInt(getRandomString());
	}
	
	public static double solve2(double y) throws XLessThanZeroException, XGreaterThanOneException {
		double x = -1;
		try {
			x = et.getX(y);
			System.out.println((++cnt) + " Correct!");
		} catch (XLessThanZeroException e) {
			System.out.println( (e.getInfo().equals(y + " is too small")) ? (++cnt) + " Correct!" : (++cnt) + " Wrong! Incorrect exception info!");
			throw e;
		} catch (XGreaterThanOneException e) {
			System.out.println( (e.getInfo().equals("Too large")) ? (++cnt) + " Correct!" : (++cnt) + " Wrong! Incorrect exception info!" );
			throw e;
		} catch (Exception e) {
			System.out.println( (++cnt) + " Wrong! No that exception!" );
		}
		return x;
	}
}
