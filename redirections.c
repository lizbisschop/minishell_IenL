#include "minishell.h"

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
				mini->exit_int = 1;
				return (-1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}

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

int			check_input_redir(char ***tokens, int i, int *tok_amount, int *found, int *fd, t_mini *mini)
{
	int		fd3;
	if (*found == 1)
		close(*fd);
	*found = 1;
	ft_putstr_fd((*tokens)[i + 1], mini->main_out);
	ft_putstr_fd("\n", mini->main_out);
	fd3 = open(((*tokens)[i + 1]), O_RDONLY);
	if (fd3 == -1)
	{
		ft_putstr_fd("ERROR\n", mini->main_out);
		mini->exit_int = 1;
		return (-1);
	}
	trim_tokens(i, tokens, tok_amount, mini);
	return (0);
}

void		check_redir(int *fd_out, int *fd_in, char ***tokens, int *tok_amount, t_mini *mini)
{
	int		i;
	int		fd;
	int		found;
	int		fd2;
	int		found2;

	i = 0;
	found = 0;
	found2 = 0;
	mini->out_redir = 0;
	mini->in_redir = 0;
	// ft_putstr_fd("fd_out = ", mini->main_out);
	// ft_putnbr_fd(*fd_out, mini->main_out);
	// ft_putstr_fd("\n", mini->main_out);
	// ft_putstr_fd("fd_in = ", mini->main_out);
	// ft_putnbr_fd(*fd_in, mini->main_out);
	// ft_putstr_fd("\n", mini->main_out);
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
				fd = open((*tokens)[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open((*tokens)[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
			ft_putstr_fd("new fd= ", mini->main_out);
			ft_putstr_fd(ft_itoa(fd), mini->main_out);
			ft_putstr_fd("\n", mini->main_out);
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
		else if (ft_strncmp((*tokens)[i], "<", 1) == 0 &&
		ft_strlen((*tokens)[i]) == 1)
		{
			if (found2 == 1)
				close(fd2);
			found2 = 1;
			ft_putstr_fd((*tokens)[i + 1], mini->main_out);
			ft_putstr_fd("\n", mini->main_out);
			fd2 = open(((*tokens)[i + 1]), O_RDONLY);
			if (fd2 == -1)
			{
				ft_putstr_fd("Error opening file\n", mini->main_out);
				return ;
			}
			trim_tokens(i, tokens, tok_amount, mini);
		}
		else
			i++;
	}
	if (found == 1)
	{
		ft_putstr_fd("output redir found: \n", mini->main_out);
		ft_putstr_fd(ft_itoa(fd), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		ft_putstr_fd(ft_itoa(*fd_out), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		if (mini->piped == 0)
			close(*fd_out); // in pipes is fd_out al geclosed
		*fd_out = dup(fd);
		ft_putstr_fd(ft_itoa(*fd_out), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		close(fd);
		mini->out_redir = 1;
	}
	if (found2 == 1)
	{
		ft_putstr_fd("input redir found: \n", mini->main_out);
		ft_putstr_fd(ft_itoa(fd2), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		ft_putstr_fd(ft_itoa(*fd_in), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		close(*fd_in);
		*fd_in = dup(fd2);
		ft_putstr_fd(ft_itoa(*fd_in), mini->main_out);
		ft_putstr_fd("\n", mini->main_out);
		close(fd2);
		mini->in_redir = 1;
	}
}
