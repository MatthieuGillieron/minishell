/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:01:02 by mg                #+#    #+#             */
/*   Updated: 2025/02/12 22:54:33 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

char		*extract_line(char *str);
char		*next_in_stash(char *stash);
char		*get_next_line(int fd);

size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *src, int i);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);

#endif