/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srgb_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:21 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:14:22 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_srgb	ft_srgb_create(int s, int r, int g, int b)
{
	t_srgb	result;

	result.data = (s << 24) | (r << 16) | (g << 8) | b;
	return (result);
}

t_srgb	ft_srgb_create_raw(int raw_color)
{
	t_srgb	result;

	ft_srgb_set_raw(&result, raw_color);
	return (result);
}

void	ft_srgb_set_raw(t_srgb *color, int bits)
{
	color->data = bits;
}
