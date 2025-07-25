/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:05:52 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/06 18:45:06 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	unset(t_shell *shell, t_cmd *cmd)
{
	t_gc	new_gc;
	t_env	*new_env;

	if (cmd->args[1])
	{
		new_gc.head = NULL;
		new_env = env_remove(shell, cmd->args[1], &new_gc);
		gc_free_all(&shell->env_gc);
		shell->env_gc = new_gc;
		shell->env = new_env;
		shell->exit_status = 0;
	}
}
