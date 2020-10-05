/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:38:08 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 13:53:18 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		destroy_mutex(t_list *fork)
{
	t_list	*tmp;

	while (fork)
	{
		pthread_mutex_destroy(fork->content);
		free(fork->content);
		tmp = fork->next;
		free(fork);
		fork = tmp;
	}
	return (0);
}

void	destroy_philo(t_list *philo)
{
	t_list	*tmp;

	while (philo)
	{
		free(philo->content);
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}

int		free_n_exit(t_list *arg)
{
	t_list	*tmp;
	t_life	l;

	sem_unlink("/sem");
	if (arg)
		l.arg = (t_args	*)arg->content;
	while (arg)
	{
		l.arg = (t_args	*)arg->content;
		tmp = arg->next;
		free(l.arg->phil);
		free(arg->content);
		free(arg);
		arg = tmp;
	}
	return (0);
}

long	mtime(void)
{
	struct timeval	t;
	long			mt;

	gettimeofday(&t, NULL);
	mt = (long)t.tv_sec * 1000 + t.tv_usec * 0.001;
	return (mt);
}

void	usleep_fix(long time)
{
	long t;

	t = mtime();
	while (mtime() - t < time)
		usleep(1);
}
