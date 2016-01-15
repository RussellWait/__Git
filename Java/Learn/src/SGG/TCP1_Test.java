package SGG;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

import org.junit.Test;


public class TCP1_Test
{
	public static void main(String[] args)
	{
		TCP1_Test obj = new TCP1_Test();
		//obj.server();
		obj.client();
	}
	
	@Test
	public void client()
	{
		Socket socket = null;
		OutputStream os = null;
		
		try
		{
			socket = new Socket(InetAddress.getByName("192.168.1.6"), 9090);
			os = socket.getOutputStream();
			os.write("I'm Client".getBytes());
		} 
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if (null != os)
		{
			try
			{
				os.close();
			} 
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (null != socket)
		{
			try
			{
				socket.close();
			} 
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}


	@Test
	public void server()
	{
		ServerSocket ss = null;
		Socket s = null;
		InputStream is = null;
		try
		{
			ss = new ServerSocket(9090);
			s = ss.accept();
			is = s.getInputStream();
			
			byte[] b = new byte[20];
			int len = 0;
			while ((len = is.read(b)) != -1)
			{
				String str = new String(b, 0, len);
				System.out.print(str);
			}
			
			System.out.println("server ready...");
		} 
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if (null != is)
		{
			try
			{
				is.close();
			} 
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (null != s)
		{
			try
			{
				s.close();
			} 
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (null != ss)
		{
			try
			{
				ss.close();
			} 
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
