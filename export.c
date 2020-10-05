#include "minishell.h"

void 	set_env(char *s, t_mini *mini)
{
	int i;

	i = 0;
	mini->def = ft_strdup(s);
	while(s[i] != '=' && s[i] != '\0')
		i++;
	mini->set = ft_substr(s, 0, i);
	mini->alias = ft_strdup(&s[i + 1]);
	printf("%s | %s\n", mini->set, mini->alias);
}