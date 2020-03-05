package complex;

public class Test {
	public static void main(String[] args) {
		Complex c = new Complex(1, 1);
		c.print();
		System.out.println("You should print: 1.0+1.0i\n");
		
		c.add(new Complex(2, 3));
		c.print();
		System.out.println(c.realPart == 3 && c.imaginaryPart == 4 ? "Correct!" : "Wrong!");
		System.out.println("");
		
		c.sub(new Complex(4, 0.5));
		c.print();
		System.out.println(c.realPart == -1 && c.imaginaryPart == 3.5 ? "Correct!" : "Wrong!");
		
	}
}
