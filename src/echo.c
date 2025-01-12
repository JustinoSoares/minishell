/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/12 18:14:43 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_last_in(char *str, char c, int index)
{
	int	i;
	int	last;
	int	back;

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

char	*str_delimited(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

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

char	*get_args(char **args, int i)
{
	char	*str;
	int		total_len;
	int		start;

	total_len = 0;
	start = i;
	while (args[i])
	{
		total_len += ft_strlen(args[i]) + 1;
		i++;
	}
	str = malloc(total_len + 1);
	if (!str)
		exit(EXIT_FAILURE);
	str[0] = '\0';
	i = start;
	while (args[i])
	{
		strcat(str, args[i]);
		strcat(str, " ");
		i++;
	}
	if (total_len > 0 && str[total_len - 1] == ' ')
		str[total_len - 1] = '\0';
	return (str);
}

bool	is_within_quotes(const char *str, int index)
{
	bool	single_quote;
	bool	double_quote;
	int		i;

	single_quote = false;
	double_quote = false;
	i = 0;
	while (str[i] && i <= index)
	{
		if (str[i] == '\'' && !double_quote)
			// Alternar aspas simples se não estiver em aspas duplas
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			// Alternar aspas duplas se não estiver em aspas simples
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

void	ft_echo(t_variables *vars)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	start = 1;
	if (new_line(vars->args[1]) != 0)
		start = 2;
	str = get_args(vars->args, start);
	if (aspas_error(str, true))
		return ;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	if (new_line(vars->args[1]) == 0)
		printf("\n");
	free(str);
}
