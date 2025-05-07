/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:15:53 by mg                #+#    #+#             */
/*   Updated: 2024/10/08 15:28:32 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_putchar(int c);
int	ft_putstr_opti(char *str);

int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_digit(int nb);
int	ft_print_hex_min(unsigned long num);
int	ft_print_hex_maj(unsigned long num);
int	ft_print_unsigned(unsigned int nb);
int	ft_print_adresse(void *ptr);

int	ft_check_string(const char *type, va_list ap);
int	ft_type_trouver(const char *type, va_list ap);
int	ft_printf(const char *format, ...);

#endif