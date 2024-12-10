/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/09 12:17:31 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(void)
{
    char *str = "Justino Soares Mila 42";
    char *new;
    
    new = filter_string(str, NULL);

    printf("new: %s\n", new);
        
}