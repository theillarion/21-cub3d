/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:53:10 by illarion          #+#    #+#             */
/*   Updated: 2022/10/09 18:53:13 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

// enum	e_keys
// {
// 	KeyEsc		= 65307,
// 	KeyLeft		= 65361,
// 	KeyUp		= 65362,
// 	KeyRight	= 65363,
// 	KeyDown		= 65364
// };

# ifdef CURRENT_OS_LINUX

enum	e_keys
{
	KeyEsc		= 65307,
	KeyLeft		= 97,
	KeyUp		= 119,
	KeyRight	= 100,
	KeyDown		= 115
};

# else
#  ifdef CURRENT_OS_MACOS

enum	e_keys
{
	KeyEsc		= 53,
	KeyLeft		= 0,
	KeyUp		= 13,
	KeyRight	= 2,
	KeyDown		= 1
};
#  else

enum	e_keys
{
	KeyEsc		= 0,
	KeyLeft		= 0,
	KeyUp		= 0,
	KeyRight	= 0,
	KeyDown		= 0
};
#  endif
# endif

#endif