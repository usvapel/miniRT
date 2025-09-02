/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:54:35 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:21:43 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_cmpcharset(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

static char	*ft_find_charset(const char *s1, const char *set)
{
	char	*buffer;
	size_t	i;
	size_t	j;
	size_t	set_size;
	size_t	size;

	size = ft_strlen(s1);
	set_size = 0;
	j = 0;
	i = size - 1;
	while (s1[j] && ft_cmpcharset(s1[j], set))
	{
		set_size++;
		j++;
	}
	while (s1[j] && ft_cmpcharset(s1[i--], set))
		set_size++;
	buffer = malloc(size - (set_size - 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (s1[j] && i < (size - set_size))
		buffer[i++] = s1[j++];
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;

	if (!s1 || !set)
		return (NULL);
	result = ft_find_charset(s1, set);
	return (result);
}
