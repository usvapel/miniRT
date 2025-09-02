/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:01:17 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:42 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		dst_len = size;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < size - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
