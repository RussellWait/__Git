package SGG;

public class Person
{
	public static void main(String arg[])
	{
		System.out.println("Launch...");
		
		Person p1 = new Person();
		p1.info();
		
		Person p2 = p1;
		p2.setName("heh");
		p1.info();
		p2.info();
	}
	
	String _name;
	int _age;
	boolean _sex;
	
	public void eat()
	{
		System.out.println("I'm eating");
	}
	
	public void sleep()
	{
		System.out.println("I'm Sleeping");
	}
	
	public void info()
	{
		System.out.println("name:" + _name +", sex:" + _sex + ", age:" + _age);
	}
	
	public String getName()
	{
		return _name;
	}
	
	public void setName(String name)
	{
		_name = name;
	}
	
	public int getAge()
	{
		return _age;
	}
	
	public void setAge(int age)
	{
		_age = age;
	}
	
	public boolean getSex()
	{
		return _sex;
	}
	
	public void setSex(boolean sex)
	{
		_sex = sex;
	}
}
