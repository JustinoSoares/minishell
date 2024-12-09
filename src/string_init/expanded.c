/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/11 13:12:46 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_get_env(char *key, t_env *env)
{
    int i = 0;
    int c = 0;
    while (env->env[i])
    {
        if (ft_strncmp(env->env[i], key, ft_strlen(key)) == 0)
        {
            while (env->env[i][c] && env->env[i][c] != '=')
                c++;
            if (env->env[i][c] == '=')
                return (env->env[i] + c + 1);
        }
        i++;
    }
    return (NULL);
}

int size_expanded(char *str, t_variables *vars)
{
    int i = 0;
    int size = 0;
    char *macro;
    char *word;

    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
            return (size + 1);
        else if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == '$'))
        {
            i++;
            size++;
        }
        else if (str[i] == '$' && str[i + 1])
        {
            word = get_word(str, i + 1);
            macro = ft_get_env(word, vars->ev);
            if (macro)
                size += strlen(macro);
            i += strlen(word);
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

char *is_expanded(char *str, t_variables *vars)
{
    int i = 0;
    int j = 0;
    char *new;
    char *word;
    char *macro;

    new = malloc(sizeof(char) * size_expanded(str, vars) + 1);
    new = ft_memset(new, 0, size_expanded(str, vars) + 1);
    if (new == NULL)
        return (NULL);
    while (str[i])
    {
        if (str[i] && str[i] == '$' && str[i + 1] == '?')
        {
            if (status_signal == SIGINT)
                vars->status_command = 130;
            else if (status_signal == SIGQUIT)
                vars->status_command = 131;
            status_signal = 0;
            return (ft_itoa(vars->status_command));
        }
        else if (str[i] && str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == '$'))
            new[j++] = str[i++];
        else if (str[i] && str[i] == '$' && str[i + 1])
        {
            word = get_word(str, i + 1);
            if (word == NULL)
                return (NULL);
            macro = ft_get_env(word, vars->ev);
            if (macro && strlen(macro) > 0)
            {
                strcat(new, macro);
                j += ft_strlen(macro);
                i += ft_strlen(word) + 1;
            }
            else
                i += strlen(word) + 1;
            free(word);
        }
        else if (str[i])
            new[j++] = str[i++];
        else
            i++;
    }
    new[j] = '\0';
    return (new);
}
