#include <stdio.h>
#include <stdlib.h>

void init(void)
{
	setvbuf(stdin,  NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(int argc, char *argv[])
{
	char name[64] = {};
	int  admin    = 0;

	init();

	printf("Hi there!\n");
	printf("What is your name?\n");

	printf("Name> ");
	scanf("%s", name);

	printf("Hello, %s!\n", name);

	if(admin)
		system("cat flag");
	else
		printf("You are not allowed to see the flag\n");
}
