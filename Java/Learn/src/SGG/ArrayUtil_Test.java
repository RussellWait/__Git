package SGG;

public class ArrayUtil_Test
{
	public static void main(String[] arge)
	{
		ArrayUtil arrayUtil = new ArrayUtil();
		int[] array = {3, 5, 7, 2, 11, 21};
		
		arrayUtil.printArray(array);
		System.out.println("max:" + arrayUtil.getMax(array));
		System.out.println("min:" + arrayUtil.getMin(array));
		System.out.println("avg:" + arrayUtil.avg(array));
	}
}
