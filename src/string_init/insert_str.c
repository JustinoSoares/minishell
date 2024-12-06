/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:35:31 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/04 16:35:47 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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