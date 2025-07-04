/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:29:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 18:30:44 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>
#include <env.h>
#include <exec.h>
#include <gc.h>
#include <init.h>
#include <lexer.h>
#include <minishell.h>
#include <parser.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <token.h>
#include <utils.h>


int	main(int ac, char **av, char **env_data)
{
	t_shell	shell;

	(void)av;
	(void)ac;
	gc_init(&shell);
	init_shell(&shell, env_data);
	while (1)
	{
		shell.input = ft_strtrim(gc_track(&shell.gc,
					readline(get_prompt(shell.exit_status))), WHITESPACES);
		if (shell.input == NULL)
			break ;
		add_history(shell.input);
		/*if (!validate_input(&shell, shell.input))
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
			free(shell.input);
			continue ;
		}*/
		lexer_run(&shell);
		parser_run(&shell);
		//debug_print_cmd_list(shell.cmd_list);
		if (exec(&shell))
			break ;
		set_signals(S_MAIN);
		token_clean(&shell.token_list);
		cmd_clean(&shell.cmd_list);
		gc_free_all(&shell.gc);
		free(shell.input);
	}
	gc_free_all(&shell.env_gc);
	return (0);
}
