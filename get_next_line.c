/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dd-alo <dd-alo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 19:24:47 by dd-alo            #+#    #+#             */
/*   Updated: 2026/10/26 17:33:55 by dd-alo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_error(char **saved, char *buffer)
{
	free(*saved);
	*saved = NULL;
	free(buffer);
	return (0);
}

static int	ft_reserve(char **saved, t_storage *storage, size_t needed)
{
	char	*new_str;
	size_t	capacity;
	size_t	i;

	if (needed <= storage->capacity)
		return (1);
	capacity = needed;
	if (needed <= (size_t)-1 / 2)
		capacity = needed * 2;
	new_str = malloc(capacity);
	if (!new_str)
		return (0);
	i = 0;
	while (i < storage->len)
	{
		new_str[i] = (*saved)[i];
		i++;
	}
	new_str[i] = '\0';
	free(*saved);
	*saved = new_str;
	storage->capacity = capacity;
	return (1);
}

static int	ft_save_chunk(char **saved, char *buffer, size_t bytes,
		t_storage *storage)
{
	size_t	i;
	size_t	needed;

	if (bytes > (size_t)-1 - storage->len - 1)
		return (0);
	needed = storage->len + bytes + 1;
	if (!ft_reserve(saved, storage, needed))
		return (0);
	i = 0;
	while (i < bytes)
	{
		(*saved)[storage->len + i] = buffer[i];
		i++;
	}
	storage->len += bytes;
	(*saved)[storage->len] = '\0';
	return (1);
}

int	ft_read_until_line(int fd, char **saved, t_storage *storage)
{
	char	*buffer;
	ssize_t	bytes;

	if (ft_strchr(*saved, '\n'))
		return (1);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (ft_read_error(saved, NULL));
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_read_error(saved, buffer));
		if (bytes == 0)
			break ;
		if (!ft_save_chunk(saved, buffer, (size_t)bytes, storage))
			return (ft_read_error(saved, buffer));
		if (ft_strchr(*saved + storage->len - (size_t)bytes, '\n'))
			break ;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	t_storage	storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_read_error(&saved, NULL);
		return (NULL);
	}
	storage.len = ft_strlen(saved);
	storage.capacity = storage.len + 1;
	if (!ft_read_until_line(fd, &saved, &storage))
		return (NULL);
	line = ft_take_line(&saved);
	if (!line)
	{
		free(saved);
		saved = NULL;
	}
	return (line);
}
