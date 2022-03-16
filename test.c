/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:48:13 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/08 15:22:15 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int i, j;
    
    i = fork();
    //j = fork();
    if (i == 0 && j == 0)
    {
        j = fork();
        printf("i = %d    j = %d  --hello\n", i, j);
    }
    printf("par\n");
    
    return (0);
}