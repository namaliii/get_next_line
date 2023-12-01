/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:57:19 by anamieta          #+#    #+#             */
/*   Updated: 2023/12/01 12:49:22 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*constr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	constr = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
			sizeof(char));
	if (constr == NULL)
		return (NULL);
	while (s1[i])
	{
		constr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		constr[i] = s2[j];
		i++;
		j++;
	}
	return (constr);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (!(unsigned char)c && !*s)
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	totalsize;
	size_t	i;
	void	*ptr;

	i = 0;
	totalsize = count * size;
	ptr = malloc(totalsize);
	if (!ptr)
		return (NULL);
	while (i < totalsize)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
