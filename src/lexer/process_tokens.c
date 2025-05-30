/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:15:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 13:18:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <stdlib.h>
#include <token.h>
#include <minishell.h>
#include <libft.h>
#include <env.h>
#include <utils.h>

void	process_tokens(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->type == QUOTE)
			process_quote_token(shell, &tmp);
		tmp = tmp->next;
	}
}
