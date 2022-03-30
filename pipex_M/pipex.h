/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:27:16 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/29 13:46:01 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>

typedef struct pip
{
	char	**comd1;
	char	**comd2;
	char	**pre_var;
	char	*var;
	char	**envp;
	char	**argv;
	char	*trim;
	int		infile;
	int		interfile;
	int		outfile;
	int		p_id;
	int		fd[2];
	int		id;
	int		id2;
	int		check_last;
	int		check;
	int		double_check;
}	t_pip;

void	ft_path(t_pip *pip);
void	child(t_pip *pip, int id, int check);
void	pre_child(t_pip *pip);
void	err_argv(void);
void	err_envp(void);
void	err_path(void);
void	err_cmd(char *cmd);
void	err_file(char *file);
void	pre_check_cmd(t_pip *pip);

#endif