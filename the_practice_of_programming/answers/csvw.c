#include <stdio.h>
#include <string.h>

#include "csvw.h"

/* the file currently being written to */
static FILE *file_p = NULL;
/* whether we are at the beginning of a line */
static int linebegin = 1;

static const char *fieldsep = ",";

void csvw_start(FILE *fp)
{
	file_p = fp;
	linebegin = 1;
}

static int write_sep(void)
{
	if (!linebegin) {
		return fprintf(file_p, "%s", fieldsep);
	} else {
		linebegin = 0;
		return 0;
	}
}

static int needs_quoted(char *s)
{
	return strstr(s, fieldsep) != NULL || strchr(s, '"') != NULL;
}

static int write_string_unquoted(char *s)
{
	int count = 0;

	for ( ; *s != '\0'; s++) {
		if (*s != '\n')
			count += fprintf(file_p, "%c", *s);
	}

	return count;
}

static int write_string_quoted(char *s)
{
	int count = 0;

	count += fprintf(file_p, "\"");
	for ( ; *s != '\0'; s++) {
		if (*s == '"')
			count += fprintf(file_p, "\"\"");
		else if (*s == '\n')
			;
		else
			count += fprintf(file_p, "%c", *s);
	}
	count += fprintf(file_p, "\"");

	return count;
}

int csvw_write_string(char *s)
{
	int count;

	count = write_sep();
	if (needs_quoted(s))
		return count + write_string_quoted(s);
	else
		return count + write_string_unquoted(s);
}

int csvw_newline(void)
{
	linebegin = 1;

	return fprintf(file_p, "\n");
}

int main(int argc, char *argv[])
{
	csvw_start(stdout);
	csvw_write_string("a");
	csvw_write_string("b");
	csvw_write_string("c");
	csvw_write_string("d");
	csvw_newline();
	csvw_write_string("");
	csvw_write_string("abcd");
	csvw_write_string("ab,cd");
	csvw_write_string("ab,,cd");
	csvw_write_string("\"abcd\"");
	csvw_write_string("\"\"ab\"cd\"");
	csvw_newline();

	return 0;
}
