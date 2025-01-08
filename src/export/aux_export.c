/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:11:48 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/08 15:19:14 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_key_value(char *var, int identify)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (var[i] && var[i] != '=')
	{
		count++;
		i++;
	}
	if (identify == 0)
		return (count);
	count = 0;
	if (var[i])
		i++;
	else
		return (0);
	if (var[i] && var[i] == '"')
		i++;
	while (var[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

char	*ft_key(char *var)
{
	int		i;
	int		pos_key;
	char	*key;

	i = 0;
	pos_key = 0;
	key = malloc(sizeof(char) * count_key_value(var, 0) + 1);
	if (key == NULL)
		return (NULL);
	while (var[i] != '=' && var[i] != 32 && var[i] != '\0' && var[i] != '$')
	{
		key[pos_key] = var[i];
		pos_key++;
		i++;
	}
	key[pos_key] = '\0';
	return (key);
}

static char	*ft_value_dup(char *var, char *value, int i)
{
	int	pos_value;

	pos_value = 0;
	while (var[i] != '\0' && var[i] != '"')
	{
		value[pos_value] = var[i];
		pos_value++;
		i++;
	}
	value[pos_value] = '\0';
	return (value);
}

static char	*ft_value_simple(char *var, char *value, int i)
{
	int	pos_value;

	pos_value = 0;
	while (var[i] != '\0' && var[i] != '\'')
	{
		value[pos_value] = var[i];
		pos_value++;
		i++;
	}
	value[pos_value] = '\0';
	return (value);
}

char	*ft_value(char *var, int pos_value)
{
	int		i;
	char	*value;

	pos_value = 0;
	if (ft_strchr(var, '=') == NULL)
		return (NULL);
	i = count_key_value(var, 0) + 1;
	value = malloc(sizeof(char) * count_key_value(var, 1) + 1);
	if (value == NULL)
		return (NULL);
	if (var[i] && var[i] == '"')
		value = ft_value_dup(var, value, i + 1);
	else if (var[i] && var[i] == '\'')
		value = ft_value_simple(var, value, i + 1);
	else
	{
		while (var[i] != '\0')
		{
			value[pos_value] = var[i];
			pos_value++;
			i++;
		}
		value[pos_value] = '\0';
	}
	return (value);
}
