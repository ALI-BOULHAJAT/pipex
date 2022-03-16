/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:44:27 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/16 14:01:44 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int i;
    int j;
    int z;
    char **pre_var;
    char *var;
    int ok;
    char **comd1;
    char **comd2;
    int fd[2];
    int infile;
    int outfile;
    pid_t id, id2;
    int Pid;
    int x = 1;
    i = 0;
    if (ac <= 5)
    {
        Pid = pipe(fd);
        infile = open(av[1], O_RDONLY, 0777);
        if (infile < 0)
            return (5);
        outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (outfile < 0)
            return (6);
        if (Pid >= 0)
        {
            while(envp[i])
            {
                if (ft_strnstr(envp[i],"PATH",ft_strlen(envp[i])))
                    pre_var = ft_split((ft_strtrim(envp[i],"PATH=")), ':');
                i++;
            }
            //free(pre_var);
            comd1 = ft_split(av[2], ' ');
            //free(comd1);
            id = fork();
            if (id == 0)
            {
                dup2(fd[1], 1);
                dup2(infile, 0);
                close(fd[1]);
                close(fd[0]);
                close (infile);
                j = 0;
                if (access(comd1[0], X_OK) == 0)
                {
                    execve(comd1[0], comd1, envp);
                }
                while (pre_var[j])
                {
                    var = ft_strjoin(ft_strjoin(pre_var[j], "/"),comd1[0]);
                    //free(var);
                    ok = access(var, X_OK);
                    if (ok == 0)
                        execve(var, comd1, envp);
                    //free(pre_var[j]);
                    j++;
                }
            }
            //free(pre_var[j]);
            comd2 = ft_split(av[3], ' ');
            //free(comd2);
            id2 = fork();
            if (id2 == 0)
            {
                dup2(fd[0], 0);
                dup2(outfile, 1);
                close(fd[1]);
                close(fd[0]);
                j = 0;
                if (access(comd2[0], X_OK) == 0)
                {
                    execve(comd2[0], comd2, envp);
                }
                while (pre_var[j])
                {
                    var = ft_strjoin(ft_strjoin(pre_var[j], "/"),comd2[0]);
                    //free(var);
                    ok = access(var, X_OK);
                    if (ok == 0)
                        execve(var, comd2, envp);
                    //free(pre_var[j]);
                    j++;
                }
            }
        }
    }
    //free (pre_var);
    
    close(fd[1]);
    close(fd[0]);
    //free(pre_var);
    waitpid(id, NULL, 0);
    //free(pre_var);
    waitpid(id2, NULL, 0);
    //while(1){}
    return (0);
}