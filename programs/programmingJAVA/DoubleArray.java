public class DoubleArray{
	public static void main(String[] args){
		int[] array = {1,2,3,4,5,6},dArray;
		dArray = computeDouble(array);
		for(int i = 0; i<dArray.length; i++)
			System.out.println(dArray[i]);
	}
	public static int[] computeDouble(int[] array){
		int[] dArray = new int[array.length];
		for(int i = 0; i<array.length;i++)
			dArray[i] = 2*array[i];
		return dArray;
	}
} 
