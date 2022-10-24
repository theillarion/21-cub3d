/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:15 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:14:16 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_point(t_point *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void	ft_set_point_int(t_point_int *point, int x, int y)
{
	point->x = x;
	point->y = y;
}
