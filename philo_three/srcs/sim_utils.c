/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:46:32 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 14:40:25 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_die(t_phil *phil, sem_t *death, long ttd)
{
	long t;

	sem_wait(death);
	t = mtime() - phil->meal;
	if (t > ttd)
	{
		print_status(mtime() - phil->birth, phil->nbr, " died\n");
		return (1);
	}
	sem_post(death);
	return (0);
}

int		put_forks(sem_t *sem)
{
	if (sem_post(sem))
		return (0);
	return (1);
}

int		take_forks(t_phil *phil, sem_t *sem, sem_t *death, t_initd *var)
{
	if (sem_wait(sem))
		return (0);
	if (check_die(phil, death, var->dead_t))
		return (0);
	if (!print_status(mtime() - phil->birth, phil->nbr,
											" has taken a fork\n"))
		return (0);
	if (check_die(phil, death, var->dead_t))
		return (0);
	return (1);
}
