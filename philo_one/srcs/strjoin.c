/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 17:09:21 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/16 21:22:33 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char *str;

	str = dest;
	while (n--)
		*str++ = (unsigned char)c;
	return (dest);
}

void	*ft_calloc(size_t num, size_t size)
{
	void *arr;

	arr = malloc(num * size);
	if (arr == NULL)
		return (NULL);
	else
		ft_memset(arr, 0, num * size);
	return (arr);
}

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (*str != 0)
	{
		i++;
		str++;
	}
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t len_s;
	size_t len_d;

	i = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (size > len_d)
	{
		while (*src != '\0' && ((len_d + i) != (size - 1)))
			dest[len_d + i++] = *src++;
	}
	if (size)
		dest[len_d + i] = '\0';
	return (len_s + (size < len_d ? size : len_d));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		len_s;

	if (!s1 || !s2)
		return (0);
	len_s = ft_strlen(s1) + ft_strlen(s2);
	if ((str = (char *)ft_calloc(1, len_s + 1)))
	{
		ft_strlcat(str, s1, len_s + 1);
		ft_strlcat(str, s2, len_s + 1);
		return (str);
	}
	return (0);
}
