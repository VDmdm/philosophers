/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:46:32 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 15:09:46 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_die(long time, long st, int nbr, long ttd)
{
	long t;

	t = mtime() - time;
	if (t > ttd)
	{
		g_dead = 1;
		print_status(mtime() - st, nbr, " died\n");
		return (1);
	}
	return (0);
}

int		put_forks(sem_t *sem)
{
	if (sem_post(sem))
		return (0);
	return (1);
}

int		take_forks(t_phil *phil, sem_t *sem, t_initd *var)
{
	if (g_dead || sem_wait(sem))
		return (0);
	if (g_dead || check_die(phil->meal, phil->birth, phil->nbr, var->dead_t))
		return (0);
	if (g_dead || !print_status(mtime() - phil->birth, phil->nbr,
											" has taken a fork\n"))
		return (0);
	if (g_dead || check_die(phil->meal, phil->birth, phil->nbr, var->dead_t))
		return (0);
	return (1);
}
