#include "./github_minishell/libft/libft.h"
#include "stdio.h"

void	swap(int int1, int int2, int *arr)
{
	int tmp;

	tmp = arr[int1];
	arr[int1] = arr[int2];
	arr[int2] = tmp;
}

void	bubble_sort(const int end, const int start, int env_len, int *arr, const char **env)
{
	int		i;
	int		len;
	int		res;
	int		j;

	printf("end%d, start%d, envlen%d\n", end, start, env_len);
	i = start;
	while (i < end - start) // loop over 
	{
		printf("i	|");
		while (j < end)
		{
			printf("j	|");
			len = ft_strlen(env[arr[start]]);
			if (ft_strlen(env[arr[start + j + 1]]) < (unsigned)len)
				len = ft_strlen(env[arr[start + 1]]);
			res = ft_strncmp(env[arr[start + j]], env[arr[start + j + 1]], len);
			if (res > 0)
				swap(start, start + 1, arr);
			else if (res == 0)
			{
				if (env[arr[start + 1 + len]][len] == '=')
					swap(start, start + 1, arr);
			}
			j++;
		}
		i++;
	}
	i = 0;
	printf("\n");
	while (i < env_len)
	{
		printf("%d|", arr[i]);
		printf("%s\n", env[arr[i]]);
		i++;
	}
	printf("\n");
}

int		bucket(int env_len, int *arr, char *alphabet, const char **env)
{
	int		index;
	int		i;
	int		j;
	int		bucket_n;
	int		alpha_len;

	index = 0;
	i = 0;
	bucket_n = 0;
	alpha_len = ft_strlen(alphabet);
	while (i < alpha_len)
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
	i = 0;
	while (i < env_len)
	{
		printf("%d|", arr[i]);
		i++;
	}
	printf("\n");
	return (bucket_n);
}

char	**sort_env(const char **env)
{
	char	*alphabet;
	int		alpha_len;
	int		env_len;
	char	**new;
	int		*arr;
	int		bucket_n;
	int		i;
	int		j;
	int		start;
	int		end;

	env_len = 0;
	alphabet =
	ft_strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz");
	alpha_len = ft_strlen(alphabet);
	printf("%d\n", env_len);
	while (env[env_len])
	{
		// printf("%s\n", env[env_len]);
		env_len++;
	}
	printf("env_len=%d, alpha_len=%d\n", env_len, alpha_len);
	new = ft_calloc(env_len + 1, sizeof(char *));
	arr = ft_calloc(env_len + 1, sizeof(int));
	arr[env_len + 1] = '\0';
	new[env_len + 1] = NULL;
	bucket_n = bucket(env_len, arr, alphabet, env);
	printf("bucket_n = %d\n", bucket_n);
	i = 0;
	(void)i;
	end = 0;
	while (j < bucket_n)
	{
		start = end;
		while (arr[end + 1] && env[arr[end + 1]][0] &&
		env[arr[end]][0] == env[arr[end + 1]][0])
		{
			printf("%c\n", env[arr[end]][0]);
			end++;
		}
		if (start != end)
			bubble_sort(end, start, env_len, arr, env);
		end++;
		j++;
	}
	if (alphabet)
		free(alphabet);
	return (new);
}

int		main(void)
{
	const char *env[6];

	env[0] = "hee";
	env[1] = "hallo";
	env[2] = "hey";
	env[3] = "halloa";
	env[4] = "hola",
	env[5] = NULL;
	sort_env(env);
}
