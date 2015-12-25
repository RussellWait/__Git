package SGG;

public class Thread_Test
{
	public static void main(String[] args)
	{
		SubThread st1 = new SubThread();
		st1.setName("st1++++++++++");
		st1.start();
		
		SubThread st2 = new SubThread();
		st2.setName("st2----------");
		st2.start();
		
		for (int i = 0; i < 100; i++)
		{
			System.out.println(Thread.currentThread().getName() + i);
			
			try
			{
				if (0 == i%10)
				{
					Thread.currentThread().yield();
				}
				else if (0 == i%5)
				{
					st1.join();
				}
				else if (0 == i%15)
				{
					st2.join();
				}
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
		
		System.out.println("\n=================================================================\n");
		
		SubRunnable sr = new SubRunnable();
		Thread t1 = new Thread(sr);
		Thread t2 = new Thread(sr);
		Thread t3 = new Thread(sr);
		t1.start();
		t2.start();
		t3.start();
	}
}


class SubThread extends Thread
{
	public void run()
	{
		for (int i = 0; i < 50; i++)
		{
			System.out.println(Thread.currentThread().getName() + i);
		}
	}
}

class SubRunnable implements Runnable
{
	int num = 100;
	
	public void run()
	{	
		while (true)
		{
			synchronized (this)
			{
				if (num > 0)
				{
					try
					{
						num--;
						Thread.sleep(10);
						System.out.println(Thread.currentThread().getName() + ":" + num);
					}
					catch (InterruptedException e)
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				else
				{
					break;
				}
			}
		}
	}
}
