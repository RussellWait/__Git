package SGG;

public class ArrayUtil
{
	public void printArray(int[] array)
	{
		for (int i = 0; i < array.length; i++)
		{
			System.out.print(array[i] + "\t");
		}
		System.out.println();
	}
	
	public int getMax(int[] array)
	{
		int max = array[0];
		for (int i = 1; i < array.length; i++)
		{
			if (max < array[i])
			{
				max = array[i];
			}
		}
		
		return max;
	}
	
	public int getMin(int[] array)
	{
		int min = array[0];
		for (int i = 1; i < array.length; i++)
		{
			if (min > array[i])
			{
				min = array[i];
			}
		}
		
		return min;
	}
	
	public int getSum(int[] array)
	{
		int sum = 0;
		for (int i = 0; i < array.length; i++)
		{
			sum += array[i];
		}
		
		return sum;
	}
	
	public float avg(int[] array)
	{
		return this.getSum(array) / array.length;
	}
}
