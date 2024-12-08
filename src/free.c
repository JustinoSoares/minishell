/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:15:58 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/08 06:14:48 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_matriz(char **matriz)
{
    int i = 0;
    while(matriz[i])
    {
        free(matriz[i]);
        i++;
    }
    free(matriz);
}

void free_words(t_words *words)
{
    t_words *tmp;
    while (words)
    {
        tmp = words;
        words = words->next;
        free(tmp->word);
        free(tmp);
    }
}