/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 17:06:06 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_status_signal = 0;

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status_signal = sig;
}

int	is_string_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_input(char *read)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	read = readline("Minishell: ");
	if (!read)
	{
		free(read);
		printf("exit\n");
		exit(0);
	}
	add_history(read);
	return (read);
}

void	ft_get_terminal(char **envp, t_variables *vars)
{
	char	*line;
	char	*read;
	t_words	*words;

	words = NULL;
	vars->status_command = 0;
	vars->env = envp;
	while (true)
	{
		read = ft_input(read);
		if (aspas_error(read, true) || read[0] == '\0'
			|| is_string_space(read) == 1)
			continue ;
		vars->line = filter_string(read, vars, &words);
		if (!vars->line)
			free_error(read, words, vars);
		vars->args = ft_split(vars->line, ' ');
		if (!vars->args)
			free_error(read, words, vars);
		function_pipe(vars, &words);
		vars->args = free_args(vars);
		free_error(read, words, vars);
		words = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_variables	vars;

	init_variables(&vars);
	init_ev(vars.ev);
	fill_env(vars.ev, envp);
	ft_get_terminal(envp, &vars);
	free_env(vars.ev);
	free_matriz(vars.env);
	return (0);
}
