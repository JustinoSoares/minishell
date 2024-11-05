/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/06 00:04:48 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int index_of(char *str, char *word)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (strncmp(str + i, word, strlen(word)) == 0)
            return (i + strlen(word) -1);
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

void ft_echo(char *str)
{
    if (count_elements(str, '"') % 2 != 0 || count_elements(str, 92) % 2 != 0)
    {
        write(1, "Error: invalid number of quotes\n", 32);
        return;
    }
	while (*str && *str != '|' && *str != ';' && *str != '>' && *str != '<')
	{
		if (*str == 92 && *(str + 1) == '"')
			str++;
        else if (*str == '"' && *(str - 1) != 92)
            str++;
		else
			write(1, str++, 1);
	}
    write(1, "\n", 1);
}

void ft_get_terminal(void)
{
    char *line;
    char **args;
    signal(SIGINT, ctrl_c); //quando o usuário aperta ctrl+c
    signal(SIGQUIT, ctrl_c); //quando o usuário aperta ctrl+
    while (true)
    {
        line = readline("\033[1;32mroot@minishell\033[m:~$ ");
        if (!line || strcmp(line, "exit") == 0)
            break;
        args = ft_split(line, ' ');
        if (args[0] && strcmp(args[0], "echo") == 0)
            ft_echo(line + start_write(line, "echo"));
        add_history(line);
        write_history("history");
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_get_terminal();
    return (0);
}