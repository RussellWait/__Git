package SGG;

import java.util.Scanner;

/**
 *我的第一个Java程序
 *@author Russell
 *@version v1.0
 */


public class HelloWorld
{
	private static Scanner s;

	public static void main(String[] args)
	{
		System.out.println("Hello Java!");
		
		while (true)
		{
			s = new Scanner(System.in);
			System.out.println(s.nextLine());
		}
	}
}

class Dog
{
	
}
