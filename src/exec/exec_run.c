/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:35:19 by kdrturan          #+#    #+#             */
/*   Updated: 2025/06/25 17:50:09 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

int	builtin_functions(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		env(shell);
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		export(shell, cmd);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		unset(shell, cmd);
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		pwd(shell);
	else if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		echo(cmd);
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0]) + 1))
		cd(shell, cmd);
	else
		return (1);
	return (0);
}

void	cmd_run(t_shell *shell, t_cmd *cmd)
{
	char	**env;
	char	*full_path;

	env = (char **)gc_track_array(&shell->exec_gc,
			(void **)env_cast_char(shell));
	full_path = find_in_path(shell, cmd);
	if (full_path)
		execve(full_path, cmd->args, env);
	else
		execve(cmd->args[0], cmd->args, env);
}

char	*find_in_path(t_shell *shell, t_cmd *cmd)
{
	int is_exist;
	char **full_path;
	char *path;
	size_t i;

	i = 0;
	path = gc_track(&shell->exec_gc, env_get_value(shell, "PATH"));
	full_path = (char **)gc_track_array(&shell->exec_gc, (void **)ft_split(path,
				':'));
	while (full_path[i])
	{
		full_path[i] = gc_track(&shell->exec_gc, ft_strjoin(full_path[i], "/"));
		full_path[i] = gc_track(&shell->exec_gc, ft_strjoin(full_path[i],
					cmd->args[0]));
		is_exist = access(full_path[i], F_OK | X_OK);
		if (!is_exist)
			return (full_path[i]);
		i++;
	}
	return (NULL);
}