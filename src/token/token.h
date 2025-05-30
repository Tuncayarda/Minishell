/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:10 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:06:28 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <minishell.h>
# include <libft.h>
# include <gc.h>

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum						e_token_type
{
	WORD,
	PIPE,
	HEREDOC,
	APPEND,
	QUOTE,
	DQUOTE,
	DOLLAR,
	INPUT,
	OUTPUT,
	WS,
	NONE
};

struct						s_token
{
	char					*text;
	t_token					*next;
	t_token					*prev;
	t_token_type			type;
};

t_token						*token_new(
								t_shell *shell,
								t_token_type type,
								char *text);

void						token_remove(
								t_token **token_list,
								t_token *token);

void						token_add_back(
								t_token **token_list,
								t_token *token);

void						token_clean(
								t_token **token_list);

t_token						*token_last(
								t_token *token_list);

void						token_insert(
								t_token **token_list,
								t_token *pos,
								t_token *new_list);

#endif