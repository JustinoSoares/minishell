/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:00 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/09 08:28:53 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_IN 1024
# define MAX_ARGS 100
# define MAX_PATH 256

extern int				g_status_signal;

typedef struct s_array
{
	int					count;
	struct s_array		*next;
}						t_array;

typedef struct s_words
{
	char				*word;
	int					type;
	struct s_words		*next;
}						t_words;

typedef struct s_tokens
{
	char				*token;
	int					type;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	char				*value;
	char				*key;
	char				**env;
	char				**env_copy;
	int					len;
	int					found;
	int					just_var;
	int					i;
	int					j;
}						t_env;

typedef struct s_extented
{
	char				*str;
	char				*macro;
	char				*word;
	char				*word_empty;
	char				*getter;
	char				*expanded_word;
	int					i;
	int					j;
	int					size;
}						t_extented;

typedef struct s_variables
{
	int					status_command;
	int					prev_fd;
	int					fd;
	char				*files_out[100];
	char				*files_in[100];
	char				*cmd_args[100];
	int					index;
	int					redir_found;
	int					quant;
	int					count_out;
	int					count_in;
	int					redir_here_doc_found;
	int					redir_greater_found;
	int					redir_lesser_found;
	int					saved_std;
	char				*line;
	char				*type_redir;
	char				*last_redir_type;
	char				**args;
	char				**env;
	pid_t				pid;
	t_extented			*ext;
	t_env				*ev;
	t_words				*words;
	struct s_variables	*next;
}						t_variables;

int						count_elements(char *str, char c);
int						count_until(char *str, char c, int index);
int						get_last_in(char *str, char c, int index);
int						is_in(char *str, char c, int index);
int						is_in_aspas(char *str, int index);
int						is_contra_barra(char *str, int i);
void					ft_echo(t_variables *vars);
int						start_write(char *str, char *command);
int						new_line(char *str);
void					ft_exec_functions(t_variables *vars, t_words **words);
void					free_matriz(char **matriz);
int						aspas_error(char *str, int show_error);
char					*find_executable(char *command);
int						print_var(char *str, int i);
char					**ft_split_aspa(char const *s, char c);

void					env(t_env *ev, t_variables *vars);
void					unset(char *key, t_env *ev);
void					ft_pwd(t_variables *vars);
void					ft_exit(t_variables *vars, t_words **words);

void					ft_cd(t_variables *vars);
void					ctrl_c(int sig);

void					set_values(t_env *ev, char *var, int i, int j);
void					set_env(char *key, t_env *ev);
void					get_variable(t_env *ev, t_words **words);
void					export(t_env *ev, char *var, char *value);
void					fill_env(t_env *ev, char **envp);
char					*ft_strcat_index(char *str, char *str2, int index);
int						is_duplas(char *str, int i);
char					*get_word(char *str, int start);
int						get_last_in(char *str, char c, int index);
int						is_in_aspas(char *str, int index);
char					*get_word(char *str, int start);

char					**ft_split_aspa(char const *s, char c);

int						size_expanded(char *str, t_variables *vars);
char					*is_expanded(char *str, t_variables *vars);
char					*get_word_d(char *str, int start);
char					*get_word_s(char *str, int start);
char					*get_word_empty(char *str, int start);
void					insert_str_end(t_words **array, char *word, int type);
char					*filter_string(char *str, t_variables *vars,
							t_words **words);

void					free_words(t_words *words);

void					function_pipe(t_variables *vars, t_words **words);
void					function_redir(t_variables *vars, t_words **words);

void					set_values(t_env *ev, char *var, int i, int j);

int						count_key_value(char *var, int identify);
int						ft_strcmp(char *s1, char *s2);
void					token_redir(t_words **words, t_variables *vars);

char					*get_key(char *env);

int						ft_empty(char *str, t_words **array, int i,
							t_variables *vars);
int						insert_redirect(char *str, t_words **array, int i);
char					*ft_get_env(char *key, t_env *env);
char					*aux_expanded(char *str, char *getter,
							t_variables *vars, int j);
void					execute(t_variables *vars, t_words **words);
int						count_key_value(char *var, int identify);
char					*ft_key(char *var);
char					*ft_value(char *var, int pos_value);
int						form_word_empty(char *str, t_variables *vars,
							t_words **array, int i);
void					get_elements(char *str, t_words **words,
							t_variables *vars);

void					new_prompt(int signal);
void					process_child(char *command_path, t_variables *vars);
void					process_parent(t_variables *vars);
void					function_no_built(t_variables *vars);
void					ft_exec_functions(t_variables *vars, t_words **words);
int						count_pipes(t_words *words);
char					**aux_split_pipe(t_words *word, char c, char **line,
							char *new);
void					init_process(t_variables *vars, int fd[2], char **args,
							t_words **words);
char					**split_pipe(t_words **words, char c);
char					**init_pipe(t_words **words, t_variables *vars);
char					*form_word(t_words *word, char *new, char *tmp);
void					other_func(t_variables *vars, char *command);
void					remove_space(char *str, char ch);
void					clean_cmd(t_variables *vars);
void					token_file_in(t_words **words, t_variables *vars);
void					redir_in(t_variables *vars, char *command);
void					token_file_out(t_words **words, t_variables *vars);
void					redir_out(t_variables *vars, char *command);
void					init_vars(t_variables *vars);
int						open_file(char *file, char *redir_type);
void					token_cmd_args(t_words **words, t_variables *vars);
void					execute_redir(char *command, t_variables *vars,
							int std);
int						index_of(char *str, char *word);
int						here_doc(const char *file);

int						start_write(char *str, char *command);
void					init_ev(t_env *ev);
void					free_env(t_env *ev);
void					free_error(char *read, t_words *words,
							t_variables *vars);
void					init_variables(t_variables *vars);

char	**free_args(t_variables *vars);
char *get_args(char **args);
char *ft_has_substr(char *str, char *substr, int n);
void	redirect_error(char *str, t_variables *vars, t_words **words);

#endif
