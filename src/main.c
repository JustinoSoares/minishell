/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/08 12:51:18 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int is_in(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    while (i < index)
    {
        if (str[i] == c)
            last++;
        i++;
    }
    if (last % 2 != 0)
        return (1);
    return (0);
}

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
    int start;
    start = index_of(str, command) + 1;
    while (*(str + start) == ' ')
        start++;
    return (start);
}

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
void ctrl_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = start;

    while (str[size] && str[size] != 32 && str[size] != '"' && str[size] != '\'')
        size++;
    new = malloc(sizeof(char) * (size) + 1);
    while (str[start] && str[start] != 32 && str[start] != '"' && str[start] != '\'')
        new[i++] = str[start++];
    new[i] = '\0';
    return (new);
}

void ft_echo(char *str)
{
    int i = 0;
    char *macro;
    if (count_elements(str, '"') % 2 != 0 || count_elements(str, '\'') % 2 != 0 || count_elements(str, 92) % 2 != 0)
    {
        write(1, "Error: invalid number of quotes\n", 32);
        return;
    }
    while (str[i] && str[i] != '|' && (str[i] != ';' || (str[i] == ';' && is_in(str, '"', i) == 1)) && str[i] != '>' && str[i] != '<')
    {
        if (str[i] == '$')
        {
            macro = getenv(get_word(str, i + 1));
            //printf("%s ", get_word(str, i + 1));
            if (macro && (((is_in(str, '"', i)) || is_in(str, '\'', i) == 0) || count_elements(str, '\'') == 0 ))
            {
                write(1, macro, ft_strlen(macro));
                i += ft_strlen(get_word(str, i));
            }
            else
                write(1, &str[i++], 1);
        }
        else if ((str[i] == '\'' && is_in(str, '"', i) == 1))
             write(1, &str[i++], 1);
        else if ((str[i] == 92 && str[i + 1] == '"') || (str[i] == 92 && str[i + 1] == '\''))
            i++;
        else if ((str[i] == '"' && str[i - 1] != 92) || (str[i] == '\'' && str[i - 1] != 92))
            i++;
        else
            write(1, &str[i++], 1);
    }
    write(1, "\n", 1);
}

void ft_cd(char *path)
{
    if (path == NULL || ft_strlen(path) == 0)
    {
        printf("cd: no such file or directory:\n");
        return ;
    }
    if (chdir(path) == -1)
    {
        printf("cd: no such file or directory: %s\n", path);
        return;
    }
}

void    ft_pwd(char *arg)
{
    char pwd[1024];

    if (!arg)
    {
        if (getcwd(pwd, sizeof(pwd)) != NULL)
            printf("%s\n", pwd);
    }
    else
        printf("pwd: can't have argument\n"); 
}

char    *find_key(char   **env, char *key)
{
    char    *tmp;
    int i;
    int j;

    tmp = malloc(sizeof(char) * ft_strlen(key));
    while (env[i] != NULL)
    {   
        j = 0;
        while (i < ft_strlen(key) && env[i][j] != '=')
        {
            tmp = env[i][j];
            i++;
        }
        if (tmp == key)
        {
            
        }
        
    }
    
}

/*void    export(char **env, char *key, char *value)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    
}*/

void ft_get_terminal(char **envp)
{
    char *line;
    char **args;
    char **env;

    env = envp;
    signal(SIGINT, ctrl_c);  // quando o usuário aperta ctrl+c
    signal(SIGQUIT, ctrl_c); // quando o usuário aperta ctrl+
    while (true)
    {
        line = readline("\033[1;32mroot@minishell\033[m:~$ ");
        if (!line || strcmp(line, "exit") == 0)
            break;
        args = ft_split(line, ' ');
        if (args[0] && strcmp(args[0], "echo") == 0)
            ft_echo(line + start_write(line, "echo"));
        else if (args[0] && strcmp(args[0], "cd") == 0)
            ft_cd(args[1]);
        else if (args[0] && strcmp(args[0], "pwd") == 0)
            ft_pwd(args[1]);
        else if (args[0] && strcmp(args[0], "export") == 0)
            export(env);
        add_history(line);
        write_history("history");
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_get_terminal(envp);
    return (0);
}