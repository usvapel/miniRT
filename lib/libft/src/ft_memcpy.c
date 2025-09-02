/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:01:10 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 18:26:25 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tdest;
	unsigned char	*tsrc;

	if (!dest && !src)
		return (dest);
	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	while (n > 0)
	{
		*(tdest) = *(tsrc);
		tdest++;
		tsrc++;
		n--;
	}
	return (dest);
}
