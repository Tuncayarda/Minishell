/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:51:09 by kdrturan          #+#    #+#             */
/*   Updated: 2025/07/23 03:06:41 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	redir_stdout_processes(t_shell *shell, t_redir *redir, int fd)
{
	if (redir->type == APPEND)
	{
		fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error(true, redir->target, NULL, E_PERM0);
			shell->exit_status = 1;
			c_exit(shell);
		}
	}
	else
	{
		fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error(true, redir->target, NULL, E_PERM0);
			shell->exit_status = 1;
			c_exit(shell);
		}
	}
	shell->exit_status = 0;
	dup2(fd, STDOUT_FILENO);
}

void	manage_redir_main(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == APPEND)
			redir_stdout_processes(shell, redir, fd);
		else if (redir->type == INPUT)
		{
			if (access(redir->target, F_OK) == -1)
			{
				print_error(true, redir->target, NULL, E_FILE0);
				shell->exit_status = 1;
				c_exit(shell);
			}
			fd = open(redir->target, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if (fd != -1)
			close(fd);
		redir = redir->next;
	}
}

void	handle_redir_error(t_shell *shell, t_redir *redir)
{
	if (!redir->target)
	{
		print_error(false, NULL, NULL, E_SYNTAX);
		shell->exit_status = 2;
		c_exit(shell);
	}
	print_error(true, redir->target, NULL, E_FILE0);
	shell->exit_status = 1;
	c_exit(shell);
}

void	manage_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == APPEND)
			redir_stdout_processes(shell, redir, fd);
		else if (redir->type == INPUT)
		{
			if (!redir->target || access(redir->target, F_OK) == -1)
				handle_redir_error(shell, redir);
			fd = open(redir->target, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (fd != -1)
			close(fd);
		redir = redir->next;
	}
}

void	handle_heredoc_main(t_redir *redir)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strncmp(tmp, redir->target, ft_strlen(redir->target)
				+ 1))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
}
