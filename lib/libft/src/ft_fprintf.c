/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:27:51 by jpelline          #+#    #+#             */
/*   Updated: 2025/06/16 21:09:02 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(uintptr_t decimal, char conv, int fd, int p)
{
	int			i;
	char		hexadecimal[20];
	const char	*hex_table;

	if (!decimal && conv == 'p')
		return (write(fd, "(nil)", 5));
	if (decimal == 0)
		return (write(fd, "0", 1));
	if (conv == 'p')
		p = ft_putstr_fd("0x", fd);
	if (conv == 'x' || conv == 'p')
		hex_table = "0123456789abcdef";
	else
		hex_table = "0123456789ABCDEF";
	i = 0;
	while (decimal)
	{
		hexadecimal[i++] = hex_table[decimal & 0xF];
		decimal >>= 4;
	}
	hexadecimal[i] = '\0';
	ft_reverse_string(hexadecimal);
	ft_putstr_fd(hexadecimal, fd);
	return (i + p);
}

static int	ft_write_conversion(va_list *args, char conv, int fd)
{
	if (conv == 'c')
		return (ft_putchar_fd((char)va_arg(*args, int), fd));
	if (conv == 's')
		return (ft_putstr_fd(va_arg(*args, char *), fd));
	if (conv == 'p')
		return (ft_puthex((uintptr_t)va_arg(*args, void *), conv, fd, 0));
	if (conv == 'x' || conv == 'X')
		return (ft_puthex((unsigned)va_arg(*args, unsigned), conv, fd, 0));
	if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fd((int)va_arg(*args, int), fd));
	if (conv == 'u')
		return (ft_uputnbr_fd((unsigned)va_arg(*args, unsigned), fd));
	return (write(fd, "%", 1));
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	while (format[count])
		if (format[count++] == '%')
			if (!format[count] || !ft_strchr("cspxXdiu%", format[count++]))
				return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && format[1] && ft_strchr("cspxXdiu%", format[1]))
			count += ft_write_conversion(&args, *++format, fd);
		else
			count += write(fd, &*format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
