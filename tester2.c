/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/06 15:38:33 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/*typedef struct s_words
{
    char *word;
    int type;
    struct s_words *next;
} t_words;*/

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

char *get_word_s(char *str, int start)
{
    char *new;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '\'')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != '\'')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != 32)
    {
        if (ft_isalnum(str[size]) || str[size] == '_')
        {
            size++;
            len++;
        }
        else
            break;
    }
    new = malloc(sizeof(char) * (len + 1));
    while (str[start] && str[start] != 32)
    {
        if (ft_isalnum(str[start]) || str[start] == '_')
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word_d(char *str, int start)
{
    char *new;
    char *macro;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '"')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return NULL; // Check for allocation failure

    while (str[start] && str[start] != '"')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return new;
}

char *get_word_empty(char *str, int start)
{
    char *new;
    char *macro;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '"' && str[size] != 32 && str[size] != '\'')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return NULL; // Check for allocation failure

    while (str[start] && str[start] != '"' && str[start] != 32 && str[start] != '\'')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return new;
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

int size_expanded(char *str)
{
    int i = 0;
    int size = 0;
    char *macro;
    char *word;

    while (str[i])
    {
        if (str[i] == '$')
        {
            word = get_word(str, i + 1);
            macro = getenv(word);
            if (macro)
            {
                size += strlen(macro);
            }
            i += strlen(word);
            free(word); // Libere a memória se get_word alocar
        }
        else
        {
            i++;
            size++;
        }
    }
    return size;
}

char *is_expanded(char *str)
{
    int i = 0;
    int j = 0;
    char *new;
    char *word;
    char *macro;

    new = malloc(sizeof(char) * size_expanded(str) + 1);
    new = ft_memset(new, 0, size_expanded(str) + 1);
    if (new == NULL)
        return NULL;
    while (str[i])
    {
        if (str[i] == '$')
        {
            word = get_word(str, i + 1);
            macro = getenv(word);
            if (macro && strlen(macro) > 0)
            {
                strcat(new, macro); // Use strcat com cuidado
                j += strlen(macro);
                i += strlen(word) + 1;
            }
            else
            {
                i += strlen(word) + 1;
                // if (str[i + 1] != 32)
                //     i++;
            }
            free(word); // Libere a memória se get_word alocar
        }
        else if (str[i])
            new[j++] = str[i++];
    }
    new[j] = '\0'; // Não esqueça de terminar a string
    return (new);
}

int ft_quotes_dup(char *str, t_words **array, int i)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != '"')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != '"')
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word);
        insert_str_end(array, expanded_word, 2);
    }
    return (i + 1);
}

int ft_quotes_simples(char *str, t_words **array, int i)
{
    char *word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != '\'')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != '\'')
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
        insert_str_end(array, word, 1);
    return (i + 1);
}

int ft_empty(char *str, t_words **s_array, int i)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != 32 && str[index] != '"' && str[index] != '\'')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != 32 && str[i] != '"' && str[i] != '\'') 
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word);
        insert_str_end(s_array, expanded_word, 0);
    }
    return (i + 1);
}

void get_elements(char *str, t_words **array)
{
    int i = 0;
    char *word;
    char *expanded_word;
    char *expanded_empty;
    char *expanded_simple;

    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] && str[i] == '"')
            i = ft_quotes_dup(str, array, i + 1);
        else if (str[i] && str[i] == '\'')
            i = ft_quotes_simples(str, array, i + 1);
        else
            i = ft_empty(str, array, i);
    }
}

int main(void)
{
    char *str;

    str = "ls";
    t_words *array = NULL;
    t_words *tmp;
    char *new = NULL;
    // str = ft_strjoin(str, "  ");
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

    // char *macro = "$USER";
    // printf("Size : %d\n", size_expanded(macro));
    // printf("Size : %s\n", is_expanded(macro));

    return (0);
}