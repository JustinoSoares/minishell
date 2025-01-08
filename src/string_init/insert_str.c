/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:35:31 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 08:53:22 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void insert_str_end(t_words **word, char *str, int type)
{
    t_words *new;
    t_words *tmp;

    new = malloc(sizeof(t_words));
    if (!new || !str)
        return;
    new->word = strdup(str);
    new->type = type;
    new->next = NULL;
    if (*word == NULL)
        *word = new;
    else
    {
        tmp = *word;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
