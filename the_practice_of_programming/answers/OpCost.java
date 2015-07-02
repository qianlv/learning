import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Date;

class AClass {
 public void fn()
 {
 }
}

class BClass extends AClass {
}
public class OpCost {
 static final int NUM_ITERATIONS = 500000;
 static DecimalFormat timeFormat = new DecimalFormat("##.000000");
 static double cal = 0.0;

 public static void main(String[] args)
 {
  AClass a = new AClass();
  BClass b = new BClass();
  int[] array;
  ArrayList al;
  LinkedList ll;
  Object o;
  calibrate();
  System.out.print("Calibration: ");
  System.out.println(timeFormat.format(cal));

  System.out.println();
  System.out.println("Object Operations");
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { a = new AClass(); } end = new Date(); { ; } System.out.print("  "); System.out.print("a = new AClass()"); for (int _i = 0; _i < 32 - "a = new AClass()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { b = new BClass(); } end = new Date(); { ; } System.out.print("  "); System.out.print("b = new BClass()"); for (int _i = 0; _i < 32 - "b = new BClass()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { a = b; } end = new Date(); { ; } System.out.print("  "); System.out.print("a = b"); for (int _i = 0; _i < 32 - "a = b".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { array = new int[10]; } end = new Date(); { ; } System.out.print("  "); System.out.print("array = new int[10]"); for (int _i = 0; _i < 32 - "array = new int[10]".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }

  System.out.println();
  System.out.println("Method Calls");
  a = new AClass();
  b = new BClass();
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { a.fn(); } end = new Date(); { ; } System.out.print("  "); System.out.print("a.fn()"); for (int _i = 0; _i < 32 - "a.fn()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { b.fn(); } end = new Date(); { ; } System.out.print("  "); System.out.print("b.fn()"); for (int _i = 0; _i < 32 - "b.fn()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }

  System.out.println();
  System.out.println("Containers");
  al = new ArrayList();
  ll = new LinkedList();
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { al = new ArrayList(); } end = new Date(); { ; } System.out.print("  "); System.out.print("al = new ArrayList()"); for (int _i = 0; _i < 32 - "al = new ArrayList()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { o = al.clone(); } end = new Date(); { ; } System.out.print("  "); System.out.print("o = al.clone()"); for (int _i = 0; _i < 32 - "o = al.clone()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { ll = new LinkedList(); } end = new Date(); { ; } System.out.print("  "); System.out.print("ll = new LinkedList()"); for (int _i = 0; _i < 32 - "ll = new LinkedList()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
  { Date start, end; { ; } start = new Date(); for (int _i = 0; _i < NUM_ITERATIONS; _i++) { o = ll.clone(); } end = new Date(); { ; } System.out.print("  "); System.out.print("o = ll.clone()"); for (int _i = 0; _i < 32 - "o = ll.clone()".length(); _i++) System.out.print(" "); System.out.println(timeFormat.format(nanos(start, end) - cal)); }
 }

 private static void calibrate()
 {
  Date start, end;
  start = new Date();
  for (int i = 0; i < NUM_ITERATIONS; i++)
   ;
  end = new Date();
  cal = nanos(start, end);
 }

 private static double nanos(Date start, Date end)
 {
  return ((double) end.getTime() - start.getTime()) * 1000.0 / NUM_ITERATIONS;
 }
}
