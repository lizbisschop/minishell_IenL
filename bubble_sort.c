#include "minishell.h"

char **bubble_sort(char **str)
{
	char *alphabet;
	alphabet = ft_strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	int i;
	int j;
	int alpha;
	char **new;

	i = 0;
	j = 0;
	alpha = 0;
	while (str[i])
		i++;
	new = ft_calloc(i, sizeof(char *));
	i = 0;
	while (alphabet[alpha] != '\0')
	{
		while (str[i])
		{
			if (str[i][0] == alphabet[alpha])
			{
			// printf("[%c], [%c]\n", str[i][0], alphabet[alpha]);
				new[j] = ft_strdup(str[i]);
				j++;
				// alpha++;
			}	
			i++;
		}
		alpha++;
		i = 0;
	}
	return (new);
}