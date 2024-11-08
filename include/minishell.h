/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:00 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/08 15:56:33 by jsoares          ###   ########.fr       */
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


int count_elements(char *str, char c);
int count_until(char *str, char c, int index);
int get_last_in(char *str, char c, int index);
int is_in(char *str, char c, int index);
int is_in_in(char *str, char in, char out, int index);
int is_in_aspas(char *str, int index);
void ft_echo(char *str);
#endif


