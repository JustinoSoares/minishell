/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/09 21:13:11 by justinosoar      ###   ########.fr       */
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
		write(2, "PWD : Many Args\n", 16);
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
				write(2, "bash: exit: numeric argument is required\n", 40);
				write(2, "Command not found\n", 18);
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
