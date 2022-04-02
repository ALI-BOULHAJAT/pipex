/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_B.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:39:41 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/04/01 15:02:18 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_B_H
# define PIPEX_B_H

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
	int		fdc;
	int		p_id;
	int		fd[2];
	int		id;
	int		id2;
	int		check_last;
	int		check;
	int		double_check;
	int		n_cmd;
	int		check_cmd;
}	t_pip;

void	ft_path(t_pip *pip);
void	child(t_pip *pip, int id, int check, int n_cmd);
void	pre_child(t_pip *pip);
void	err_argv(void);
void	err_envp(void);
void	err_path(void);
void	err_cmd(char *cmd);
void	err_file(char *file);
void	pre_check_cmd(t_pip *pip, int n);
void	ft_heredoc(t_pip *pip);
char	*get_next_line(int fd);
void	pre_child_hdoc(t_pip *pip);
void	while_cmd(t_pip *pip, int n);
int		ft_close(t_pip *pip);

#endif