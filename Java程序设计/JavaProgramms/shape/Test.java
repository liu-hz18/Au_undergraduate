package shape;

public class Test {
	public static void main(String[] args) {
		Rectangle r0 = new Rectangle();
		r0.setWidth(1);
		r0.setHeight(2);
		judge(r0.getArea() == 2);							// 1
		judge(r0.getPerimeter() == 6);						// 2
		judge(r0.isFilled() == false);						// 3
		
		Rectangle r1 = new Rectangle(3, 1);
		judge(r1.getArea() == 3);							// 4
		judge(r1.getPerimeter() == 8);						// 5
		
		Rectangle r2 = new Rectangle(2, 4, "Red");
		judge(r2.getArea() == 8);							// 6
		judge(r2.getPerimeter() == 12);						// 7
		judge(r2.isFilled() == true);						// 8
		judge(r2.getColor() == "Red");						// 9
		judge(r2.toString().equals("Rectangle (Red)"));		// 10
		
		Circle c0 = new Circle(1);
		judge(c0.getArea() == Math.PI);						// 11
		judge(c0.getPerimeter() == Math.PI * 2);			// 12
		c0.setRadius(2);
		judge(c0.getArea() == c0.getPerimeter());			// 13
		judge(c0.isFilled() == false);						// 14
		judge(c0.toString().equals("Circle (#)"));			// 15
		c0.setColor("Blue");
		judge(c0.toString().equals("Circle (Blue)"));		// 16
		
		Circle c1 = new Circle();
		judge(c1.isFilled() == false);						// 17
		c1.setRadius(0.5);
		
		Circle c2 = new Circle(3, "Green");
		judge(c2.getColor() == "Green");					// 18
		
		Square s0 = new Square();
		s0.setSide(1);
		judge(s0.getArea() == 1);							// 19
		judge(s0.getPerimeter() == 4);						// 20
		judge(s0.isFilled() == false); 						// 21
		s0.setColor("Yellow");
		s0.setSide(1.5);
		judge(s0.getPerimeter() == 6);						// 22
		judge(s0.toString().equals("Square (Yellow)"));		// 23
		judge(s0.getWidth() == 1.5);						// 24
		
		Shape[] shapeList = new Shape[] { r0, r1, r2, c0, c1, c2, s0 };
		Shapes shapes = new Shapes(shapeList);
		judge(Math.abs(shapes.getArea() - 56.87610266006476) < 1e-5);			// 25
		judge(Math.abs(shapes.getFilledArea() - 51.090704496667314) < 1e-5);	// 26
		String s = "[Rectangle (#), Rectangle (#), Rectangle (Red), Circle (Blue), Circle (#), Circle (Green), Square (Yellow)]";
        judge(shapes.toString().equals(s));										// 27
	}
	
	static int counter = 0;
	static void judge(boolean answer) {
		counter++;
		System.out.println( answer ? counter + " Correct!" : counter + " Wrong!");
	}
}
