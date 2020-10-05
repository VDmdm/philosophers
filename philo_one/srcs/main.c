/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 11:24:36 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/16 21:22:43 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int ac, char **av)
{
	t_initd data;

	g_dead = 0;
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd(NARG, 1));
	data.count = 0;
	if ((data.philo_n = ft_atol(av[1])) <= 0 || !ft_check_sign_n_nbr(av[1]))
		return (ft_putstr_fd(WARG, 1));
	if ((data.dead_t = ft_atol(av[2])) <= 0 || !ft_check_sign_n_nbr(av[2]))
		return (ft_putstr_fd(WARG, 1));
	if ((data.eat_t = ft_atol(av[3])) <= 0 || !ft_check_sign_n_nbr(av[3]))
		return (ft_putstr_fd(WARG, 1));
	if ((data.sleep_t = ft_atol(av[4])) <= 0 || !ft_check_sign_n_nbr(av[4]))
		return (ft_putstr_fd(WARG, 1));
	if (ac == 6)
	{
		if ((data.count = ft_atol(av[5])) <= 0 || !ft_check_sign_n_nbr(av[5]))
			return (ft_putstr_fd(WARG, 1));
	}
	return (sim_init(&data));
}
