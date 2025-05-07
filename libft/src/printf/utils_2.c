/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_print_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:10:05 by mg                #+#    #+#             */
/*   Updated: 2024/10/08 15:19:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb > 9)
		count += ft_print_unsigned(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_print_adresse(void *ptr)
{
	unsigned long	adresse;
	int				count;

	adresse = (unsigned long)ptr;
	count = 0;
	count += ft_putstr_opti("0x");
	count += ft_print_hex_min(adresse);
	return (count);
}
