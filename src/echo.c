/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 20:32:17 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_last_in(char *str, char c, int index)
{
	int i;
	int last;
	int back;

	i = 0;
	last = 0;
	back = index;
	while (i < index)
	{
		if (str[i] == c)
			last = i;
		i++;
	}
	back = count_until(str, c, back);
	if (back % 2 != 0)
		return (last);
	return (-1);
}

char *str_delimited(char *str)
{
	int i;
	int j;
	int len;
	char *new;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '|' && is_in_aspas(str, i) == 1)
			len = i;
		i++;
	}
	new = malloc(sizeof(char) * len);
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char *get_args(char **args)
{
	char *str;
	int total_len;
	int i;

	i = 1;
	total_len = 0;
	while (args[i])
	{
		total_len += strlen(args[i]) + 1;
		i++;
	}
	str = malloc(total_len + 1);
	if (!str)
	{
		perror("Erro ao alocar memória");
		exit(EXIT_FAILURE);
	}
	str[0] = '\0';
	i = 1;
	while (args[i])
	{
		strcat(str, args[i]);
		strcat(str, " ");
		i++;
	}
	if (total_len > 0 && str[total_len - 1] == ' ')
		str[total_len - 1] = '\0';
	return str;
}

void ft_echo(t_variables *vars)
{
	int i;
	int get;
	char *str;

	i = 0;
	get = 0;

	str = get_args(vars->args);
	if (aspas_error(str, true))
		return;
	while (str[i] && str[i] != '|')
	{
		printf("%c", str[i]);
		i++;
	}
	free(str);
}
