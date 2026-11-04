/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dd-alo <dd-alo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 19:24:44 by dd-alo            #+#    #+#             */
/*   Updated: 2026/10/26 17:33:58 by dd-alo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t			len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		ch;

	if (!s)
		return (NULL);
	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&(s[i]));
		i++;
	}
	if (s[i] == ch)
		return ((char *)&(s[i]));
	return (NULL);
}

char	*ft_append(const char *dst, const char *src, size_t len)
{
	char					*str;
	size_t					dst_len;
	size_t					i;
	size_t					j;

	if (!src && len > 0)
		return (NULL);
	dst_len = ft_strlen(dst);
	str = (char *)malloc(len + dst_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i != dst_len)
		str [j++] = dst[i++];
	i = 0;
	while (i < len)
		str[j++] = src[i++];
	str[j] = '\0';
	return (str);
}

int	ft_update_saved(char **saved, size_t len)
{
	char			*old_str;
	size_t			new_len;

	if ((*saved)[len] != '\0')
	{
		new_len = ft_strlen(*saved) - len;
		old_str = ft_append(NULL, *saved + len, new_len);
		if (!old_str)
			return (0);
		free(*saved);
		*saved = old_str;
	}
	else
	{
		free(*saved);
		*saved = NULL;
	}
	return (1);
}

char	*ft_take_line(char **saved)
{
	char		*new_str;
	size_t		len;

	if (!saved || !*saved)
		return (NULL);
	len = 0;
	if (!((*saved)[len]))
	{
		free(*saved);
		*saved = NULL;
		return (NULL);
	}
	while ((*saved)[len] != '\n' && (*saved)[len] != '\0')
		len++;
	if ((*saved)[len] == '\n')
		len++;
	new_str = ft_append(NULL, *saved, len);
	if (!new_str)
		return (NULL);
	if (ft_update_saved(saved, len) == 0)
	{
		free(new_str);
		return (NULL);
	}
	return (new_str);
}
