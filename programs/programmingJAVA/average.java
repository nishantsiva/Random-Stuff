public class average{
	public static void main(String[] args){
		int[] numbers = {21,34,21,54,46};
		System.out.println("Average = " + computeAvg(numbers,5));
	}
	
	public static float computeAvg(int[] nos, int count){
		int i,total = 0;
		for(i=0; i<count; i++)
			total += nos[i];
		return total/count;
	}
}
