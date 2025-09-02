/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:01:27 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:05 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = ft_strlen(s);
	j = 0;
	while (i > 0)
	{
		if (s[i] == (char) c)
		{
			j = i;
			break ;
		}
		i--;
	}
	if (s[j] == (char) c || s[i] == (char) c)
		return ((char *) &s[j]);
	return (NULL);
}
