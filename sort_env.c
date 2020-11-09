/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:56 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:57 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_buckets(char **env, int *arr, int bucket_n)
{
	int		i;
	int		start;
	int		end;

	end = 0;
	i = 0;
	while (i < bucket_n)
	{
		start = end;
		while (arr[end + 1] && env[arr[end + 1]][0] &&
		env[arr[end]][0] == env[arr[end + 1]][0])
			end++;
		if (start != end)
			insertion_sort(end, start, arr, env);
		end++;
		i++;
	}
}

int		create_buckets(int env_len, int *arr, char *alphabet, char **env)
{
	int		index;
	int		i;
	int		j;
	int		bucket_n;

	index = 0;
	i = 0;
	bucket_n = 0;
	while (i < EXT_ALPHABET_SIZE)
	{
		j = 0;
		while (j < env_len)
		{
			if (env[j][0] == alphabet[i])
			{
				if (index == 0 || env[arr[index - 1]][0] != alphabet[i])
					bucket_n++;
				arr[index] = j;
				index++;
			}
			j++;
		}
		i++;
	}
	return (bucket_n);
}

int		*sort_env(char **env)
{
	char	*alphabet;
	int		env_len;
	int		*arr;
	int		bucket_n;

	env_len = 0;
	alphabet = ft_strdup("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	alphabet = gnl_strjoin(alphabet, "_abcdefghijklmnopqrstuvwxyz");
	while (env[env_len])
		env_len++;
	arr = ft_calloc(env_len + 1, sizeof(int));
	arr[env_len] = '\0';
	bucket_n = create_buckets(env_len, arr, alphabet, env);
	sort_buckets(env, arr, bucket_n);
	if (alphabet)
		free(alphabet);
	return (arr);
}
