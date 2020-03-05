package hugeinteger;

public class Test {
	public static void main(String[] args) {
		HugeInteger h = new HugeInteger("0");
		h.output();
		System.out.println("You should print 0.");
		h.input("12345");
		h.output();
		System.out.println("You should print 12345.");
		System.out.println("");
		
		h.add(new HugeInteger("10988"));
		h.output();
		System.out.println("You should print 23333.");
		System.out.println("");

		h.input("12345");
		System.out.println((h.isEqualTo(new HugeInteger("12345")) ? "Correct!" : "Wrong!") + " h = 12345");
		System.out.println((h.isNotEqualTo(new HugeInteger("54321")) ? "Correct!" : "Wrong!") + " h != 54321");
		System.out.println((h.isGreaterThan(new HugeInteger("12305")) ? "Correct!" : "Wrong!") + " h > 12305");
		System.out.println((h.isGreaterThan(new HugeInteger("12348")) ? "Wrong!" : "Correct!") + " h < 12348");
		System.out.println((h.isGreaterThan(new HugeInteger("12345")) ? "Wrong!" : "Correct!") + " h = 12345");
		System.out.println((h.isGreaterThanOrEqualTo(new HugeInteger("12345")) ? "Correct!" : "Wrong!") + " h >= 12345");
		System.out.println((h.isLessThan(new HugeInteger("19988")) ? "Correct!" : "Wrong!") + " h < 19988");
		System.out.println((h.isLessThan(new HugeInteger("9887")) ? "Wrong!" : "Correct!") + " h > 9887");
		System.out.println((h.isLessThan(new HugeInteger("12345")) ? "Wrong!" : "Correct!") + " h = 12345");
		System.out.println((h.isLessThanOrEqualTo(new HugeInteger("100000")) ? "Correct!" : "Wrong!") + " h <= 100000");
	}
}
