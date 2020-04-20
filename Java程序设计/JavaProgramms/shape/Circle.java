package shape;

public class Circle extends Shape{
    double radius;
    public Circle(){
        radius = 0.0;
    }
    public Circle(double r){
        this.radius = r;
    }
    public Circle(double r, String _color){
        super(_color);
        this.radius = r;
    }
    public double getRadius(){
        return this.radius;
    }
    public void setRadius(double r){
        this.radius = r;
    }
    public double getArea(){
        return Math.PI * this.radius * this.radius;
    }
    public double getPerimeter(){
        return 2.0 * Math.PI * this.radius;
    }
    public String toString(){
        return "Circle (" + this.getColor() + ")";
    }
}