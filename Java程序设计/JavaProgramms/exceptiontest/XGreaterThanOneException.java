package exceptiontest;

public class XGreaterThanOneException extends Exception{
    double y;
    public XGreaterThanOneException(double _y){
        this.y = _y;
    }
    public String getInfo(){
        return "Too large";
    }
}