public class Program{
	public static void main(String[] args){
		Person[] p = {
			new Student("Arun"),
			new Teacher("KC"),
			//new Person()
		};
		for(Person varr : p){
			varr.printDetails();
		}
	}
}
