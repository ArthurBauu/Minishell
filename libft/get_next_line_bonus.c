/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:54:03 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/22 17:38:52 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_buff(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	if (buffer)
		free (buffer);
	return (temp);
}

char	*ft_next(char *buff)
{
	int		i;
	int		j;
	char	*l;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	l = ft_calloc((ft_strplen(buff) - i), sizeof(char));
	if (!l)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		l[j++] = buff[i++];
	free(buff);
	return (l);
}

char	*ft_line_to_display(char *buff)
{
	char	*l;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	l = ft_calloc(i + 2, sizeof(char));
	if (!l)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		l[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		l[i++] = '\n';
	return (l);
}

char	*readf(int fd, char *res)
{
	char	*buff;
	int		b_read;

	if (!res)
		res = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(res);
			free(buff);
			return (NULL);
		}
		buff[b_read] = '\0';
		res = ft_free_buff(res, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	*str[1024];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	str[fd] = readf(fd, str[fd]);
	if (!str[fd] || str[fd] == NULL)
		return (NULL);
	out = ft_line_to_display(str[fd]);
	str[fd] = ft_next(str[fd]);
	return (out);
}
