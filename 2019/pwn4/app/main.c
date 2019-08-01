#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define  SIZE 16

void init(void)
{
	setvbuf(stdin,  NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

long long int askInt(const char *prompt)
{
	char buffer[64];

	printf("%s> ", prompt);
	fgets(buffer, sizeof(buffer), stdin);
	return strtoll(buffer, NULL, 0);
}

long long int menu(void)
{
	printf("0. leave\n");
	printf("1. sort\n");
	printf("2. set\n");
	printf("3. get\n");

	return askInt("choice");
}

void sort(long long unsigned array[SIZE])
{
	int cmp(const void *a, const void *b)
	{
		if(*((long*)a) >  *((long*)b))
			return 1;

		if(*((long*)a) <  *((long*)b))
			return -1;

		if(a > b) return 1;
		if(a < b) return -1;
		return 0;
	}

	qsort(array, SIZE, sizeof(long long unsigned), cmp);
	printf("Array sorted!\n");
}

void get(long long unsigned array[SIZE])
{
	size_t index;

	index = (size_t)askInt("index");
	printf("array[%lu] = %llu\n", index, array[index]);
}

void set(long long unsigned array[SIZE])
{
	size_t index;

	index        = (size_t)askInt("index");
	array[index] = (size_t)askInt("value");
}

int main(int argc, char *argv[])
{
	long long unsigned array[SIZE] = {};
	int choice;
	size_t i;

	init();

	do {
		choice = menu();

		if(1 == choice)
			sort(array);
		else if(2 == choice)
			set(array);
		else if(3 == choice)
			get(array);

	} while(0 != choice);

	printf("Final array:\n");
	for(i = 0; i < sizeof(array) / sizeof(*array); i++) {
		printf("array[%lu] = %llu\n", i, array[i]);
	}

	return EXIT_SUCCESS;
}
