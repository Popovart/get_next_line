/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitrii <dmitrii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:24:35 by dmitrii           #+#    #+#             */
/*   Updated: 2024/11/18 13:47:03 by dmitrii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "stdio.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dest = (char *)malloc(1);
		if (!dest)
			return (NULL);
		return (dest[0] = '\0', dest);
	}
	if (len > s_len - start)
		len = s_len - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	return (dest[i] = '\0', dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_get_dirty_line(int fd, char **reminder, char *buffer)
{
	ssize_t	bts_read;
	char	*temp;

	while (1)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read == -1)
			return (free(*reminder), *reminder = NULL, NULL);
		if (bts_read == 0)
			break ;
		buffer[bts_read] = '\0';
		if (!(*reminder))
			*reminder = ft_strdup("");
		temp = *reminder;
		*reminder = ft_strjoin(*reminder, buffer);
		free(temp);
		if (!(*reminder))
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*reminder);
}

char	*ft_get_reminder(char **line)
{
	char	*new_line_pos;
	char	*temp;
	char	*reminder;

	new_line_pos = ft_strchr(*line, '\n');
	if (new_line_pos)
	{
		temp = *line;
		*line = ft_substr(*line, 0, new_line_pos - *line + 1);
		reminder = ft_strdup(new_line_pos + 1);
		free(temp);
		if (*reminder == '\0')
			return (free(reminder), NULL);
		return (reminder);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*reminder[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(reminder[fd]);
		reminder[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = ft_get_dirty_line(fd, &reminder[fd], buffer);
	free(buffer);
	if (!line)
		return (NULL);
	reminder[fd] = ft_get_reminder(&line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("test.txt", O_RDWR);
// 	if (fd < 0)
// 	{
// 		printf("Error opening file\n");
// 		return (1);
// 	}
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

// int main() {
//     int fd = open("test.txt", O_RDONLY);
//     char *line;

//     while ((line = get_next_line(fd)) != NULL) {
//         printf("Line: %s", line);
//         free(line);
//     }

//     line = get_next_line(fd);
//     if (line == NULL) {
//         printf("End of file reached correctly.\n");
//     } else {
//         printf("Unexpected result: %s\n", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }
