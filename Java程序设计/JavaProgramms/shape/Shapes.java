package shape;

public class Shapes{
    Shape[] shapeCollection;
    public Shapes(Shape[] shapearr){
        this.shapeCollection = shapearr;
    }
    public double getArea(){
        double res = 0.0;
        for(Shape s: this.shapeCollection){
            res += s.getArea();
        }
        return res;
    }
    public double getFilledArea(){
        double res = 0.0;
        for(Shape s: this.shapeCollection){
            if(s.isFilled()){
                res += s.getArea();
            }
        }
        return res;
    }
    public String toString(){
        return java.util.Arrays.toString(this.shapeCollection);
    }
}
