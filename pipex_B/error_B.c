/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_B.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:39:02 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/27 17:53:44 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_B.h"

void	err_argv(void)
{
	write(2, "Usage : ./pipex  infile \"cmd1\" \"cmd2\" outfile", 46);
	exit(1);
}

void	err_envp(void)
{
	write(2, "No environment found", 21);
	exit(1);
}

void	err_path(void)
{
	write(2, "path not found", 15);
	exit(1);
}

void	err_cmd(char *cmd)
{
	write(2, "command not found: ", 20);
	write(2, cmd, ft_strlen(cmd));
	exit(1);
}

void	err_file(char *file)
{
	write(2, "file not found: ", 20);
	write(2, file, ft_strlen(file));
	exit(1);
}
