public class Program{
	public static void main(String[] args){
		person p1 = new person("k","s",25);
		person p2 = new person("a","s");
		person p3 = new person("k","t",-13);
		System.out.println("p1 age : " + p1.getAge());
		System.out.println("p2 age : " + p2.getAge());
		System.out.println("p3 age : " + p3.getAge());
		if(p1.sameFamily(p2))
			System.out.println("p1 p2 same ");
		else
			System.out.println("p1 p2 not same ");
	}
}
