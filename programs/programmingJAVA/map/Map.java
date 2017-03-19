import java.util.List;
import java.util.ArrayList;

public class Map{
	public static void main(String[] args){
		List<Integer> a = new ArrayList<Integer>();
		a.add(1);
		a.add(2);
		a.add(3);
		map(new Function(){
				public int f(int n){
					System.out.println(n + " ");
					return 0;
				}
			},
			map(new Function(){
					public int f(int n){
						return n*n;
					}
				},
				a
			)
		);
	}
	
	private static List<Integer> map(Function F, List<Integer> arr){
		List<Integer> res = new ArrayList<Integer>();
		for(int i = 0; i<arr.size(); i++)
			res.add(F.f(arr.get(i)));
		return res;
	}
}

interface Function{
	public int f(int n);
}
		
