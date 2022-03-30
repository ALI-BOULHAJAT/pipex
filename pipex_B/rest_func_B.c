/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_func_B.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:55:49 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/30 15:35:17 by aboulhaj         ###   ########.fr       */
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

void	pre_check_cmd(t_pip *pip)
{
	char	**cmd;
	int		x;
	int		i;

	x = 1;
	ft_path(pip);
	while (x <= pip->n_cmd)
	{
		cmd = ft_split(pip->argv[x + 1], ' ');
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
