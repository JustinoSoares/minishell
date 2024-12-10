/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:00 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/10 12:24:39 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../libft/libft.h"

#define MAX_IN 1024
#define MAX_ARGS 100
#define MAX_PATH 256

extern int status_signal;

typedef struct s_array
{
    int count;
    struct s_array *next;
} t_array;

typedef struct s_words
{
    char *word;
    int type;
    struct s_words *next;
} t_words;

typedef struct s_tokens
{
    char *token;
    int type;
    struct s_tokens *next;
} t_tokens;

typedef struct s_env
{
    char *value;
    char *key;
    char **env;
    char **env_copy;
    int len;
    int found;
    int just_var;
    int i;
    int j;
} t_env;

typedef struct s_variables
{
    int status_command;
    int prev_fd;
    int index;
    int quant;
    char *line;
    char **args;
    char **env;
    pid_t pid;
    t_env *ev;
    t_words *words;
    struct s_variables *next;
} t_variables;

int count_elements(char *str, char c);
int count_until(char *str, char c, int index);
int get_last_in(char *str, char c, int index);
int is_in(char *str, char c, int index);
int is_in_aspas(char *str, int index);
int is_contra_barra(char *str, int i);
void ft_echo(t_variables *vars);
int start_write(char *str, char *command);
int new_line(char *str);
void ft_exec_functions(t_variables *vars);
void free_matriz(char **matriz);
int aspas_error(char *str, int show_error);
char *find_executable(char *command);
int print_var(char *str, int i);
char **ft_split_aspa(char const *s, char c);

void env(t_env *ev, t_variables *vars);
void unset(char *key, t_env *ev);
void ft_pwd(t_variables *vars);
void ft_exit(t_variables *vars);

void ft_cd(t_variables *vars);
void ctrl_c(int sig);

void set_values(t_env *ev, char *var, int i, int j);
void set_env(char *key, t_env *ev);
void get_variable(t_env *ev, char *var);
void verfi_arg(t_env *ev);
void	export(t_env *ev, char *var, char *value);
void copy_env(t_env *ev);
void fill_env(t_env *ev, char **envp);
char *ft_strcat_index(char *str, char *str2, int index);
int is_duplas(char *str, int i);
char *get_word(char *str, int start);
int get_last_in(char *str, char c, int index);
int is_in_aspas(char *str, int index);
char *get_word(char *str, int start);

char **ft_split_aspa(char const *s, char c);

int size_expanded(char *str);
char *is_expanded(char *str, t_variables *vars);
char *get_word_d(char *str, int start);
char *get_word_s(char *str, int start);
char *get_word_empty(char *str, int start);
void insert_str_end(t_words **array, char *word, int type);
void get_elements(char *str, t_words **array, t_variables *vars);
char *filter_string(char *str, t_variables *vars, t_words **words);

void free_words(t_words *words);

void function_pipe(t_variables *vars, t_words **words);

#endif
