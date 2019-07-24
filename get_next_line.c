/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:14:30 by fprevela          #+#    #+#             */
/*   Updated: 2019/03/19 21:18:03 by fprevela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int						update(int fd, char **file)
{
	char				*buff;
	char				*wait;
	int					i;

	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	i = read(fd, buff, BUFF_SIZE);
	if (i > 0)
	{
		buff[i] = '\0';
		wait = ft_strjoin(*file, buff);
		free(*file);
		*file = wait;
	}
	free(buff);
	return (i);
}

int						get_next_line(const int fd, char **line)
{
	int					i;
	static char			*file = NULL;
	char				*nl;

	if ((!file && !(file = ft_strnew(0))) || !line || fd < 0 ||
			BUFF_SIZE < 1 || fd > 4864)
		return (-1);
	nl = ft_strchr(file, '\n');
	while (!nl)
	{
		i = update(fd, &file);
		if (i == 0)
		{
			if (ft_strlen(file) == 0)
				return (0);
			file = ft_strjoin(file, "\n");
		}
		if (i < 0)
			return (-1);
		else
			nl = ft_strchr(file, '\n');
	}
	*line = ft_strsub(file, 0, (ft_strlen(file) - ft_strlen(nl)));
	file = ft_strdup(nl + 1);
	return (1);
}
