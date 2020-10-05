/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:46:32 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 00:03:16 by jalvaro          ###   ########.fr       */
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

int		put_forks(t_phil *phil, t_list *fork, int l)
{
	long	i;
	t_list	*tmp;

	i = 0;
	tmp = fork;
	while (i < (l ? phil->left_fork : phil->right_fork))
	{
		tmp = tmp->next;
		i++;
	}
	if (pthread_mutex_unlock(tmp->content))
		return (0);
	return (1);
}

int		take_forks(t_phil *phil, t_list *fork, t_initd *var, int l)
{
	long	i;
	t_list	*tmp;

	i = 0;
	tmp = fork;
	while (i < (l ? phil->left_fork : phil->right_fork))
	{
		tmp = tmp->next;
		i++;
	}
	if (g_dead || pthread_mutex_lock(tmp->content))
		return (0);
	if (g_dead || check_die(phil->meal, phil->birth, phil->nbr, var->dead_t))
		return (pthread_mutex_unlock(tmp->content));
	if (g_dead || !print_status(mtime() - phil->birth, phil->nbr,
											" has taken a fork\n"))
		return (pthread_mutex_unlock(tmp->content));
	if (g_dead || check_die(phil->meal, phil->birth, phil->nbr, var->dead_t))
		return (pthread_mutex_unlock(tmp->content));
	return (1);
}
