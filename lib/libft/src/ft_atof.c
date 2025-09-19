/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:00:56 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/23 12:40:12 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_input(const char **nptr, int *neg)
{
	while (**nptr == ' ' || (**nptr >= '\a' && **nptr <= '\r'))
		(*nptr)++;
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*neg = -1;
		(*nptr)++;
	}
	if (**nptr == '0' && *(*nptr + 1) != '.')
		return (0);
	return (1);
}

static int	check_for_dots(const char *nptr, int *flag, int *floats)
{
	if (*nptr == '.')
		*flag += 1;
	if (*flag == 2)
		return (0);
	if (*flag == 1)
		(*floats)++;
	return (1);
}

float	ft_atof(const char *nptr)
{
	float	result;
	int		neg;
	int		floats;
	int		flag;

	result = 0;
	neg = 1;
	floats = 0;
	flag = 0;
	if (check_input(&nptr, &neg) == 0)
		return (0);
	while ((*nptr >= '0' && *nptr <= '9') || *nptr == '.')
	{
		if (check_for_dots(nptr, &flag, &floats) == 0)
			return (0);
		if (*nptr >= '0' && *nptr <= '9')
			result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
		return (0);
	while (--floats && flag == 1)
		result = result / 10;
	return ((float)(result *= neg));
}
