/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:34:53 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/16 21:39:00 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_check_sign_n_nbr(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}

long	ft_atol(char const *str)
{
	long	res;
	int		len;
	int		minus;

	res = 0;
	len = 0;
	minus = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (str[len] >= '0' && str[len] <= '9')
	{
		res = (res * 10) + (str[len] - 48);
		len++;
	}
	return (res * minus);
}
