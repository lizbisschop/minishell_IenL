/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:43 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/22 16:45:38 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		malloc_error();
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

char	*read_line(t_mini *mini)
{
	char	*line;
	int		ret;
	char	*old_line;

	ret = 0;
	ret = get_next_line(0, &line);
	if (ret == 0 && ft_strlen(line) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	while (ret == 0)
	{
		old_line = ft_strdup(line);
		if (line)
			free(line);
		ret = get_next_line(0, &line);
		line = ft_strjoin_read(old_line, line);
		if (old_line)
			free(old_line);
	}
	return (line);
}
