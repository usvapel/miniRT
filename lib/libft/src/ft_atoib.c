/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:00:56 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/24 21:56:30 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	check_input(const char *nptr, int sign, ssize_t result, int digit)
{
	int	check;

	check = false;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (sign == 1 && result > (INT_MAX - digit) / 10)
			return (false);
		if (sign == -1 && result > (-(long)INT_MIN - digit) / 10)
			return (false);
		result = result * 10 + digit;
		nptr++;
		check = true;
	}
	if ((*nptr < '0' || *nptr > '9') && *nptr && *nptr != '\0')
		return (false);
	if (!check)
		return (false);
	return (true);
}

bool	ft_atoib(const char *nptr)
{
	ssize_t	result;
	int		sign;
	int		digit;

	result = 0;
	digit = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\a' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	return (check_input(nptr, sign, result, digit));
}
