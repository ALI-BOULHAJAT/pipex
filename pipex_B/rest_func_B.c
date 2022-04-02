/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_func_B.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:55:49 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/04/02 11:56:04 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_B.h"

static void	ft_free(t_pip *pip)
{
	int	i;

	i = 0;
	while (pip->pre_var[i])
	{
		free(pip->pre_var[i]);
		i++;
	}
	free(pip->pre_var);
}

static void	check_boucle(t_pip *pip, char **cmd)
{
	char	*pre_join;
	int		j;
	int		ok;

	ok = 1;
	j = 0;
	while (pip->pre_var[j])
	{
		pre_join = ft_strjoin(pip->pre_var[j], "/");
		pip->var = ft_strjoin(pre_join, cmd[0]);
		free(pre_join);
		ok = access(pip->var, X_OK);
		if (ok == 0)
		{
			free(pip->var);
			break ;
		}
		j++;
		free(pip->var);
	}
	if (ok)
		err_cmd(cmd[0]);
}

void	pre_check_cmd(t_pip *pip, int n)
{
	char	**cmd;
	int		x;
	int		i;

	x = 1;
	ft_path(pip);
	while (x <= pip->n_cmd)
	{
		cmd = ft_split(pip->argv[x + n], ' ');
		if (cmd[0] == NULL)
			err_cmd("");
		if (access(cmd[0], X_OK) == 0)
			return ;
		check_boucle(pip, cmd);
		i = 0;
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		x++;
	}
	ft_free(pip);
}

void	ft_heredoc(t_pip *pip)
{
	char	*input;

	pip->n_cmd -= 4;
	pre_check_cmd(pip, 2);
	pip->infile = open(".infile", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 1);
		input = get_next_line(0);
		if (!ft_strcmp(input, ft_strjoin(pip->argv[2], "\n")))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, pip->infile);
		free(input);
	}
	close (pip->infile);
	pre_child_hdoc(pip);
}

void	pre_child_hdoc(t_pip *pip)
{
	int	x;
	int	last;

	x = 1;
	last = pip->n_cmd + 3;
	pip->infile = open(".infile", O_RDONLY, 0777);
	pip->outfile = open(pip->argv[last], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pip->outfile < 0 || pip->infile < 0)
		err_file(pip->argv[1]);
	while_cmd(pip, 1);
}
