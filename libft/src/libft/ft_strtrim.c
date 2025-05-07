/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:22:18 by mg                #+#    #+#             */
/*   Updated: 2024/08/18 11:47:45 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_str(char c, const char *check)
{
	int	i;

	i = 0;
	while (check[i])
	{
		if (c == check[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s2;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check_str(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && check_str(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	s2 = malloc(sizeof(char) * (end - start + 2));
	if (!s2)
		return (NULL);
	i = 0;
	while (start <= end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}
