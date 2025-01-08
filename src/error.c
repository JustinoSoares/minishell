/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:39:22 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 13:16:22 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_as(char *str, int i, int duplas, int simples)
{
	int	mutex;

	mutex = 0;
	while (str[i])
	{
		if (is_in_aspas(str, i) == 1)
		{
			if (str[i] == '"')
			{
				duplas++;
				if (mutex == 0)
					mutex = 1;
				else
					mutex = 0;
			}
		}
		if (str[i] == '\'' && mutex == 0)
			simples++;
		i++;
	}
	if (duplas % 2 != 0 || simples % 2 != 0)
		return (-1);
}

int	aspas_error(char *str, int show_error)
{
	int	i;
	int	duplas;
	int	simples;

	i = 0;
	duplas = 0;
	simples = 0;
	if (error_as(str, i, duplas, simples) == -1)
		return (printf("\033[31mError: quotes error\033[m \n"));
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
