/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:17:26 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/12 17:38:16 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_copy(const char *src)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!src)
		return (NULL);
	len = ft_strlen_gnl(src);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strchr_gnl(char *s, char c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (s[i] == c)
		return (&s[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	char	*joined;

	if (!s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup_copy(s2));
	joined = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_gnl(char const *src, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!src || start >= ft_strlen_gnl(src))
		return (ft_strdup_copy(""));
	if (len > ft_strlen_gnl(src + start))
		len = ft_strlen_gnl(src + start);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (src[start + i] && i < len)
	{
		res[i] = src[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
