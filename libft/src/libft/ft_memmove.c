/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:40:35 by mg                #+#    #+#             */
/*   Updated: 2024/08/16 11:49:13 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*uc_dst;
	const unsigned char	*uc_srce;

	if ((!dest || !src) && len > 0)
		return (NULL);
	uc_dst = (unsigned char *)dest;
	uc_srce = (const unsigned char *)src;
	if (uc_dst > uc_srce)
	{
		while (len--)
			uc_dst[len] = uc_srce[len];
	}
	else
	{
		while (len--)
		{
			*uc_dst++ = *uc_srce++;
		}
	}
	return (dest);
}
