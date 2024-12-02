/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/02 12:13:10 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int count_elements(char *str, char c)
{
    int count = 0;
    while (*str)
    {
        if (*str == c)
            count++;
        str++;
    }
    return (count);
}

char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && str[size] != 32 && str[size] != '"' && str[size] != '\'')
    {
        if (ft_isalnum(str[size]) || str[size] == '_')
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != 32 && str[start] != '"' && str[start] != '\'')
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

int count_until(char *str, char c, int index)
{
    int count = 0;
    int i = 0;
    while (i < index)
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int get_last_in(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    int back = index;
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

int is_in_aspas(char *str, int index)
{
    int start;
    int dup = get_last_in(str, '"', index);
    int simple = get_last_in(str, '\'', index);
    if (dup != -1)
    {
        start = get_last_in(str, '\'', dup);
        if (start != -1)
            return (0);
        return (1);
    }
    if (simple != -1)
    {
        start = get_last_in(str, '"', simple);
        if (start != -1)
            return (1);
        return (0);
    }
    return (1);
}

char *ft_strcat_macro(char *str, char *str2, int index, int size_word)
{
    char *new;
    int i = 0;
    int j = 0;
    int x = 0;
    int len = strlen(str) + strlen(str2);
    new = malloc(sizeof(char) * (strlen(str) + strlen(str2) + 1));
    while (str[i] && i < index)
    {
        new[i] = str[i];
        i++;
    }
    x = i;
    while (str2[j])
    {
        new[i] = str2[j];
        i++;
        j++;
    }
    x += size_word;
    while (str[x])
    {
        new[i] = str[x];
        i++;
        x++;
    }
    return (new);
}

int count_words(char *str)
{
    int count = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == 32 && str[i] != '$')
            count++;
        i++;
    }
    return (count + 1);
}
int is_valid_macro_char(char str)
{
    while (str != 32 && str != '$' && str != '"' && str != '\'' && str != '\0' && str != '$')
        return (1);
    return (0);
}
char *ft_strncpy(char *s1, char *s2, int n)
{
    int i;

    i = -1;
    while (++i < n && s2[i])
        s1[i] = s2[i];
    s1[i] = '\0';
    return (s1);
}

char **ft_split_new(char *s)
{
    int i = 0;
    int k = 0;
    int j = 0;
    char **split;

    split = malloc(sizeof(char *) * 256);
    if (!split)
        return (NULL);
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i++;
    while (s[i])
    {
        j = 0;
        split[k] = (char *)malloc(sizeof(char) * 4096);
        if (!split[k])
            return (NULL);
        while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i])
        {
            split[k][j++] = s[i++];
            if (s[i] == '$' || s[i] == '"' || s[i] == '\'')
                break;
        }
        while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
            i++;
        split[k][j] = '\0';
        k += 1;
    }
    split[k] = NULL;
    return (split);
}

int is_dup(char **each_word, int i)
{
    char *macro;
    // each_word[i] = ft_strdup("");
    while (each_word[++i] && each_word[i][0] != '"')
    {
        if (each_word[i][0] == '$')
        {
            macro = getenv(get_word(each_word[i], 1));
            if (macro)
                each_word[i] = ft_strdup(macro);
            else
                each_word[i] = ft_strdup("");
        }
    }
    // each_word[i] = ft_strdup("");
    return (i);
}

int is_simples(char **each_word, int i)
{
    each_word[i] = ft_strdup("");
    while (each_word[++i] && each_word[i][0] != '\'')
        ;
    each_word[i] = ft_strdup("");
    return (i);
}

int without_quotes(char **each_word, int i)
{
    char *macro;
    if (each_word[i][0] == '$')
    {
        if (each_word[i][0] == '$')
        {
            macro = getenv(get_word(each_word[i], 1));
            if (macro)
                each_word[i] = ft_strdup(macro);
            else
                each_word[i] = ft_strdup("");
        }
        i++;
    }
    return (i);
}

char **is_expanded(char *str)
{
    char *macro;
    char **each_word;
    int i = 0;
    int status = 0;

    each_word = ft_split_new(str);
    while (each_word[i])
    {
         if (each_word[i][0] == '\'')
            i = is_simples(each_word, i);
        else if (each_word[i][0] == '"')
            i = is_dup(each_word, i);
        else
            i = without_quotes(each_word, i);
        i++;
    }
    return (each_word);
}

void insert_fim(t_array **array, int count)
{
    t_array *new;
    t_array *tmp;

    new = malloc(sizeof(t_array));
    new->count = count;
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

t_array *count_spaces(char *str)
{
    t_array *array = NULL;
    t_array *tmp;
    int count = 0;
    int i = 0;
    int index = 0;
    int dolar = 0;

    array = malloc(sizeof(t_array));
    while (str[i])
    {
        if (str[i] == '"')
        {
            while (str[++i] && str[i] != '"')
            {
                if (str[i] && str[i] == 32)
                {
                    count = 0;
                    while (str[i] && str[i] == 32)
                    {
                        count++;
                        i++;
                    }
                    insert_fim(&array, count);
                }
            }
        }
        i++;
    }
    return (array);
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

char *form_char(char c, int quant)
{
    int i = 0;
    char *new = malloc(sizeof(char) * quant + 1);
    while (i < quant)
    {
        new[i] = c;
        i++;
    }
    new[i] = '\0';
    return (new);
}

char *join_all(char **matriz, char *str)
{
    int i = 0;
    t_array *array;
    t_array *tmp;
    int index = 0;
    char *new = malloc(sizeof(char) * 1);

    array = count_spaces(str);
    tmp = array->next;
    while (matriz[i])
    {
        if (matriz[i][0] == '"')
        {
            while (matriz[++i] && matriz[i][0] != '"')
            {
                new = ft_strcat(new, matriz[i]);
                new = ft_strcat(new, form_char(32, tmp->count));
                printf("Count2 : %d\n", tmp->count);
                if (tmp->next)
                    tmp = tmp->next;
            }
        }
        else
        {
            new = ft_strcat(new, matriz[i]);
            new = ft_strcat(new, form_char(32, 1));
        }
        i++;
    }
    return (new);
}

int get_index_quotes(char *str, int pos)
{
    int i = 0;
    int quotes = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            quotes++;
        if (quotes == pos)
            return (i);
        i++;
    }
    return (-1);
}

int main(void)
{
    char *str = "echo \"$HOME  $USER    skj    \"CAntar";
    //char **new = is_expanded(str);
    //char *new_new = join_all(new, str);
    char **new = ft_split_aspa(str, ' ');

    int i = 0;
    while (new[i])
    {
        printf("%s\n", new[i]);
        i++;
    }
    return (0);
}