/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:52:35 by justinosoar       #+#    #+#             */
/*   Updated: 2025/01/12 18:36:14 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	index_of(char *str, char *word)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str + i, word, ft_strlen(word)) == 0)
			return (i + ft_strlen(word) - 1);
		i++;
	}
	return (-1);
}

int	start_write(char *str, char *command)
{
	int	start;

	start = 0;
	start = index_of(str, command) + 1;
	while (*(str + start) == ' ')
		start++;
	return (start);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	remove_space(char *str, char ch)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (str == NULL || str[0] == '\0')
		return ;
	len = ft_strlen((const char *)str);
	while (i < len)
	{
		if (str[i] != ch)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	new_line(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (str[0] == '-')
		return (i + 1);
	return (0);
}

char	*ft_has_substr(char *str, char *substr, int n)
{
	int	i;
	int	j;
	int	count;

	if (!str || !substr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == substr[j])
		{
			count = 0;
			while (str[i] == substr[j] && substr[j] && count < n)
			{
				i++;
				j++;
				count++;
			}
			if (substr[j] == '\0' || count == n)
				return (str + i - j);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strcat(char *dest, const char *src)
{
	char *ptr = dest;
	while (*ptr != '\0')
	{
		ptr++;
	}
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}