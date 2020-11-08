#include "minishell.h"

void	free_second_string(char *s2)
{
	if (s2)
		free(s2);
}

char	*ft_strjoin_read(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str3;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str3)
		return (0);
	while (s1[i] != '\0')
	{
		str3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str3[i] = s2[j];
		j++;
		i++;
	}
	str3[i] = '\0';
	free_second_string(s2);
	return (str3);
}

char	*read_line(void)
{
	char	*line;
	int		ret;
	char	*old_line;

	line = NULL;
	ret = 0;
	ret = get_next_line(0, &line);
	if (ret == 0 && ft_strlen(line) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(1); //dit gaat soms nog fout met return values
	}
	while (ret == 0)
	{
		old_line = ft_strdup(line);
		ret = get_next_line(0, &line);
		line = ft_strjoin_read(old_line, line);
		if (old_line)
			free(old_line);
	}
	return (line);
}
