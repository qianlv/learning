#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int factorial(int n)
{
	int fac;
	fac = 1;
	while (n--)
		fac *= n;
	return fac;
}

int factorial_correct(int n)
{
	int fac;
	fac = 1;
	for ( ; n > 0; n--)
		fac *= n;
	return fac;
}

void print_chars(char *s)
{
	int i;
	i = 0;
	do {
		putchar(s[i++]);
		putchar('\n');
	} while (s[i] != '\0');
}

void print_chars_correct(char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		putchar(s[i]);
		putchar('\n');
	}
}

void strcpy_(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
}

void strcpy_correct(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}

void strncpy_(char *t, char *s, int n)
{
	while (n > 0 && *s != '\0') {
		*t = *s;
		t++;
		s++;
		n--;
	}
}

void strncpy_correct(char *t, char *s, int n)
{
	int i;

	for (i = 0; n > 0 && s[i] != '\0'; i++, n--)
		t[i] = s[i];
	t[i] = '\0';
}

void compare(int i, int j)
{
	if (i > j)
		printf("%d is greater than %d.\n", i, j);
	else
		printf("%d is smaller than %d.\n", i, j);
}

void compare_correct(int i, int j)
{
	if (i > j)
		printf("%d is greater than %d.\n", i, j);
	else if (i < j)
		printf("%d is smaller than %d.\n", i, j);
}

void charclass(int c)
{
	if (c >= 'A' && c <= 'Z') {
		if (c <= 'L')
			cout << "first half of alphabet";
		else
			cout << "second half of alphabet";
	}
}

void charclass_correct(int c)
{
	if (c >= 'A' && c <= 'Z') {
		if (c <= 'M')
			cout << "first half of alphabet";
		else
			cout << "second half of alphabet";
	}
}

void init_buf(void *buf, size_t len)
{
	strncpy((char *) buf, "ABCDEFGHIJKLMNOPQRSTUVWYXZ", len);
}

int main(int argc, char *argv[])
{
	char *s = "Hello, world!";
	char buf[32];
	char *p;
	int i;

	/* printf("factorial(-1): %d %d\n", factorial(-1), factorial_correct(-1)); */
	for (i = 0; i < 10; i++)
		printf("factorial(%d): %d %d\n", i, factorial(i), factorial_correct(i));

	printf("---\n");
	print_chars("");
	printf("---\n");
	print_chars_correct("");
	printf("---\n");

	init_buf(buf, sizeof(buf));
	strcpy_(buf, s);
	printf("[%s]\n", buf);
	init_buf(buf, sizeof(buf));
	strcpy_correct(buf, s);
	printf("[%s]\n", buf);

	printf("\n");

	init_buf(buf, sizeof(buf));
	strncpy_(buf, s, 5);
	printf("[%s]\n", buf);
	init_buf(buf, sizeof(buf));
	strncpy_(buf, s, 32);
	printf("[%s]\n", buf);

	init_buf(buf, sizeof(buf));
	strncpy_correct(buf, s, 5);
	printf("[%s]\n", buf);
	init_buf(buf, sizeof(buf));
	strncpy_correct(buf, s, 32);
	printf("[%s]\n", buf);

	printf("\n");

	compare(5, 6);
	compare(6, 5);
	compare(5, 5);
	compare_correct(5, 6);
	compare_correct(6, 5);
	compare_correct(5, 5);

	printf("\n");

	/* ABCDEFGHIJKLM */
	/* NOPQRSTUVWXYZ */
	for (p = "LMN%"; *p != '\0'; p++) {
		printf("%c: ", *p);
		charclass(*p);
		printf("\n");
	}
	for (p = "LMN%"; *p != '\0'; p++) {
		printf("%c: ", *p);
		charclass_correct(*p);
		printf("\n");
	}

	return 0;
}
