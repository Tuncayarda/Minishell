/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:36:20 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:44:43 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	env_add(t_shell *shell, char *key, char *val)
{
	t_pair	*new_pairs;
	size_t	i;

	new_pairs = gc_track(&shell->gc,
			malloc(sizeof(t_pair) * (shell->env->count + 1)));
	if (!new_pairs)
		return ;
	i = 0;
	while (i < shell->env->count)
	{
		new_pairs[i].key = shell->env->pairs[i].key;
		new_pairs[i].val = shell->env->pairs[i].val;
		i++;
	}
	new_pairs[i].key = key;
	new_pairs[i].val = val;
	shell->env->pairs = new_pairs;
	shell->env->count++;
}
