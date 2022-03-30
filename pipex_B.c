/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_B.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:41:55 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/30 12:20:20 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_B.h"

void	ft_path(t_pip *pip)
{
	int		i;
	char	*pre_var;
	int		check_path;

	i = 0;
	check_path = 1;
	while (pip->envp[i])
	{
		if (ft_strnstr(pip->envp[i], "PATH", ft_strlen(pip->envp[i])))
		{
			pre_var = ft_strtrim(pip->envp[i], "PATH=");
			pip->pre_var = ft_split(pre_var, ':');
			check_path = 0;
			free (pre_var);
		}
		i++;
	}
	if (check_path)
		err_path();
}

void	ft_dup(t_pip *pip, int check)
{
	dup2(pip->infile, 0);
	close(pip->fd[1]);
	close(pip->fd[0]);
	close (pip->infile);
	close(pip->outfile);
}

void	child(t_pip *pip, int id, int check, int n_cmd)
{
	int		j;
	char	**cmd;
	char	*pre_join;
	int		ac;

	ac = n_cmd + 1;
	if (id == 0)
	{
		ft_path(pip);
		ft_dup(pip, check);
		cmd = ft_split(pip->argv[ac], ' ');
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, pip->envp);
		j = 0;
		while (pip->pre_var[j])
		{
			pre_join = ft_strjoin(pip->pre_var[j], "/");
			pip->var = ft_strjoin(pre_join, cmd[0]);
			if (access(pip->var, X_OK) == 0)
				execve(pip->var, cmd, pip->envp);
			j++;
		}
	}
}

void	pre_child(t_pip *pip)
{
	int x;
	pre_check_cmd(pip);
	pip->infile = open(pip->argv[1], O_RDONLY, 0777);
	pip->outfile = open(pip->argv[pip->n_cmd + 2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pip->outfile < 0 || pip->infile < 0)
		err_file(pip->argv[1]);
	x = 1;
	while (x <= pip->n_cmd)
	{
		pip->p_id = pipe(pip->fd);
		if (pip->p_id >= 0)
		{
			pip->id = fork();
			if (x == pip->n_cmd)
				child(pip, pip->id, 2, x);
			else
			{
	
				child(pip, pip->id, 1, x);
				//pip->p_id = pipe(pip->fd);
				//close(pip->fd[0]);
				//close (pip->infile);
				// x++;
			}
			// }
		}
		pip->infile = pip->fd[0];
		// if (x < pip->n_cmd)
		// else if (x > 1 && x < pip->n_cmd)
		// {
		// 	child(pip, pip->id, 3, x);
		// 	x++;
		// }
		// //x++;
		close(pip->fd[1]);
		close(pip->fd[0]);
		waitpid(pip->id, NULL, 0);
		x++;
	}
	//}
}

int	main(int ac, char **av, char **envp)
{
	t_pip	*pip;
	int		i;

	pip = NULL;
	i = 0;
	if (ac >= 5)
	{
		if (!envp)
			err_envp();
		pip = (t_pip *)malloc(sizeof(t_pip));
		if (!pip)
			exit(1);
		pip->envp = envp;
		pip->argv = av;
		pip->n_cmd = ac - 3;
		pre_child(pip);
	}
	else
		err_argv();
	close(pip->fd[1]);
	close(pip->fd[0]);
	waitpid(pip->id, NULL, 0);
	// waitpid(pip->id2, NULL, 0);
	free(pip);
	return (0);
}
