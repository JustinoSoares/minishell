/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/02 16:49:45 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

typedef struct s_words
{
    char *word;
    int type;
    struct s_words *next;
} t_words;

char *get_word_full(char *str, int start, int is_space)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && (str[size] != 32 || is_space == 1) && str[size] != '"' && str[size] != '\'')
    {
        if (ft_isalnum(str[size]) || str[size] == '_' || (str[size] == 32 && is_space == 1))
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && (str[start] != 32 || is_space == 1) && str[start] != '"' && str[start] != '\'')
    {
        if (ft_isalnum(str[start]) || str[start] == '_' || (str[start] == 32 && is_space == 1))
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word_full_s(char *str, int start)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && str[size] != '\'')
    {
        if (ft_isalnum(str[size]) || str[size] == '_' || str[size] == '"' || str[size] == 32)
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != '\'')
    {
        if (ft_isalnum(str[start]) || str[start] == '_' || str[start] == '"' || str[start] == 32)
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word_full_d(char *str, int start)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && str[size] != '"')
    {
        if (ft_isalnum(str[size]) || str[size] == '_' || str[size] == '\'' || str[size] == 32)
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != '"')
    {
        if (ft_isalnum(str[start]) || str[start] == '_' || str[start] == '\'' || str[start] == 32)
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

void insert_str_end(t_words **array, char *str, int type)
{
    t_words *new;
    t_words *tmp;

    new = malloc(sizeof(t_array));
    new->word = strdup(str);
    new->type = type;
    new->next = NULL;
    if (*array == NULL)
        *array = new;
    else
    {
        tmp = *array;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void get_elements(char *str, t_words **array)
{
    int i = 0;
    char *word;

    word = malloc(sizeof(char) * 1);
    while (str[i] && str[i] == 32)
        i++;
    while (str[i])
    {
        if (str[i] && str[i] == '"')
        {
            word = ft_strdup(get_word_full_d(str, i + 1));
            insert_str_end(array, word, 2);
            i += strlen(word) + 1;
        }
        else if (str[i] && str[i] == '\'')
        {
            word = ft_strdup(get_word_full_s(str, i + 1));
            i += strlen(word) + 1;
            insert_str_end(array, word, 1);
        }
        else
        {
            word = ft_strdup(get_word_full(str, i, 0));
            if (ft_strlen(word) > 1 || (ft_strlen(word) == 1 && isalnum(str[i + 1])))
            {
                insert_str_end(array, word, 0);
                i += strlen(word);
            }
        }
        i++;
    }
}

char *ft_strcat(char *dest, char *s)
{
    char *new;
    int len;
    int i = 0;
    int j = 0;
    int spaces = 0;
    int count_space = 0;

    len = ft_strlen(dest) + ft_strlen(s);
    new = malloc(sizeof(char) * len + 1);
    if (dest == NULL || s == NULL)
        return (NULL);
    while (dest[i])
    {
        new[i] = dest[i];
        i++;
    }
    while (s[j])
        new[i++] = s[j++];
    return (new);
}

int main(void)
{
    char *str;
    
    str = malloc(sizeof(char) * 1);
    str = "echo \"hello ' world \" 'hello \"world nada mais' 'hello n world'";
    t_words *array = NULL;
    t_words *tmp;
    char *new;
    str = ft_strjoin(str, "  ");
    get_elements(str, &array);
    tmp = array;
    while (tmp != NULL)
    {
        new = ft_strjoin(new, tmp->word);
        if (tmp->next)
            new = ft_strjoin(new, " ");
        tmp = tmp->next;
    }
    printf("Old : %s\n", str);
    printf("New : %s\n", new);
    return (0);
}