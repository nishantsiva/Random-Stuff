public class person{
	private String name;
	private String lastName;
	private int age;
	private String gender;
	
	public person(String _name, String _lastName,int _age){
		name = _name;
		lastName = _lastName;
		setAge(_age);
	}
	public person(String _name, String _lastName){
		name = _name;
		lastName = _lastName;
		setAge(21);
	}
	
	public void setAge(int _age){
		if( _age>0 && _age<1000)
			age = _age;
	}
	
	int getAge(){
		return age;
	}
	
	public String getFullName(){
		return name + lastName;
	}
	
	public boolean sameFamily(person p){
		if(p.lastName.equals(lastName))
			return true;
		return false;
	}
}
