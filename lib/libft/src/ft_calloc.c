/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:02:11 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/05 13:53:49 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;
	size_t			total;
	size_t			i;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	tmp = malloc(total);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i + 3 < total)
	{
		tmp[i] = 0;
		tmp[i + 1] = 0;
		tmp[i + 2] = 0;
		tmp[i + 3] = 0;
		i += 4;
	}
	while (i < total)
		tmp[i++] = 0;
	return (tmp);
}
