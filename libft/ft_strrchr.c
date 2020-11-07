/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:04:58 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:02:58 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char*)str;
	while (ptr[i] != '\0')
		i++;
	while (ptr[i] != (char)c && i != 0)
	{
		i--;
		if (ptr[i] == (char)c)
			return ((char*)&ptr[i]);
	}
	if ((char)c == '\0')
		return ((char*)&ptr[i]);
	return (0);
}
