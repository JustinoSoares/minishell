/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:15:58 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 16:53:49 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_matriz(char **matriz)
{
	int	i;

	i = 0;
	if (!matriz)
		return ;
	while (matriz[i])
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}

void	free_words(t_words *words)
{
	t_words	*tmp;

	if (!words)
		return ;
	while (words)
	{
		tmp = words;
		words = words->next;
		free(tmp->word);
		free(tmp);
	}
}

void	free_error(char *read, t_words *words, t_variables *vars)
{
	free_words(words);
	free(vars->line);
	free(read);
	return ;
}

void	free_env(t_env *ev)
{
	int	i;

	i = 0;
	if (!ev)
		return ;
	while (i < ev->len)
	{
		free(ev->env[i]);
		i++;
	}
	free(ev->env);
	free(ev);
}

char	**free_args(t_variables *vars)
{
	if (vars->args)
		free_matriz(vars->args);
	return (NULL);
}
