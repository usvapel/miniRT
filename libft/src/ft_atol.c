/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erantala <erantala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:21:19 by erantala          #+#    #+#             */
/*   Updated: 2025/07/13 01:42:24 by erantala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow(long long nbr, int neg, int digit);

long	ft_atol(const char *nptr)
{
	long long	res;
	int			neg;

	res = 0;
	neg = 1;
	while (((*nptr) >= 9 && (*nptr) <= 13) || (*nptr) == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg *= -1;
		nptr++;
	}
	while ((*nptr) >= 48 && (*nptr) <= 57)
	{
		if (overflow(res, neg, (*nptr - '0')) != 2)
			return (overflow(res, neg, (*nptr - '0')));
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return ((res * neg));
}

static int	overflow(long long nbr, int neg, int digit)
{
	if (neg < 0)
	{
		nbr = -nbr;
		if (nbr < (LONG_MIN + digit) / 10)
			return (0);
	}
	if (neg > 0)
		if (nbr > (LONG_MAX - digit) / 10)
			return (0);
	return (2);
}
