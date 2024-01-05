/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:30:34 by bposa             #+#    #+#             */
/*   Updated: 2023/12/23 15:39:55 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_putnbr(int n, int *err)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		*err = write(1, "-2147483648", 11 * sizeof(char));
		return (*err);
	}
	else if (n < 0)
	{
		n *= -1;
		*err = write(1, "-", sizeof(char));
		if (*err == -1)
			return (-1);
		count++;
	}
	if (n >= 10)
	{
		count += my_putnbr(n / 10, err);
	}
	if (*err != -1)
		*err = write(1, &"0123456789"[n % 10], sizeof(char));
	count++;
	return (count);
}
