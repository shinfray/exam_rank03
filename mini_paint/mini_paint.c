#include "mini_paint.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_print_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int	ft_retrieve_limit(FILE *file, t_limit *limit)
{
	if (fscanf(file, "%d %d %c\n", &limit->width, &limit->height, &limit->bg_char) != 3)
		return (-1);
	if (limit->width < 1 || limit->width > 300 \
		|| limit->height < 1 || limit->height > 300)
		return (-1);
	return (0);
}

int	ft_scan_l(FILE *file, t_shape *shape)
{
	return (fscanf(file, "%c %f %f %f %c\n]", &shape->op, &shape->x, &shape->y, &shape->radius, &shape->ch));
}

int	ft_quit(FILE *file, char *pic, const char *str)
{
	if (file != NULL)
		fclose(file);
	if (pic != NULL)
		free(pic);
	if (str != NULL)
		return (ft_print_error(str));
	return (EXIT_SUCCESS);
}

char	*ft_pic(t_limit *limit)
{
	char	*pic;
	size_t	pic_len;
	size_t	nl_place;
	int		i;

	pic_len = limit->width * limit->height + limit->height;
	pic = calloc(pic_len + 1, sizeof(*pic));
	if (pic == NULL)
		return (NULL);
	memset(pic, limit->bg_char, pic_len);
	nl_place = 0;
	i = 0;
	while (i++ < limit->height)
	{
		nl_place += limit->width;
		pic[nl_place] = '\n';
		++nl_place;
	}
	return (pic);
}

// int	ft_is_in_bordure(t_shape *shape, int x, int y)
// {
// 	// float	tlx = shape->x;
// 	// float	tly = shape->y;;

// 	// return (((x - tlx) < 1.0 || ((tlx + shape->width) - x) < 1.0) \
// 	// 		|| ((y - tly) < 1.0 || ((tly + shape->height) - y) < 1.0));

// }

int	ft_is_in_shape(t_shape *shape, char c, int x, int y)
{
	float	difference;

	difference = sqrtf(powf(x - shape->x, 2) + powf(y - shape->y, 2));
	return (difference <= shape->radius && (c == 'C' || (difference - shape->radius < 1)));
	// float	tlx = shape->x;
	// float	tly = shape->y;;
	// float	brx = tlx + shape->width;;
	// float	bry = tly + shape->height;;

	// return ((x >= tlx && x <= brx) && (y >= tly && y <= bry) \
	// 		&& (c == 'R' || (ft_is_in_bordure(shape, x, y) == 1)));
}

void	ft_apply_op(t_limit *limit, char *pic, t_shape *shape, char c)
{
	size_t	i = 0;
	int		y = 0;
	int		x;

	while (y < limit->height)
	{
		x = 0;
		while (x < limit->width)
		{
			if (ft_is_in_shape(shape, c, x, y) == 1)
					pic[i] = shape->ch;
			++i;
			++x;
		}
		++i;
		++y;
	}
}

int	ft_cmd_is_valid(t_shape *shape)
{
	return (shape->radius > 0 || (shape->op == 'c' || shape->op == 'C'));
}

int	ft_draw(FILE *file, t_limit *limit, t_shape *shape, char *pic)
{
	int		ret;

	while ((ret = ft_scan_l(file, shape)) == 5)
	{
		if (ft_cmd_is_valid(shape) == 0)
			return (-1);
		ft_apply_op(limit, pic, shape, shape->op);
	}
	if (ret != EOF)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	t_limit	s_limit;
	t_shape	s_shape;
	char	*pic;

	if (argc != 2)
		return (ft_print_error(ERRARG));
	pic = NULL;
	file = fopen(argv[1], "r");
	if (file == NULL)
		return (ft_quit(file, pic, ERRCORR));
	if (ft_retrieve_limit(file, &s_limit) != 0)
		return (ft_quit(file, pic, ERRCORR));
	pic = ft_pic(&s_limit);
	if (pic == NULL)
		return (ft_quit(file, pic, ERRCORR));
	if (ft_draw(file, &s_limit, &s_shape, pic) != 0)
		return (ft_quit(file, pic, ERRCORR));
	ft_putstr(pic);
	return (ft_quit(file, pic, NULL));
}
