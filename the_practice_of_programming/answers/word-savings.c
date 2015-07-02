#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

enum { NHASH = 127, MULTIPLIER = 31 };

struct word_entry {
	char *word;
	int count;
	struct word_entry *next;
};

struct word_entry *words[NHASH];

int hash(const char *word)
{
	unsigned int h = 0;

	while (*word != '\0') {
		h = h * MULTIPLIER + *word;
		word++;
	}

	return h % NHASH;
}

void add_word(char *word)
{
	struct word_entry *p;
	int h;

	h = hash(word);
	for (p = words[h]; p != NULL; p = p->next) {
		if (strcmp(word, p->word) == 0) {
			p->count++;
			return;
		}
	}
	p = emalloc(sizeof(struct word_entry));
	p->word = estrdup(word);
	p->count = 1;
	p->next = words[h];
	words[h] = p;
}

void clear_words(void)
{
	int i;

	for (i = 0; i < NHASH; i++)
		words[i] = NULL;
}

void freeall(void)
{
	struct word_entry *p, *next;
	int i;

	for (i = 0; i < NHASH; i++) {
		for (p = words[i]; p != NULL; p = next) {
			next = p->next;
			free(p->word);
			free(p);
		}
	}
}

void print_summary(void)
{
	int low_words = 0, high_words = 0;
	int low_bytes = 0, high_bytes = 0;
	const struct word_entry *p;
	int i;

	for (i = 0; i < NHASH; i++) {
		for (p = words[i]; p != NULL; p = p->next) {
			low_words++;
			high_words += p->count;
			low_bytes += strlen(p->word) + 1;
			high_bytes += (strlen(p->word) + 1) * p->count;
		}
	}

	printf("words: %d to %d  bytes: %d to %d = %.2f%%\n",
		high_words, low_words,
		high_bytes, low_bytes,
		(double) (low_bytes - high_bytes) / high_bytes * 100);
}

int read_word(FILE *fp, char word[], size_t size)
{
	char fmt[10];

	sprintf(fmt, "%%%ds", (int) (size - 1));

	return fscanf(fp, fmt, word) != EOF;
}

int main(int argc, char *argv[])
{
	char word[100];
	const char *file_name;
	FILE *fp;
	int i;

	for (i = 1; i < argc; i++) {
		file_name = argv[i];
		fp = fopen(file_name, "r");
		if (fp == NULL) {
			fprintf(stderr, "Can't open %s.\n", file_name);
			continue;
		}
		clear_words();
		while (read_word(fp, word, sizeof(word)))
			add_word(word);
		fclose(fp);
		printf("%s: ", file_name);
		print_summary();
		freeall();
	}

	return 0;
}
