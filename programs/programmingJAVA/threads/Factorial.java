class Factorial implements Runnable{
	public int number,result;
	
	public Factorial(int _number){
		number = _number;
	}
		
	public int getResult(){
		return result;
	}
	
	public int factorial(int n){
		if(n<=1)
			return 1;
		//System.out.println("HI");
		return n*factorial(n-1);
	}
	
	public void run(){
		result = factorial(number);
		System.out.println("Factorial of " + number + " is: " + result);
	}
}
