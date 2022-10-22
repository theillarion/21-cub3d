/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:31:37 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:31:37 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
