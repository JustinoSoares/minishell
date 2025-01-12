/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:39:22 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/12 18:14:48 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_as(char *str, int i, int is_valid)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		if (str[i] == '"')
			return (i);
		else
			return (-1);
	}
	else if (str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i);
		else
			return (-1);
	}
	return (i);
}

int	aspas_error(char *str, int show_error)
{
	int	i;
	int	is_valid;

	is_valid = 1;
	i = 0;
	while (str[i] != '\0')
	{
		i = error_as(str, i, is_valid);
		if (i == -1)
		{
			printf("\033[31mError: aspas's error\033[m \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	error_pipe(char *str)
{
	int	i;
	int	mutex;
	int	pipes;

	i = 0;
	mutex = 0;
	pipes = count_elements(str, '|');
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (mutex == 0)
				mutex = 1;
			else
				return (printf("\033[31mError: pipe's error\033[m "));
		}
		i++;
	}
	return (0);
}
