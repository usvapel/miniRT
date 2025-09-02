/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:08:15 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/28 17:23:17 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_itod(int n)
{
	if (n > 9)
	{
		ft_itod(n / 10);
		n = n % 10;
	}
	return (n + '0');
}

static int	ft_intlen(int n)
{
	size_t	temp;
	size_t	i;

	i = 0;
	temp = 0;
	if (n == INT_MIN)
		return (10);
	if (n < 0)
	{
		temp = -n;
		i++;
	}
	else
		temp = n;
	while (temp > 9 && i <= (size_t)n)
	{
		temp /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*result;
	int		neg;

	neg = 0;
	i = ft_intlen(n) + 1;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	if (n == INT_MIN)
		return (ft_strlcpy(result, "-2147483648", 12), result);
	result[i] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		if (n < 0 && i--)
			n = -n;
		neg = 1;
	}
	while (i--)
	{
		result[i + neg] = ft_itod(n);
		n /= 10;
	}
	return (result);
}
