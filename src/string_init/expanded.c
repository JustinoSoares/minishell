/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:08 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/07 09:31:49 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_key(char *env)
{
    int i = 0;
    while (env[i] && env[i] != '=')
        i++;
    return (ft_substr(env, 0, i));
}

char *ft_get_env(char *key, t_env *env)
{
    int i = 0;
    int c = 0;
    char *get_env;
    while (env->env[i])
    {
        get_env = get_key(env->env[i]);
        if (ft_strcmp(get_env, key) == 0)
        {
            while (env->env[i][c] && env->env[i][c] != '=')
                c++;
            if (env->env[i][c] == '=')
            {
                free(get_env);
                return (env->env[i] + c + 1);
            }
        }
        free(get_env);
        i++;
    }
    return (NULL);
}

int count_expanded(char *str, t_variables *vars, int i, int size)
{
    char *macro;
    char *word;

    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
            return (size + 1);
        if (str[i] == '$' && str[i + 1] && str[i + 1] != '?')
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

int size_expanded(char *str, t_variables *vars)
{
    int i;
    int size;
    char *macro;
    char *word;

    size = 0;
    i = 0;
    size = count_expanded(str, vars, i, size);
    return (size);
}
char *alloc_getter(char *str, t_variables *vars)
{
    char *getter;

    getter = malloc(sizeof(char) * size_expanded(str, vars) + 1);
    getter = ft_memset(getter, 0, size_expanded(str, vars) + 1);
    if (getter == NULL)
        return (NULL);
}
char *call_status(char *str, t_variables *vars)
{
    if (status_signal == SIGINT)
        vars->status_command = 130;
    else if (status_signal == SIGQUIT)
        vars->status_command = 131;
    status_signal = 0;
    return (ft_itoa(vars->status_command));
}

// char *expanded(char *str)
// {
    
// }

char *is_expanded(char *str, t_variables *vars)
{
    int i = 0;
    int j = 0;
    char *getter;
    char *word;
    char *macro;

    getter = alloc_getter(str, vars);
    while (str[i])
    {
        if (str[i] && str[i] == '$' && str[i + 1] == '?')
            return (call_status(str, vars));
        else if (str[i] && str[i] == '$' && (str[i + 1] == '\0' || !ft_isalpha(str[i + 1])))
            getter[j++] = str[i++];
        else if (str[i] && str[i] == '$' && str[i + 1])
        {
            word = get_word(str, i + 1);
            if (word == NULL)
                return (NULL);
            macro = ft_get_env(word, vars->ev);
            if (macro && ft_strlen(macro) > 0)
                strcat(getter, macro);
            j += ft_strlen(macro);
            i += ft_strlen(word) + 1;
            free(word);
        }
        else if (str[i])
            getter[j++] = str[i++];
        else
            i++;
    }
    getter[j] = '\0';
    return (getter);
}
