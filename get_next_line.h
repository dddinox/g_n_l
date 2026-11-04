/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dd-alo <dd-alo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 19:24:51 by dd-alo            #+#    #+#             */
/*   Updated: 2026/10/26 17:33:57 by dd-alo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_storage
{
	size_t	len;
	size_t	capacity;
}	t_storage;

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_append(const char *dst, const char *src, size_t len);
int		ft_update_saved(char **saved, size_t len);
char	*ft_take_line(char **saved);
int		ft_read_until_line(int fd, char **saved, t_storage *storage);
char	*get_next_line(int fd);

#endif