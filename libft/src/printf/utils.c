/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontion_print_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:00:42 by mg                #+#    #+#             */
/*   Updated: 2024/10/08 15:12:31 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	ft_putchar(c);
	return (1);
}

int	ft_print_str(char *str)
{
	int	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

int	ft_print_digit(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		count += ft_print_digit(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_print_hex_min(unsigned long num)
{
	int		count;
	char	*hex_digits;

	count = 0;
	hex_digits = "0123456789abcdef";
	if (num >= 16)
		count += ft_print_hex_min(num / 16);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}

int	ft_print_hex_maj(unsigned long num)
{
	int		count;
	char	*hex_digits;

	count = 0;
	hex_digits = "0123456789ABCDEF";
	if (num >= 16)
		count += ft_print_hex_maj(num / 16);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}
