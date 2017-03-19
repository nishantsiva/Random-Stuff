class Program{
	public static void main(String[] args){
		for(int i = 5; i >= 0; i--){
			Factorial f = new Factorial(i);
			Thread t = new Thread(f);
			t.start();
		}
	}
}
