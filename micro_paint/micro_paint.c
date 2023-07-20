#include "micro_paint.h"

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
	return (1);
}

int	ft_retrieve_fl(FILE *file, int *width, int *height, char *bg_char)
{
	if (fscanf(file, "%d %d %c\n", width, height, bg_char) != 3)
		return (-1);
	if (*width < 1 || *width > 300 || *height < 1 || *height > 300)
		return (-1);
	return (0);
}

int	ft_scan_l(FILE *file, t_cl *s_cl)
{
	return (fscanf(file, "%c %f %f %f %f %c\n", &s_cl->op, &s_cl->x, &s_cl->y, &s_cl->width, &s_cl->height, &s_cl->ch));
}

int	ft_quit_error(FILE *file, char *pic, const char *str)
{
	fclose(file);
	if (pic != NULL)
		free(pic);
	return (ft_print_error(str));
}

char	*ft_pic(t_fl *fl)
{
	char	*pic;
	size_t	pic_len;
	size_t	nl_place;
	int		i;

	pic_len = fl->width * fl->height + fl->height;
	pic = calloc(pic_len + 1, sizeof(*pic));
	if (pic == NULL)
		return (NULL);
	memset(pic, fl->bg_char, pic_len);
	nl_place = 0;
	i = 0;
	while (i++ < fl->height)
	{
		nl_place += fl->width;
		pic[nl_place] = '\n';
		++nl_place;
	}
	return (pic);
}

void	ft_apply_op(t_fl *fl, char *pic, t_cl *cl, char c)
{
	float	tlx = cl->x;
	float	tly = cl->y;;
	float	brx = tlx + cl->width;;
	float	bry = tly + cl->height;;
	size_t	i = 0;
	int		y = 0;
	int		x;

	while (y < fl->height)
	{
		x = 0;
		while (x < fl->width)
		{
			if ((x >= tlx && x <= brx) && (y >= tly && y <= bry))
			{
				if (c == 'R' || (((x - tlx) < 1.0 || ((tlx + cl->width) - x) < 1.0) || ((y - tly) < 1.0 || ((tly + cl->height) - y) < 1.0)))
				{
					pic[i] = cl->ch;
				}
			}
			++i;
			++x;
		}
		++i;
		++y;
	}
}

int	main(int argc, char **argv)
{
	FILE	*file;
	t_fl	s_fl;
	t_cl	s_cl;
	int		ret;
	char	*pic;

	if (argc != 2)
		return (ft_print_error(ERRARG));
	file = fopen(argv[1], "r");
	if (file == NULL)
		return (ft_print_error(ERRCORR));
	pic = NULL;
	if (ft_retrieve_fl(file, &s_fl.width, &s_fl.height, &s_fl.bg_char) != 0)
		return (ft_quit_error(file, pic, ERRCORR));
	pic = ft_pic(&s_fl);
	if (pic == NULL)
		return (ft_quit_error(file, pic, ERRCORR));
	ret = 0;
	while ((ret = ft_scan_l(file, &s_cl)) == 6)
	{
		if (s_cl.width < 0 || s_cl.height < 0 || (s_cl.op != 'r' && s_cl.op != 'R'))
			return (ft_quit_error(file, pic, ERRCORR));
		ft_apply_op(&s_fl, pic, &s_cl, s_cl.op);
	}
	if (ret != EOF)
		return (ft_quit_error(file, pic, ERRCORR));
	ft_putstr(pic);
	fclose(file);
	return (0);
}
