public abstract class Person{
	protected String name;
	public abstract String work();
	public final void printDetails(){
		System.out.println(name + " " + work());
	}
}
