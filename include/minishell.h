/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:00 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/17 13:09:04 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

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
#include "../libft/libft.h"

typedef struct s_env
{
    char    *value;
    char    *key;
    char    **env;
    char    **env_copy;
    int     len;
    int     found;
    int     just_var;
}   t_env;

void    env(t_env *ev, char *str);
void    export(t_env *ev, char *var);
void	get_variable(t_env *ev, char *var);
void	set_env(char *key, t_env *ev);
void    verfi_arg(t_env *ev);
void    copy_env(t_env *ev);
void    set_values(t_env *ev, char *var, int i, int j);
void    fill_env(t_env *ev, char **envp);
void	unset(char *key, t_env *ev);


#endif


