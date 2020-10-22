#include "minishell.h"

void		trim_tokens(int i, char ***tokens, int *tok_amount, t_mini *mini)
{
	while ((*tokens)[i])
	{
		free((*tokens)[i]);
		if ((*tokens)[i + 1] != NULL && (*tokens)[i + 2] != NULL)
			(*tokens)[i] = ft_strdup((*tokens)[i + 2]);
		else
		{
			free((*tokens)[i + 1]);
			(*tokens)[i] = NULL;
			(*tokens)[i + 1] = NULL;
		}
		i++;
	}
	i = 0;
	ft_putstr_fd("trimmed tokens\n", mini->main_out);
	while ((*tokens)[i])
	{
		ft_putstr_fd("[", mini->main_out);
		ft_putstr_fd((*tokens)[i], mini->main_out);
		ft_putstr_fd("]\n", mini->main_out);
		i++;
	}
	*tok_amount -= 2;
}

void		check_output_redir(int *fd_out, char ***tokens, int *tok_amount, t_mini *mini)
{
	int		i;
	int		fd;
	int		found;

	found = 0;
	i = 0;
	mini->out_redir = 0;
	while ((*tokens)[i])
	{
		if ((ft_strncmp((*tokens)[i], ">", 1) == 0 &&
		ft_strlen((*tokens)[i]) == 1) || (ft_strncmp((*tokens)[i], ">>", 2) == 0
		&& ft_strlen((*tokens)[i]) == 2))
		{
			if (found == 1)
				close(fd);
			found = 1;
			if (ft_strlen((*tokens)[i]) == 1)
				fd = open((*tokens)[i + 1], O_WRONLY | O_CREAT, 0777);
			else
				fd = open((*tokens)[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
			if (fd == -1)
			{
				ft_putstr_fd("bash: ", mini->main_out);
				ft_putstr_fd((*tokens)[i + 1], mini->main_out);
				ft_putstr_fd(strerror(errno), mini->main_out);
				ft_putstr_fd("\n", mini->main_out);
				mini->out_redir = -1;
				return ;
			}
			trim_tokens(i, tokens, tok_amount, mini);
		}
		else
			i++;
	}
	if (found == 1)
	{
		close(*fd_out);
		*fd_out = dup(fd);
		close(fd);
		mini->out_redir = 1;
	}
	else
		mini->out_redir = 0;
	return ;
}

int			valid_input_redir(t_command *command, t_mini *mini)
{
	int i;
	int	fd;

	i = 0;
	while (command->tokens[i])
	{
		if (ft_strncmp(command->tokens[i], "<", 1) == 0 &&
		ft_strlen(command->tokens[i]) == 1)
		{
			fd = open(command->tokens[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("bash: ", mini->main_out);
				ft_putstr_fd(command->tokens[i + 1], mini->main_out);
				ft_putstr_fd(": ", mini->main_out);
				ft_putstr_fd(strerror(errno), mini->main_out);
				ft_putstr_fd("\n", mini->main_out);
				command->invalid_input = 1;
				return (-1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}

void		check_input_redir(int *fd_in, char ***tokens, int *tok_amount, t_mini *mini)
{
	int		i;
	int		fd;
	int		found;

	found = 0;
	i = 0;
	while ((*tokens)[i])
	{
		if (ft_strncmp((*tokens)[i], "<", 1) == 0 &&
		ft_strlen((*tokens)[i]) == 1)
		{
			if (found == 1)
				close(fd);
			found = 1;
			fd = open((*tokens)[i + 1], O_RDONLY);
			if (fd == -1)
				return ;
			trim_tokens(i, tokens, tok_amount, mini);
		}
		else
			i++;
	}
	if (found == 1)
	{
		close(*fd_in);
		*fd_in = dup(fd);
		close(fd);
		mini->in_redir = 1;
		return ;
	}
	mini->in_redir = 0;
}
