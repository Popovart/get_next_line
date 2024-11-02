/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitrii <dmitrii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:24:35 by dmitrii           #+#    #+#             */
/*   Updated: 2024/11/02 14:14:24 by dmitrii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int	ft_is_end(char *buffer, int bytes_read)
{
	int	i;

	i = 0;
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_dirty_line(int fd, char *buffer, char *reminder)
{
	ssize_t	bytes_read;
	char	*dirty_line;
	char	*temp;

	if (reminder)
		dirty_line = ft_strdup(reminder);
	else
		dirty_line = ft_strdup("");
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(dirty_line), NULL);
		buffer[bytes_read] = '\0';
		temp = dirty_line;
		dirty_line = ft_strjoin(dirty_line, buffer);
		if (!dirty_line)
			return (NULL);
		free(temp);
		if (ft_strrchr(buffer, '\n') || bytes_read == 0)
			break ;
	}
	return (dirty_line);
}

char	*ft_get_clean_line(char *dirty_line, char **clean_line)
{
	char	*new_line_pos;

	new_line_pos = ft_strrchr(dirty_line, '\n');
	if (new_line_pos)
	{
		*clean_line = ft_strndup(dirty_line, new_line_pos - dirty_line + 1);
		return (ft_strdup(new_line_pos + 1));
	}
	*clean_line = ft_strdup(dirty_line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*reminder;
	char		*dirty_line;
	char		*clean_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	dirty_line = ft_get_dirty_line(fd, buffer, reminder);
	if (!dirty_line)
		return (NULL);
	if (reminder)
		free(reminder);
	if (buffer)
		free(buffer);
	if (!dirty_line)
		return (NULL);
	reminder = ft_get_clean_line(dirty_line, &clean_line);
	if (dirty_line)
		free(dirty_line);
	return (clean_line);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDWR);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	str = get_next_line(fd);
	while (*str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
