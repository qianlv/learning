import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Csv
{
	private BufferedReader in;
	private String fieldsep;
	private ArrayList field;

	private static int advquoted(String s, int i, String sep, StringBuffer field)
	{
		field.setLength(0);
		for ( ; i < s.length(); i++) {
			if (s.charAt(i) == '"' && ++i < s.length() && s.charAt(++i) != '"') {
				int j = s.indexOf(sep, i);
				if (j == -1)
					j = s.length();
				field.append(s.substring(i, j));
				i = j;
				break;
			}
			field.append(s.charAt(i));
		}

		return i;
	}

	private static ArrayList split(String line, String sep)
	{
		ArrayList list = new ArrayList();
		int i, j;

		if (line.length() == 0)
			return list;

		i = 0;
		do {
			if (i < line.length() && line.charAt(i) == '"') {
				StringBuffer field = new StringBuffer();
				j = advquoted(line, ++i, sep, field);
				list.add(field.toString());
			} else {
				j = line.indexOf(sep, i);
				if (j == -1)
					j = line.length();
				list.add(line.substring(i, j));
			}
			i = j + sep.length();
		} while (j < line.length());

		return list;
	}

	public Csv()
	{
		this(System.in, ",");
	}

	public Csv(InputStream in)
	{
		this(in, ",");
	}

	public Csv(InputStream in, String sep)
	{
		this.in = new BufferedReader(new InputStreamReader(in));
		this.fieldsep = sep;
	}

	public String getline() throws IOException
	{
		String line;

		line = in.readLine();
		if (line == null)
			return null;

		field = split(line, fieldsep);

		return line;
	}

	public String getfield(int n)
	{
		return (String) field.get(n);
	}

	public int getnfield()
	{
		return field.size();
	}

	public static void main(String[] args) throws IOException
	{
		Csv csv;
		String line;

		csv = new Csv();
		while ((line = csv.getline()) != null) {
			System.out.println("line = `" + line + "'");
			for (int i = 0; i < csv.getnfield(); i++) {
				System.out.println("field[" + i + "] = `"
					+ csv.getfield(i) + "'");

			}
		}
	}
}
