import java.util.Scanner;

public class Main{
	public static void main(String[] args){
		System.out.print("Input: ");
		Scanner in = new Scanner(System.in);
		int num = in.nextInt();
		int[][] Array = new int[num][num];
		int row = 0;
		int col = num/2;
		System.out.println("Output: ");
		for(int i = 0; i < num; i++){
			for(int j = 0; j < num; j++)
				Array[i][j] = 0;
		}
		for(int i = 1; i <= num*num; i++){
			Array[row][col] = i;
			row--;col++;
			if(row<0&&col>=num){
				row+=2;
				col--;
			}
			else if(row<0)
				row = num - 1;
			else if(col>=num)
				col = 0;
			else if(Array[row][col] != 0){
				row +=2;
				col--;
			}
		}
		//System.out.print("Sum of each row, column or diagonal : ");
		int Sum = 0;
		for(int i = 0; i < num; i++)
			Sum += Array[0][i];
		System.out.println(Sum);
		for(int i = 0; i < num; i++){
			for(int j = 0; j < num; j++)
				System.out.print(Array[i][j] + "\t");
			System.out.print("\n");
		}
	}
}
				
