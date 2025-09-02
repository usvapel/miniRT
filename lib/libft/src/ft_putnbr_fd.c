/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:57 by jpelline          #+#    #+#             */
/*   Updated: 2025/04/29 18:47:04 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	size_t	count;

	count = 0;
	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		count += ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		count += ft_putnbr_fd(n / 10, fd);
		count += ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		count += ft_putchar_fd(n + '0', fd);
	}
	return (count);
}
