/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_func_B2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:05:14 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/04/01 15:05:41 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_B.h"

void	while_cmd(t_pip *pip, int n)
{
	int	x;

	x = 1;
	while (x <= pip->n_cmd)
	{
		pip->p_id = pipe(pip->fd);
		if (pip->p_id >= 0)
		{
			pip->id = fork();
			if (x == pip->n_cmd)
				child(pip, pip->id, 2, x + n);
			else
				child(pip, pip->id, 1, x + n);
			pip->infile = dup(pip->fd[0]);
			close(pip->fd[1]);
			x++;
		}
	}
}

int	ft_close(t_pip *pip)
{
	close(pip->fd[1]);
	close(pip->fd[0]);
	waitpid(pip->id, NULL, 0);
	free(pip);
	return (0);
}
