public class List
{
	private class Node
	{
		private Object data;
		private Node next;

		public Node(Object data)
		{
			this.data = data;
			next = null;
		}
	}

	private Node head;

	public List()
	{
		head = null;
	}

	/* Insert an element at the front of the list. */
	public void insert(Object data)
	{
		Node node;

		node = new Node(data);
		node.next = head;
		head = node;
	}

	/* Return the number of elements in the list. */
	public int size()
	{
		Node p;
		int count;

		count = 0;
		for (p = head; p != null; p = p.next)
			count++;

		return count;
	}

	/* Get the object at the given index. */
	public Object get(int index) throws IndexOutOfBoundsException
	{
		Node p;

		for (p = head; p != null && index > 0; p = p.next)
			index--;
		if (p == null || index < 0)
			throw new IndexOutOfBoundsException();

		return p.data;
	}

	/* Delete the first occurrence of data in the list. Return true if
	   anything was deleted, false otherwise. */
	public boolean delete(Object data)
	{
		Node p, prev;

		prev = null;
		for (p = head; p != null; p = p.next) {
			if ((p.data == null && data == null)
			    || (p.data != null && p.data.equals(data))) {
				if (prev == null)
					head = p.next;
				else
					prev.next = p.next;
				return true;
			}
		}

		return false;
	}

	/* Return true if the list contains the given object. */
	public boolean contains(Object data)
	{
		Node p;

		for (p = head; p != null; p = p.next) {
			if ((p.data == null && data == null)
			    || (p.data != null && p.data.equals(data))) {
				return true;
			}
		}

		return false;
	}
}
