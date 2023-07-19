#include "micro_paint.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

int	ft_print_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (ft_print_error(ERRARG));
	return (0);
}
