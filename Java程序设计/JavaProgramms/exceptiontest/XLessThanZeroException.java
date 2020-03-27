package exceptiontest;

public class XLessThanZeroException extends Exception{
    double y;
    public XLessThanZeroException(double _y){
        this.y = _y;
    }
    public String getInfo(){
        return y + " is too small";
    }
}
