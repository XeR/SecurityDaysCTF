#include <stdio.h>
#include <stdlib.h>

int admin = 0;

void init(void)
{
	setvbuf(stdin,  NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(int argc, char *argv[])
{
	char name[64] = {};

	init();

	printf("Hi there!\n");
	printf("Man, those organizers are really out of idea...\n");

	printf("What is your name?\n");
	printf("Name> ");
	fgets(name, sizeof(name), stdin);

	printf("Hello, ");
	printf(name);
	printf("!\n");

	if(admin)
		system("cat flag");
	else
		printf("You are not allowed to see the flag\n");
}
