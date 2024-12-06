/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/06 16:12:35 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int index_of(char *str, char *word)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (ft_strncmp(str + i, word, ft_strlen(word)) == 0)
            return (i + ft_strlen(word) - 1);
        i++;
    }
    return (-1);
}

int start_write(char *str, char *command)
{
    int start = 0;
    start = index_of(str, command) + 1;
    while (*(str + start) == ' ')
        start++;
    return (start);
}

int new_line(char *str)
{
    int i = 1;
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

void fill_env(t_env *ev, char **envp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (envp[i] != NULL)
        i++;
    ev->len = i;
    ev->env = malloc((i + 1) * sizeof(char *));
    if (!ev->env)
        return;
    while (j < i)
    {
        ev->env[j] = strdup(envp[j]);
        j++;
    }
    ev->env[i] = NULL;
}

char *ft_strcat_index(char *str, char *str2, int index)
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
    while (str[x])
    {
        new[i] = str[x];
        i++;
        x++;
    }
    return (new);
}

char *last_word(char *str, char limited)
{
    int i = 0;
    char **word;

    word = ft_split(str, limited);
    if (!word)
        return (NULL);
    while (word[i])
        i++;
    return (word[i - 1]);
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

int is_valid_macro_char(char str)
{
    while (str != 32 && str != '$' && str != '"' && str != '\'' && str != '\0' && str != '$')
        return (1);
    return (0);
}

/*char *is_expanded(char *st)
{
    char *macro, *word, *new;
    int i = 0;

    new = strdup(st);
    
    while (new[i])
    {
        if (new[i] == '"')
        {
            i++;
            while (new[i] && new[i] != '"')
            {
                if (new[i] == '$' && is_valid_macro_char(new[i + 1]))
                {
                    word = get_word(new, i + 1);
                    macro = getenv(word);
                    if (macro)
                    {
                        new = ft_strcat_macro(new, macro, i, ft_strlen(word) + 1);
                        i += ft_strlen(macro);
                    }
                    else
                        i += ft_strlen(word);
                    free(word);
                }
                else
                    i++;
            }
        }
        else if (new[i] == '\'')
            while (new[++i] && new[i] != '\'')
                ; // Ignorar dentro de aspas simpleS
        else if (new[i] == '$' && is_valid_macro_char(new[i + 1]))
        {
            word = get_word(new, i + 1);
            macro = getenv(word);
            if (macro)
            {
                new = ft_strcat_macro(new, macro, i, ft_strlen(word) + 1);
                i += ft_strlen(macro);
            }
            else
            {
                i += ft_strlen(word);
            }
            free(word);
        }
        else
            i++;
    }
    return (new);
}*/

void ctrl_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
void ft_get_terminal(char **envp, t_variables vars)
{
    char *line;
    char *new;
    int len = 0;
    vars.status_command = 0;
    vars.env = envp;
    //signal(SIGQUIT, ctrl_c); // quando o usuário aperta ctrl+d
    while (true)
    {
        signal(SIGINT, ctrl_c);  // quando o usuário aperta ctrl+c
        line = ft_strcat_index("\033[1;32mroot@minishell\033[m:~/ $ ",
                               last_word(getcwd(NULL, 0), '/'), 27);
        new = readline(line);
        if (!new)
            return ;
        vars.line = filter_string(new);
        printf("line: %s\n", vars.line);
        add_history(new);
        if (!vars.line)
            return (free(vars.line));
        vars.args = ft_split(vars.line, ' ');
        if (!vars.line)
            return (free(vars.line));
        ft_exec_functions(vars);
        write_history("history");
        free(vars.line);
        free(new);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_variables vars;
    vars.ev = malloc(sizeof(t_env));
    fill_env(vars.ev, envp);
    ft_get_terminal(envp, vars);
    return (0);
}