/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:55:37 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/14 17:09:56 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int				i;
	char			*ptr;
	char			cha;

	i = 0;
	cha = (char)c;
	ptr = (char*)str;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == cha)
		{
			return ((char*)&ptr[i]);
		}
		i++;
	}
	if (cha == '\0')
		return ((char*)&ptr[i]);
	return (0);
}
