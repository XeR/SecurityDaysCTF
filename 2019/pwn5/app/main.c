#include <stdio.h>
#include <stdlib.h>

void init(void)
{
	setvbuf(stdin,  NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int readchar()
{
	int ret;

	if('\n' == (ret = getchar()))
		ret = EOF;

	return ret;
}

int main(int argc, char *argv[])
{
	char   buffer[64] = {};
	size_t i;
	int    r;

	init();

	do {
		i = 0;

		while(EOF != (r = readchar()))
			buffer[i++] = r;

		if(i > 0)
			puts(buffer);
	} while(i > 0);

	return EXIT_SUCCESS;
}
