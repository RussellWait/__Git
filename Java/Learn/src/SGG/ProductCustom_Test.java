package SGG;

public class ProductCustom_Test
{
	public static void main(String[] args)
	{
		Clerk clerk = new Clerk();
		Product p = new Product(clerk);
		Customer c = new Customer(clerk);
		
		Thread tp1 = new Thread(p);
		tp1.setName("生产者1");
		
		Thread tp2 = new Thread(p);
		tp2.setName("生产者2");
		
		Thread tc1 = new Thread(c);
		tc1.setName("消费者1");
		
		tp1.start();
		tp2.start();
		tc1.start();
	}
}

class Clerk
{
	int _limt = 20;
	int _cur = 0;
	
	public synchronized void addProduct()
	{	
		if (_cur >= _limt)
		{
			try
			{
				wait();
			} catch (InterruptedException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else
		{
			try
			{
				Thread.sleep(20);
			} catch (InterruptedException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println(Thread.currentThread().getName() + "生产\t" + ++_cur);
			notifyAll();
		}
	}
	
	public synchronized void consumeProduct()
	{
		if (_cur <= 0)
		{
			try
			{
				wait();
			} catch (InterruptedException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else
		{
			try
			{
				Thread.sleep(10);
			} catch (InterruptedException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println(Thread.currentThread().getName() + "消费\t" + _cur--);
			notifyAll();
		}
	}
}

class Product implements Runnable
{
	private Clerk _clerk;
	
	public Product(Clerk clerk)
	{
		_clerk = clerk;
	}
	
	public void run()
	{
		while (true)
		{
			_clerk.addProduct();
		}
	}
}

class Customer implements Runnable
{
	private Clerk _clerk;
	
	public Customer(Clerk clerk)
	{
		_clerk = clerk;
	}
	
	public void run()
	{
		while (true)
		{
			_clerk.consumeProduct();
		}
	}
}