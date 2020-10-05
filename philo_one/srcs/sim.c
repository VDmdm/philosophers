/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:28:38 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 00:14:00 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eat(t_initd *var, t_phil *phil, t_list *fork)
{
	if (g_dead ||
		check_die(phil->meal, phil->birth, phil->nbr, var->dead_t))
		return (put_forks(phil, fork, 0) || put_forks(phil, fork, 1));
	phil->meal = mtime();
	if (g_dead ||
		!print_status(mtime() - phil->birth, phil->nbr, " is eating\n"))
		return (put_forks(phil, fork, 0) || put_forks(phil, fork, 1));
	usleep_fix(var->eat_t);
	return (1);
}

int		ph_sleep(t_phil *phil, long sleep)
{
	if (g_dead ||
		!print_status(mtime() - phil->birth, phil->nbr, " is sleeping\n"))
		return (0);
	usleep_fix(sleep);
	return (1);
}

void	*life(void *args)
{
	t_life		l;

	l.arg = (t_args *)args;
	l.var = l.arg->vars;
	l.fork = l.arg->forks;
	l.phil = l.arg->phil;
	l.i = 1;
	while (1)
	{
		if (!take_forks(l.phil, l.fork, l.var, 1) ||
			!take_forks(l.phil, l.fork, l.var, 0))
			return (0);
		if (!eat(l.var, l.phil, l.fork) ||
			!put_forks(l.phil, l.fork, 0) || !put_forks(l.phil, l.fork, 1))
			return (0);
		if (!ph_sleep(l.phil, l.var->sleep_t))
			return (0);
		if (g_dead || !print_status(mtime() - l.phil->birth, l.phil->nbr,
														" is thinking\n"))
			return (0);
		if (l.var->count && l.i == l.var->count)
			break ;
		l.i++;
	}
	return (0);
}

int		sim_start(t_list *threads, t_list *args)
{
	unsigned int	i;
	t_list			*tmp;
	t_list			*arg;

	i = 0;
	tmp = threads;
	arg = args;
	while (tmp)
	{
		pthread_create((pthread_t *)tmp->content, NULL, life, arg->content);
		tmp = tmp->next;
		arg = arg->next;
		i++;
		usleep(2000);
	}
	tmp = threads;
	while (tmp)
	{
		pthread_join(*((pthread_t *)tmp->content), NULL);
		tmp = tmp->next;
	}
	free_n_exit(args, threads);
	return (0);
}
