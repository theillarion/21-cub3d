#include "cub3d.h"

void	ft_foreach(void **array, void (*func)(void *))
{
	if (!array || !func)
		return ;
	while (*array)
		(*func)(*(array++));
}

void	ft_smart_free(void	**address)
{
	if (address == NULL || *address == NULL)
		return ;
	free(*address);
	*address = NULL;
}

/*
void	ft_foreach(void **array, unsigned int size, void (*func)(void *))
{
	if (!array || !func)
		return ;
	while (*array)
	{
		(*func)(*(array));
		array = (void *)(((unsigned char *)*array) + size);
	}
}
*/