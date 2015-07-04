public class DecimalFormat {
	public static void main(String args[])
	{
		java.text.DecimalFormat df;
		String fmt;
		double v;

		if (args.length < 2) {
			System.err.println("Usage: DecimalFormat <format> <number>");
			System.exit(1);
		}

		fmt = args[0];
		v = Double.parseDouble(args[1]);

		df = new java.text.DecimalFormat(fmt);
		System.out.println(df.format(v));
	}
}
