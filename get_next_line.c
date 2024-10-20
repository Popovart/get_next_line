/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitrii <dmitrii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:24:35 by dmitrii           #+#    #+#             */
/*   Updated: 2024/10/20 19:12:22 by dmitrii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

#define BUFFER_SIZE 42

char	*ft_get_line(int fd, char *buffer)
{
	char	*end_line;
	int		bytes_read;
	char	*line;

	end_line = NULL;
	while (!end_line)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0) // с концом файла будут проблемы
			return (NULL);
		line = ft_strjoin(line, buffer);
		end_line = ft_strrchr(buffer, '\n');
	}
	return (line);
}


char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	size_t		line_len;
	static char	remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_line(fd, buffer);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	line_len = ft_strrchr(buffer, '\n') - buffer + 1;
	return (ft_substr(buffer, 0, line_len));
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
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
