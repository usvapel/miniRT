/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:09 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:30 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buff;
	int		i;

	if (!s || !f)
		return (NULL);
	buff = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!buff)
		return (NULL);
	i = 0;
	while (s[i])
	{
		buff[i] = (*f)(i, s[i]);
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
