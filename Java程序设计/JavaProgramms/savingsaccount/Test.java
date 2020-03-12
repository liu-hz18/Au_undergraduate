package savingsaccount;

public class Test {
	public static void main(String[] args) {
		SavingsAccount saver0 = new SavingsAccount(2000);
		SavingsAccount saver1 = new SavingsAccount(3000);
		System.out.println( saver0.calculateMonthlyInterest() == 10 ? "Correct!" : "Wrong!" );
		System.out.println( saver1.calculateMonthlyInterest() == 15 ? "Correct!" : "Wrong!" );
		
		SavingsAccount.annualInterestRate = 0.04;
		System.out.println( saver0.calculateMonthlyInterest() == 6.7 ? "Correct!" : "Wrong!" );
		
		SavingsAccount saver2 = new SavingsAccount(5400);
		System.out.println( saver2.calculateMonthlyInterest() == 18 ? "Correct!" : "Wrong!" );
		System.out.println( saver2.calculateMonthlyInterest() == 18.06 ? "Correct!" : "Wrong!" );
	}
}
