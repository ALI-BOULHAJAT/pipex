/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:33:39 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/04 12:51:45 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int i;
    int j;
    char **pre_var;
    char *var;
    int ok;
    char **comd;
    int exc;
    int fd[2];
    //int file = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC);
    i = 0;
    if (ac == 2)
    {
        comd = ft_split(av[1], ' ');
        while(envp[i])
        {
            //printf("%s\n", envp[i]);
            if (ft_strnstr(envp[i],"PATH",ft_strlen(envp[i])))
            {
                j = 0;
                pre_var = ft_split((ft_strtrim(envp[i],"PATH=")), ':');
                while (pre_var[j])
                {
                    var = ft_strjoin(ft_strjoin(pre_var[j], "/"),"ls");
                    ok = access(var, X_OK);
                    //printf("%d ---- %s \n", ok, var);
                    if (ok == 0)
                    {
                        dup2(fd[0], 1);
                        execve(var, comd, envp);
                    }
                    //printf("%s  , %d\n", var, ok);
                    free (pre_var[j]);
                    j++;
                }
            }
            i++;
        }
    }
    return (0);
}

