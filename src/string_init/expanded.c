/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:08 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/10 00:22:59 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_expanded(char *str, t_variables *vars, int i, int size)
{
	char	*macro;
	char	*word;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (size + 1);
		if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		{
			word = get_word(str, i + 1);
			macro = ft_get_env(word, vars->ev);
			if (macro)
				size += ft_strlen(macro);
			i += ft_strlen(word);
			free(word);
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
	int		i;
	int		size;
	char	*macro;
	char	*word;

	size = 0;
	i = 0;
	size = count_expanded(str, vars, i, size);
	return (size);
}

char	*alloc_getter(char *str, t_variables *vars)
{
	char	*getter;

	getter = malloc(sizeof(char) * size_expanded(str, vars) + 1);
	if (getter == NULL)
		return (NULL);
	getter = ft_memset(getter, 0, size_expanded(str, vars) + 1);
	return (getter);
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
	getter = alloc_getter(str, vars);
	if (!str || getter == NULL)
		return (NULL);
	getter = aux_expanded(str, getter, vars, j);
	return (getter);
}
