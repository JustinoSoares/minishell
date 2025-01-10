/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:28:20 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/09 22:21:59 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void redirect_error(char *str, t_variables *vars, t_words **words)
{
    token_cmd_args(words, vars);
	if (vars->cmd_args[0] == NULL)
		write(2, "bash: Syntax error near unexpected token\n", 41);
    else if (ft_has_substr(str, ">>>", 3) == NULL
        && ft_has_substr(str, "<<<", 3) == NULL)
        function_redir(vars, words);
    else
        write(2, "bash: syntax error near unexpected token\n", 41);
}