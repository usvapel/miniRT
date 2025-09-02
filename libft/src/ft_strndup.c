/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erantala <erantala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:41:00 by erantala          #+#    #+#             */
/*   Updated: 2025/06/19 03:20:48 by erantala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t n)
{
	size_t	pos;
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	pos = 0;
	len = ft_strlen(s);
	if (len > n)
		dup = malloc(sizeof(char) * n + 1);
	else
		dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (s[pos] && pos < n)
	{
		dup[pos] = s[pos];
		pos++;
	}
	dup[pos] = '\0';
	return (dup);
}
