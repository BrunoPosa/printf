/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:12:52 by bposa             #+#    #+#             */
/*   Updated: 2024/01/03 23:25:21 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_ch(char ch, int *err)
{
	return (*err = (int)write(1, &ch, sizeof(char)));
}

static int	my_putstr(char *s, int *err)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		*err = (int)write(1, "(null)", 6 * sizeof(char));
		return (*err);
	}
	while (s[i] != '\0' && *err != -1)
	{
		*err = (int)write(1, &s[i], sizeof(char));
		i++;
	}
	return ((int)i);
}

static int	unsign_nbr(unsigned int n, int *err)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += unsign_nbr(n / 10, err);
	}
	if (*err != -1)
		*err = write(1, &"0123456789"[n % 10], sizeof(char));
	if (*err == -1)
		return (-1);
	count++;
	return (count);
}

static int	specifier_sort(const char *fmt, int *err, va_list args, char *hex)
{
	if (*fmt == 'c')
		return (print_ch(va_arg(args, int), err));
	else if (*fmt == 's')
		return (my_putstr(va_arg(args, char *), err));
	else if (*fmt == 'p')
	{
		if (hex_prefix(err) == -1)
			return (-1);
		return (2 + put_hex((unsigned long int)va_arg(args, void *), err, hex));
	}
	else if (*fmt == 'd' || *fmt == 'i')
		return (my_putnbr(va_arg(args, int), err));
	else if (*fmt == 'u')
		return (unsign_nbr(va_arg(args, unsigned int), err));
	else if (*fmt == 'x')
		return (put_hex(va_arg(args, unsigned int), err, hex));
	else if (*fmt == 'X')
		return (put_hex(va_arg(args, unsigned int), err, "0123456789ABCDEF"));
	else if (*fmt == '%')
		return (*err = (int)write(1, "%", sizeof(char)));
	else
		return (*err = write(1, fmt, sizeof(char)));
}

int	ft_printf(const char *format, ...)
{
	int		rvalue;
	int		err_check;
	va_list	args;
	char	*hex;

	hex = "0123456789abcdef";
	va_start(args, format);
	rvalue = 0;
	err_check = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
			rvalue += (specifier_sort(++format, &err_check, args, hex));
		else if (*format == '%' && *(format + 1) == '\0')
			break ;
		else
			rvalue += ((err_check = (int)write(1, format, sizeof(char))));
		if (err_check == -1)
			break ;
		format++;
	}
	va_end(args);
	if (err_check == -1)
		return (-1);
	return (rvalue);
}
