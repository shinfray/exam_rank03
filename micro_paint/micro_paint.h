#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

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
	float	width;
	float	height;
	char	ch;
}				t_shape;

#endif
