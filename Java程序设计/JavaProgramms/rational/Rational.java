package rational;

public class Rational{
    int numerator, denominator;
    private static int gcd(int a, int b){//O(logn)
        while(b != 0){
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
    private void reduction(){
        int g = gcd(this.numerator, this.denominator);
        this.numerator /= g;
        this.denominator /= g;
        if(this.denominator < 0 && this.numerator > 0){
            this.numerator = -this.numerator;
            this.denominator = -this.denominator;
        }
    }
    public Rational(int n, int d){
        this.numerator = n;
        this.denominator = d;
        reduction();
    }
    public void add(Rational r){
        this.numerator = this.numerator * r.denominator + this.denominator * r.numerator;
        this.denominator = this.denominator * r.denominator;
        reduction();
    }
    public void sub(Rational r){
        this.numerator = this.numerator * r.denominator - this.denominator * r.numerator;
        this.denominator = this.denominator * r.denominator;
        reduction();
    }
    public void mul(Rational r){
        this.numerator *= r.numerator;
        this.denominator *= r.denominator;
        reduction();
    }
    public void div(Rational r){
        this.numerator *= r.denominator;
        this.denominator *= r.numerator;
        reduction();
    }
    public void printRational(){
        if (this.denominator == 1) {
            System.out.println(this.numerator);
        } else {
            System.out.println(this.numerator + "/" + this.denominator);
        }
    }
    public void printReal(){
        double r = (double)this.numerator / (double)this.denominator;
        System.out.println(r);
    }
}
