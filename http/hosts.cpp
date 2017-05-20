#include <netdb.h>
#include <stdio.h>

int main(void)
{
	while (struct hostent *he = gethostent())
	{
		printf("%s\n", he->h_name);
	}
}