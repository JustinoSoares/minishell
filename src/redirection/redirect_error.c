/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:28:20 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/10 09:24:35 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void redirect_error(char *str, t_variables *vars, t_words **words)
{
	if (token_cmd_error(words, vars) == 0)
		write(2, "bash: Syntax error near unexpected token\n", 41);
    else if (ft_has_substr(str, ">>>", 3) == NULL
        && ft_has_substr(str, "<<<", 3) == NULL)
        function_redir(vars, words);
    else
        write(2, "bash: syntax error near unexpected token\n", 41);
}