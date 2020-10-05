/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:27:16 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 00:36:15 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		thread_init(t_list **list, unsigned int count)
{
	unsigned int	i;
	void			*thread;
	t_list			*tmp;

	i = 0;
	while (i < count)
	{
		thread = malloc(sizeof(pthread_t));
		if (!(tmp = ft_lstnew(thread)))
			return (0);
		ft_lstadd_back(list, tmp);
		i++;
	}
	return (1);
}

void	philo_init(t_phil *philosopher, unsigned left_fork,
										unsigned right_fork)
{
	philosopher->nbr = left_fork + 1;
	if (left_fork % 2)
	{
		philosopher->left_fork = left_fork;
		philosopher->right_fork = right_fork;
	}
	else
	{
		philosopher->left_fork = right_fork;
		philosopher->right_fork = left_fork;
	}
	philosopher->birth = mtime();
	philosopher->meal = philosopher->birth;
}

int		args_init(t_list **list, t_list **forks, unsigned int count,
														t_initd *data)
{
	unsigned int	i;
	t_args			*args;
	t_list			*tmp;

	i = 0;
	while (i < count)
	{
		if (!(args = malloc(sizeof(t_args))))
			return (0);
		if (!(args->phil = malloc(sizeof(t_phil))))
			return (0);
		philo_init(args->phil, i, (i + 1) % count);
		args->forks = *forks;
		args->vars = data;
		if (!(tmp = ft_lstnew(args)))
			return (0);
		ft_lstadd_back(list, tmp);
		i++;
	}
	return (1);
}

int		fork_init(t_list **list, unsigned int count)
{
	unsigned int	i;
	void			*fork;
	t_list			*tmp;

	i = 0;
	while (i < count)
	{
		fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init((pthread_mutex_t *)fork, NULL))
			return (0);
		if (!(tmp = ft_lstnew(fork)))
			return (0);
		ft_lstadd_back(list, tmp);
		i++;
	}
	return (1);
}

int		sim_init(t_initd *data)
{
	t_list		*threads;
	t_list		*forks;
	t_list		*args;

	threads = 0;
	forks = 0;
	args = 0;
	if (!fork_init(&forks, data->philo_n))
		return (destroy_mutex(forks));
	if (!args_init(&args, &forks, data->philo_n, data))
		return (free_n_exit(args, threads));
	if (!thread_init(&threads, data->philo_n))
		return (free_n_exit(args, threads));
	return (sim_start(threads, args));
}
