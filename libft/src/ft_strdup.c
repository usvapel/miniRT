/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:02:07 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:51 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dest;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, size + 1);
	dest[size] = '\0';
	return (dest);
}
