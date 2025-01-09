/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:30:11 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 12:57:48 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_elements(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	count_until(char *str, char c, int index)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	is_in_aspas(char *str, int index)
{
	int	start;
	int	dup;
	int	simple;

	dup = get_last_in(str, '"', index);
	simple = get_last_in(str, '\'', index);
	if (dup != -1)
	{
		start = get_last_in(str, '\'', dup);
		if (start != -1)
			return (0);
		return (1);
	}
	if (simple != -1)
	{
		start = get_last_in(str, '"', simple);
		if (start != -1)
			return (1);
		return (0);
	}
	return (1);
}

int	is_contra_barra(char *str, int i)
{
	if (str[i] == 92 && str[i + 1] == '"')
	{
		printf("\"");
		i += 2;
	}
	if (str[i] == 92 && str[i + 1] == '\'')
	{
		printf("'");
		i += 2;
	}
	return (i);
}

int	is_in(char *str, char c, int index)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (i < index)
	{
		if (str[i] == c)
			last++;
		i++;
	}
	if (last % 2 == 0)
		return (0);
	return (1);
}
