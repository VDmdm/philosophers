/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 15:38:47 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/16 21:25:05 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int		ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

char	*ft_itoa(long int n)
{
	long int		buff;
	long int		count;
	char			*str;

	buff = n;
	count = 1;
	while ((buff = buff / 10))
		count++;
	if (!(str = ft_calloc(1, count + (n < 0 ? 2 : 1))))
		return (0);
	if (n < 0)
		str[0] = '-';
	while (count)
	{
		buff = (n % 10);
		n = n / 10;
		str[count - (*str == '-' ? 0 : 1)] = (buff >= 0) ? buff + 48 :
		(buff * -1) + 48;
		count--;
	}
	return (str);
}

int		print_status(int nbr, long t, char *chr)
{
	char	*str;
	char	*nbr1;
	char	*nbr2;

	if (!(nbr1 = ft_itoa(nbr)))
		return (0);
	if (!(nbr2 = ft_itoa(t)))
		return (0);
	if (!(str = ft_strjoin(nbr1, "ms ")))
		return (0);
	free(nbr1);
	if (!(nbr1 = ft_strjoin(nbr2, chr)))
		return (0);
	free(nbr2);
	if (!(nbr2 = ft_strjoin(str, nbr1)))
		return (0);
	free(nbr1);
	free(str);
	write(1, nbr2, ft_strlen(nbr2));
	free(nbr2);
	return (1);
}
