/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:38:42 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/27 15:53:57 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(t_pip *pip, char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	while (cmd1[i])
	{
		free(cmd1[i]);
		i++;
	}
	free(cmd1);
	i = 0;
	while (cmd2[i])
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd2);
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

void	pre_check_cmd(t_pip *pip)
{
	char	**cmd1;
	char	**cmd2;

	ft_path(pip);
	cmd1 = ft_split(pip->argv[2], ' ');
	cmd2 = ft_split(pip->argv[3], ' ');
	if (access(cmd1[0], X_OK) == 0)
	{
		return ;
	}
	if (access(cmd2[0], X_OK) == 0)
		return ;
	check_boucle(pip, cmd1);
	check_boucle(pip, cmd2);
	ft_free(pip, cmd1, cmd2);
}
