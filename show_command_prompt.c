#include "minishell.h"

static int	len_nbr(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		while (n / 10 < 0)
		{
			n = n / 10;
			i++;
		}
		i++;
	}
	else
	{
		while (n / 10 > 0)
		{
			n = n / 10;
			i++;
		}
	}
	i++;
	return (i);
}

static int	ft_negative(char *str, int n)
{
	int		min_int;

	min_int = -2147483648;
	str[0] = '-';
	if (n == min_int)
	{
		str[1] = '2';
		n = 147483648;
	}
	else
		n = -n;
	return (n);
}

char		*mini_itoa(int n)
{
	int		stop;
	int		len;
	char	*str;

	stop = 0;
	len = len_nbr(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (n < 0)
		stop = 1;
	if (n == -2147483648)
		stop = 2;
	if (n < 0)
		n = ft_negative(str, n);
	str[len] = '\0';
	len--;
	while (len >= stop)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

void	show_command_prompt(void)
{
	int		i;
	int		j;

	i = 31;
	j = 0;
	char buf[4096];
	getcwd(buf, 4096);
	if (buf == 0)
		ft_putstr_fd("Error getting path\n", 1);
	ft_putstr_fd("\e[0;31m~", 1);
	while (buf[j] != '\0' && i <= 36)
	{
		// printf("i = %i\n", i);
		ft_putstr_fd("\e[0;", 1);
		// ft_putstr_fd("31", 1);
		// ft_putstr_fd(mini_itoa(i), 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("m", 1);
		ft_putchar_fd(buf[j], 1);
		if (buf[j] == '/')
			i++;
		if (i == 37)
			i = 31;
		j++;
	}
	ft_putstr_fd("\e[0m", 1);
	write(1, "$ ", 2);
}
