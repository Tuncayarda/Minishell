/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 20:13:11 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;32m\002🐱 OIIA OIIA$\001\033[0m\002"
# define WHITESPACES " \t\n\v\f\r"

# include <gc.h>

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_token		t_token;

struct	s_shell
{
	char					*cmd;
	t_env					*env;
	t_token					*token_list;
	t_gc					gc;
};

#endif