/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:37:07 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/08 14:10:22 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

int count_until(char *str, char c, int index)
{
    int count = 0;
    int i = 0;
    while (i < index)
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int get_last_ocurrenc(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    int back = index;
    while (i < index)
    {
        if (str[i] == c)
            last = i;
        i++;
    }
    back = count_until(str, c, back);
    if (back % 2 != 0)
        return (last);
    return (-1);
}

int is_in_in(char *str, char in, char out, int index)
{
    if (get_last_ocurrenc(str, out, index) != -1)
        return (1);
}

int main()
{
   char str[100] = "\"hello world \"hello world\" \"hello world\" \"hello world\" \"hello world\"";

    printf("%d\n", get_last_ocurrenc(str, '"', 27));
}