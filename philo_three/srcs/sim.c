/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:28:38 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 14:41:04 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eat(t_initd *var, t_phil *phil, sem_t *death)
{
	if (check_die(phil, death, var->dead_t))
		return (0);
	phil->meal = mtime();
	if (!print_status(mtime() - phil->birth, phil->nbr, " is eating\n"))
		return (0);
	usleep_fix(var->eat_t);
	if (check_die(phil, death, var->dead_t))
		return (0);
	return (1);
}

int		ph_sleep(t_phil *phil, long sleep)
{
	if (!print_status(mtime() - phil->birth, phil->nbr, " is sleeping\n"))
		return (0);
	usleep_fix(sleep);
	return (1);
}

int		life(void *args)
{
	t_life		l;

	l.arg = (t_args *)args;
	l.var = l.arg->vars;
	l.sem = l.arg->sem;
	l.phil = l.arg->phil;
	l.i = 1;
	while (1)
	{
		if (!take_forks(l.phil, l.sem, l.arg->death, l.var) ||
			!take_forks(l.phil, l.sem, l.arg->death, l.var))
			exit(1);
		if (!eat(l.var, l.phil, l.arg->death) ||
			!put_forks(l.sem) || !put_forks(l.sem))
			exit(1);
		if (!ph_sleep(l.phil, l.var->sleep_t))
			exit(1);
		if (!print_status(mtime() - l.phil->birth, l.phil->nbr,
														" is thinking\n"))
			exit(1);
		if (l.var->count && l.i == l.var->count)
			break ;
		l.i++;
	}
	exit(0);
}

int		kill_n_wait(t_list *args, long n)
{
	int				stat;

	stat = 0;
	while (!stat && n)
	{
		if (waitpid(-1, &stat, 0) < 0)
			exit(0);
		n--;
	}
	while (stat && args)
	{
		kill(args->pid, 9);
		args = args->next;
	}
	return (0);
}

int		sim_start(t_list *args, long n)
{
	t_list			*arg;

	arg = args;
	while (arg)
	{
		if ((arg->pid = fork()) == -1)
			exit(0);
		if (!arg->pid)
			life(arg->content);
		arg = arg->next;
	}
	kill_n_wait(args, n);
	free_n_exit(args);
	return (0);
}
