public class ListTestJava
{
	public static void main(String[] args)
	{
		List list;

		list = new List();
		check(list.size() == 0, "list.size() == 0");
		list.insert("abc");
		check(list.size() == 1, "list.size() == 1");
		check(list.contains("abc"), "list.contains(\"abc\")");
		check(!list.contains("def"), "!list.contains(\"def\")");
		check("abc".equals(list.get(0)), "\"abc\".equals(list.get(0))");
		list.insert("def");
		check(list.size() == 2, "list.size() == 2");
		check("def".equals(list.get(0)), "\"def\".equals(list.get(0))");
		list.delete("abc");
		check(!list.contains("abc"), "!list.contains(\"abc\")");
	}

	private static void check(boolean c, String what)
	{
		System.out.println((c ? "passed: " : "FAILED: ") + what);
	}
}
