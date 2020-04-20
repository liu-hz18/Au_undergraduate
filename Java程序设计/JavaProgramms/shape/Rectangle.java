package shape;

public class Rectangle extends Shape{
    double width, length;
    public Rectangle(){
        width = length = 0.0;
    }
    public Rectangle(double w, double l){
        this.width = w;
        this.length = l; 
    }
    public Rectangle(double w, double l, String _color){
        super(_color);
        this.width = w;
        this.length = l;
    }
    public double getWidth(){
        return this.width;
    }
    public void setWidth(double w){
        this.width = w;
    }
    public double getHeight(){
        return this.length;
    }
    public void setHeight(double l){
        this.length = l;
    }
    public double getArea(){
        return this.width * this.length;
    }
    public double getPerimeter(){
        return 2.0 * (this.width + this.length);
    }
    public String toString(){
        return "Rectangle (" + this.getColor() + ")";
    }
}