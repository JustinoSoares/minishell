/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:08 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/12 18:14:18 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_expanded(char *str, t_variables *vars, int i, int size)
{
	char	*macro;
	char	*word;

	while (str[i] != '\0')
	{
		if (str[i] && str[i] == '$' && str[i + 1] == '?')
			return (size + 1);
		else if (str[i] && str[i] == '$' && str[i + 1] && ft_isalnum(str[i
				+ 1]))
		{
			word = get_word(str, i + 1);
			macro = ft_get_env(word, vars->ev);
			if (macro != NULL)
			{
				size += ft_strlen(macro);
				i += ft_strlen(word);
				free(word);
				return (size);
			}
			i++;
			free(word);
			word = NULL;
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

int	size_expanded(char *str, t_variables *vars)
{
	int		size;
	char	*macro;
	char	*word;

	size = 0;
	size = count_expanded(str, vars, 0, size);
	return (size);
}

char	*is_expanded(char *str, t_variables *vars)
{
	int		i;
	int		j;
	char	*getter;
	char	*word;
	char	*macro;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	getter = ft_calloc(sizeof(char), size_expanded(str, vars) + 1);
	if (getter == NULL)
		return (NULL);
	return (aux_expanded(str, getter, vars, j));
}
