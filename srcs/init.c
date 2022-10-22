/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:28:17 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:28:18 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_init(t_env *env)
{
	if (!env)
		return (false);
	ft_memset((void *)env, '\0', sizeof(*env));
	return (true);
}
