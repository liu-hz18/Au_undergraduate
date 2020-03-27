package exceptiontest;

public class ExceptionTest{
    public int getFirstValidInt(){
        int result;
        while (true) {
            try{
                result = Test.readInt();
                break;
            } catch (NumberFormatException e){
                continue;
            }
        }
        return result;
    }
    public double getX(double y) throws XLessThanZeroException, 
                                        XGreaterThanOneException{
        double x;
        x = Math.log(y);
        if(x < 0.0){
            throw new XLessThanZeroException(y);
        }
        if(x > 1.0){
            throw new XGreaterThanOneException(y);
        }
        return x;
    }
    public double solve(double y){
        double result;
        try{
            result = Test.solve2(y);
        } catch (XLessThanZeroException e) {
            return -1;
        } catch (XGreaterThanOneException e) {
            return -2;
        }
        return result;
    }
}