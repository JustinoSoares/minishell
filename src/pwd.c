/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 15:49:13 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_variables *vars)
{
	char	pwd[1024];

	if (vars->args[1] == NULL)
	{
		if (getcwd(pwd, sizeof(pwd)) != NULL)
			printf("%s\n", pwd);
	}
	else
		printf("pwd: can't have argument\n");
}

void	ft_exit(t_variables *vars, t_words **words)
{
	int		i;
	char	*str;
	int		out;

	i = 0;
	str = vars->args[1];
	if (str != NULL && ft_strlen(str) != 0)
	{
		while (str[i] != '\0')
		{
			if (!ft_isdigit(str[i]))
			{
				printf("bash: exit: %s: numeric argument required\n", str);
				free_words(*words);
				exit(2);
			}
			i++;
		}
		out = ft_atoi(str);
	}
	else
		out = 0;
	printf("exit\n");
	free_words(*words);
	exit(out);
}
