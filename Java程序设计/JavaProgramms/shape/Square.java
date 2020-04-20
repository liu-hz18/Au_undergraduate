package shape;

public class Square extends Rectangle{
    public Square(){}
    public Square(double l){
        super(l, l);
    }
    public Square(double l, String _color){
        super(l, l, _color);
    }
    public double getSide(){
        return super.getWidth();
    }
    public void setSide(double l){
        super.setWidth(l);
        super.setHeight(l);
    }
    public String toString(){
        return "Square (" + this.getColor() + ")";
    }
}
