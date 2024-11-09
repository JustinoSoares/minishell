/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/09 18:47:16 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Esta func pega as env e organiza elas em ordem alfabetica baseadas no valor da tabela ASCII
static void    sort_env(char **env)
{
    int i;
    int n;
    int j;
    char    *temp;
    
    i = 0;
    n = 0;
    while (env[n] != NULL)
            n++;
    while (i < n-1)
    {
        j = 0;
        while (j < n-i-1)
        {
            if (strcmp(env[j], env[j+1]) > 0)
            {
                temp = env[j];
                env[j] = env[j+1];
                env[j+1] = temp;
            }
            j++;
        }
        i++;
    }
}

//Está Funcao pega o argumento e divide em Key e Value
//OBS: Ainda precisa ser optimizada.
static void    get_variable(t_env  *ev, char *var)
{
    int i;
    int j; 

    i = 0;
    j = 0;
    ev->key = malloc(sizeof(char) * ft_strlen(var) + 1);
    ev->value = malloc(sizeof(char) * ft_strlen(var) + 1);
    while(var[i] != '=')
    {
        ev->key[i] = var[i];
        i++;
    }
    ev->key[i] = '\0';
    i++;
    while (var[i] != '\0')
    {
        ev->value[j++] = var[i];
        i++;
    }
    ev->value[j] = '\0';
}
//Está Funcao pega no arg e verifica se a key é uma var presente nas env,  
//se for, vai substituir o valor da var pelo valor que foi passado no arg. 
//OBS: Falta dar tratamento para casos em que o value dado no arg é Nullo.
static void  replace_env(char *key, t_env *ev)
{
    int  i;
    int  j;
    char    *tmp;

    i = 0;
    tmp = malloc(sizeof(char) * ft_strlen(key) + 1);
    while (ev->env[i] != NULL)
    {
        j = 0;
        while (ev->env[i][j] != '=')
        {
            tmp[j] = ev->env[i][j];
            j++;
        }
        tmp[j] = '\0';
        if (strcmp(tmp, key) == 0)
        {
            j++;
            int n = 0;
            while (ev->env[i][j] != '\0')
            {
                ev->env[i][j] = ev->value[n++];
                j++;
            }
        }   
        i++;
    }
}
//A func Export, imprime as env em ordem se nao for dado um arg.
//Se for dado um arg, verificamos se o arg dado é uma variavel 
//com valor para ser exportado nas env ou substituir o valor de alguma env.
void    export(t_env *ev, char *var)
{
    int i;

    i = 0;
    if (var == NULL || ft_strlen(var) == 0)
    {
        sort_env(ev->env);
        while (ev->env[i] != NULL)
        {
            printf("declare -x ");
            printf("%s\n", ev->env[i]);
            i++;
        }
    }
   else
   {
       get_variable(ev, var);
       replace_env(ev->key, ev);
   }
}
