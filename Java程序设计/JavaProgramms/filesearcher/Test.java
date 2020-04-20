package filesearcher;

public class Test {
	public static void main(String[] args) {
		FileSearcher fileSearcher = new FileSearcher("dialog.txt");
		System.out.println( fileSearcher.search("we") == 35 ? "Correct!" : "Wrong!" );
		System.out.println( fileSearcher.search("have") == 92 ? "Correct!" : "Wrong!" );
		System.out.println( fileSearcher.search("the") == 141 ? "Correct!" : "Wrong!" );
		System.out.println( fileSearcher.search("google") == 0 ? "Correct!" : "Wrong!" );
	}
}
