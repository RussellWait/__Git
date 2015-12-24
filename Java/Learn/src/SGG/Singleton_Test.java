package SGG;

public class Singleton_Test
{
	public static void main(String[] args)
	{
		SubRunnable1 sr1 = new SubRunnable1();
		Thread t1 = new Thread(sr1);
		Thread t2 = new Thread(sr1);
		
		t1.start();
		t2.start();
		
		try
		{
			Thread.sleep(2000);
		} catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		SubRunnable2 sr2 = new SubRunnable2();
		Thread t3 = new Thread(sr2);
		Thread t4 = new Thread(sr2);
		
		t3.start();
		t4.start();
	}
}


class SubRunnable1 implements Runnable
{
	public void run()
	{
		Singleton.getInstance();
	}
}

class Singleton
{
	private static Singleton s_ShareSingleton = null;
	
	public static Singleton getInstance()
	{
		if (null == s_ShareSingleton)		// 提高效率
		{
			synchronized(Singleton.class)	// 线程安全
			{
				try
				{
					Thread.sleep(1000);
				} catch (InterruptedException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				if (null == s_ShareSingleton)
				{
					s_ShareSingleton = new Singleton();
					Object obj = s_ShareSingleton;
					System.out.println("=========" + obj);
				}
			}
		}
		
		return s_ShareSingleton;
	}
}

class SubRunnable2 implements Runnable
{
	int num = 0;
	
	public void run()
	{
		while (true)
		{	
			synchronized (this)
			{
				notify();
				
				if (num < 50)
				{
					try
					{
						Thread.sleep(50);
					} catch (InterruptedException e)
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}

					int n = num++;
					System.out.println(Thread.currentThread().getName() + " " + n);
				} else
				{
					break;
				}
				
				try
				{
					wait();
				} catch (InterruptedException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
}
