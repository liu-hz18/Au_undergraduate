package complex;

public class Complex{
    double realPart, imaginaryPart;
    public Complex(){
        this.realPart = 0;
        this.imaginaryPart = 0;
    }
    public Complex(double a, double b){
        this.realPart = a;
        this.imaginaryPart = b;
    }
    public double length(){
        return Math.sqrt(this.realPart*this.realPart + this.imaginaryPart*this.imaginaryPart);
    }
    public void add(Complex c){
        this.realPart += c.realPart;
        this.imaginaryPart += c.imaginaryPart;
    }
    public void sub(Complex c){
        this.realPart -= c.realPart;
        this.imaginaryPart -= c.imaginaryPart;
    }
    public void mul(Complex c){
        double temp = this.realPart;
        this.realPart = temp * c.realPart - this.imaginaryPart * c.imaginaryPart;
        this.imaginaryPart = temp * c.imaginaryPart + this.imaginaryPart * c.realPart;
    }
    public void div(Complex c){
        double denominator = c.realPart * c.realPart + c.imaginaryPart * c.imaginaryPart;
        double temp = this.realPart;
        this.realPart = (temp * c.realPart + this.imaginaryPart * c.imaginaryPart) / denominator;
        this.imaginaryPart = (this.imaginaryPart * c.realPart - temp * c.imaginaryPart) / denominator;
    }
    public void print(){
        System.out.println(this.realPart + "+" + this.imaginaryPart + "i");
    }
}