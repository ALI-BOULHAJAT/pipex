/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulhaj <aboulhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:30:25 by aboulhaj          #+#    #+#             */
/*   Updated: 2022/03/31 13:45:20 by aboulhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_B.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	l_s;
	int		i;

	l_s = ft_strlen((char *)s1);
	str = malloc((l_s + 1) * sizeof (char));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s1[i] && l_s)
	{
		str[i] = (char)s1[i];
		l_s--;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char	buff[1];
	char	line[1000000];
	int		i;
	int		n;

	line[0] = 0;
	i = 0;
	if (fd < 0)
		return (NULL);
	n = read(fd, buff, 1);
	while (n > 0)
	{
		line[i++] = buff[0];
		line[i] = '\0';
		if (buff[0] == '\n')
			return (ft_strdup(line));
		n = read(fd, buff, 1);
	}
	if (!line[0])
		return (NULL);
	return (ft_strdup(line));
}
