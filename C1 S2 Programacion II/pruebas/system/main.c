#include <windows.h>
#include <string.h>
#include <stdio.h>
int main()
{
	char inicio[]="";
	char* string1 = strcat(inicio,"echo Success");
	system(string1);
	//printf("k");
	return 0;
}