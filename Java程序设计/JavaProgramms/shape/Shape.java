package shape;

public abstract class Shape{
    String color;
    boolean isfilled;
    public Shape(){
        this.color = "#";
        this.isfilled = false;
    }
    public Shape(String _color){
        this.color = _color;
        this.isfilled = true;
    }
    public String getColor(){
        return this.color;
    }
    public void setColor(String _color){
        this.color = _color;
        this.isfilled = true;
    }
    public boolean isFilled(){
        return this.isfilled;
    }
    public abstract double getArea();
    public abstract double getPerimeter();
    public abstract String toString();
}