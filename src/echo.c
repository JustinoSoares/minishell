/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 12:58:44 by rquilami         ###   ########.fr       */
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

void	ft_echo(t_variables *vars)
{
	int		i;
	int		get;
	char	*str;

	i = 0;
	get = 0;
	str = vars->line + (start_write(vars->line, vars->args[0])
			+ new_line(vars->args[1]));
	if (aspas_error(str, true))
		return ;
	while (str[i] && str[i] != '|')
	{
		printf("%c", str[i]);
		i++;
	}
}
