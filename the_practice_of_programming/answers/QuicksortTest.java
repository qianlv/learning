import java.util.Random;

interface Cmp {
	int cmp(Object x, Object y);
}

class Icmp implements Cmp {
	public int cmp(Object o1, Object o2)
	{
		int i1 = ((Integer) o1).intValue();
		int i2 = ((Integer) o2).intValue();
		if (i1 < i2)
			return -1;
		else if (i1 == i2)
			return 0;
		else
			return 1;
	}
}

class Quicksort {
	// Quicksort.sort: quicksort v[left]..v[right]
	static void sort(Object[] v, int left, int right, Cmp cmp)
	{
		int i, last;

		if (left >= right)  // nothing to do
			return;
		swap(v, left, rand(left,right));  // move pivot elem
		last = left;                      //   to v[left]
		for (i = left+1; i <= right; i++) // partition
			if (cmp.cmp(v[i], v[left]) < 0)
				swap(v, ++last, i);
		swap(v, left, last);              // restore pivot elem
		sort(v, left, last-1, cmp);       // recursively sort
		sort(v, last+1, right, cmp);      //   each part
	}

	// Like sort but specialized to sort ints.
	static void sort(int[] v, int left, int right)
	{
		int i, last;

		if (left >= right)  // nothing to do
			return;
		swap(v, left, rand(left,right));  // move pivot elem
		last = left;                      //   to v[left]
		for (i = left+1; i <= right; i++) // partition
			if (v[i] < v[left])
				swap(v, ++last, i);
		swap(v, left, last);              // restore pivot elem
		sort(v, left, last-1);            // recursively sort
		sort(v, last+1, right);           //   each part
	}

	// Quicksort.swap: swap v[i] and v[j]
	static void swap(Object[] v, int i, int j)
	{
		Object temp;

		temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}

	// Like swap but specialize to sort ints
	static void swap(int[] v, int i, int j)
	{
		int temp;

		temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}

	static Random rgen = new Random();

	// Quicksort.rand: return random integer in [left,right]
	static int rand(int left, int right)
	{
		return left + Math.abs(rgen.nextInt())%(right-left+1);
	}
}

public class QuicksortTest {
	public static void main(String[] args)
	{
		long start, end;
		int size;

		size = 1;
		for (int i = 0; i < 7; i++) {
			Integer[] objArray;
			int[] primArray;
			double objTime, primTime;

			// create int and Integer arrays with the same values
			primArray = new int[size];
			fillArrayRandom(primArray);
			objArray = new Integer[size];
			for (int j = 0; j < primArray.length; j++)
				objArray[j] = new Integer(primArray[j]);

			System.out.println("Size " + size);
			start = System.currentTimeMillis();
			Quicksort.sort(objArray, 0, objArray.length - 1, new Icmp());
			end = System.currentTimeMillis();
			objTime = (end - start) / 1000.0;
			System.out.println("Objects (Integer): " + objTime);

			start = System.currentTimeMillis();
			Quicksort.sort(primArray, 0, primArray.length - 1);
			end = System.currentTimeMillis();
			primTime = (end - start) / 1000.0;
			System.out.println("Primitives (int):  " + primTime);

			System.out.println("Ratio objects / primitives: "
				+ new java.text.DecimalFormat("0.###").format(objTime / primTime));

			size *= 10;
		}
	}

	private static Random rgen = new Random();

	private static void fillArrayRandom(int[] v)
	{
		for (int i = 0; i < v.length; i++)
			v[i] = rgen.nextInt();
	}
}
