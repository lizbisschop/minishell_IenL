#include "minishell.h"

int		swap_count(char *key_str, char *str, size_t len)
{
	int		swaps;
	int		res;

	swaps = 0;
	if (word_len(str) < len)
		len = word_len(str);
	res = ft_strncmp(key_str, str, len);
	if (res < 0)
		swaps++;
	else if (res == 0)
	{
		if (len == word_len(key_str))
			swaps++;
	}
	return (swaps);
}

void	insertion_sort(int end, int start, int *arr, char **env)
{
	int		key;
	int		key_len;
	size_t	len;
	int		i;
	int		swaps;

	key = start + 1;
	len = 0;
	while (key <= end)
	{
		i = key - 1;
		key_len = word_len(env[arr[key]]);
		len = key_len;
		swaps = 0;
		while (i >= start)
		{
			swaps += swap_count(env[arr[key]], env[arr[i]], len);
			i--;
		}
		if (swaps)
			swap(key, swaps, arr);
		key++;
	}
}
