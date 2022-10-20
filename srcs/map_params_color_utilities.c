/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_params_color_utilities.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:55:01 by ltowelie          #+#    #+#             */
/*   Updated: 2022/10/20 12:55:02 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initiate_color_params(char **tmp, char **c, int *len)
{
	*len = 0;
	*tmp = NULL;
	c[0] = NULL;
	c[1] = NULL;
	c[2] = NULL;
}

void	free_colors(char *const *c)
{
	free(c[0]);
	free(c[1]);
	free(c[2]);
}
