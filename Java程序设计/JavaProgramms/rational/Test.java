package rational;

public class Test {
	public static void main(String[] args) {
		Rational r = new Rational(2, 4);
		r.printRational();
		System.out.println(r.numerator == 1 && r.denominator == 2 ? "Correct! You should print 1/2." : "Wrong! You didn't reduce.");
		System.out.println("");
		
		r.add(new Rational(2, 3));
		r.printRational();
		System.out.println(r.numerator == 7 && r.denominator == 6 ? "Correct!" : "Wrong!");
		System.out.println("");

		r.sub(new Rational(3, 4));
		r.printRational();
		System.out.println(r.numerator == 5 && r.denominator == 12 ? "Correct!" : "Wrong!");
		System.out.println("");
		
		r.mul(new Rational(6, 7));
		r.printRational();
		System.out.println(r.numerator == 5 && r.denominator == 14 ? "Correct!" : "Wrong!");
		System.out.println("");
		
		r.div(new Rational(5, 21));
		r.printRational();
		System.out.println(r.numerator == 3 && r.denominator == 2 ? "Correct!" : "Wrong!");
		System.out.println("");
		
		r.printReal();
		System.out.println("You should print 1.5");
		r.add(new Rational(1, 2));
		r.printRational();
		System.out.println("You should print 2");
	}
}
