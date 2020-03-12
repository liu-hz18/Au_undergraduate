package savingsaccount;

public class SavingsAccount{
    static double annualInterestRate = 0.06;
    private double savingsBalance;
    public SavingsAccount(double money){
        savingsBalance = money;
    }
    public double calculateMonthlyInterest(){
        double interest = savingsBalance * annualInterestRate / 12.0;
        savingsBalance += interest;
        return interest;
    }
    public void modifyInterestRate(double rate){
        annualInterestRate = rate;
    }
}