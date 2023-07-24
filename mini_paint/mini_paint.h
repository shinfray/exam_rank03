/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:16:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/24 10:17:13 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ERRARG "Error: arguments\n"
# define ERRCORR "Error: Operation file corrupted\n"

typedef struct limit
{
	int		width;
	int		height;
	char	bg_char;
}				t_limit;

typedef struct shape
{
	char	op;
	float	x;
	float	y;
	float	radius;
	char	ch;
}				t_shape;

#endif
