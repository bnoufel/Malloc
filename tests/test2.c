#include <stdlib.h>
#include <malloc.h>

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 10)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}
