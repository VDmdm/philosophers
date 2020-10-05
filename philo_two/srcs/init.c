/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:27:16 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 15:11:59 by jalvaro          ###   ########.fr       */
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

void	philo_init(t_phil *philosopher, long name)
{
	philosopher->nbr = name + 1;
	philosopher->birth = mtime();
	philosopher->meal = philosopher->birth;
}

int		args_init(t_list **list, sem_t **sem, unsigned int count,
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
		philo_init(args->phil, i);
		args->sem = *sem;
		args->vars = data;
		if (!(tmp = ft_lstnew(args)))
			return (0);
		ft_lstadd_back(list, tmp);
		i++;
	}
	return (1);
}

int		sim_init(t_initd *data)
{
	t_list		*threads;
	t_list		*args;
	sem_t		*sem;

	threads = 0;
	args = 0;
	sem = sem_open("/sem", O_CREAT, S_IRWXU, data->philo_n);
	if (!args_init(&args, &sem, data->philo_n, data))
		return (free_n_exit(args, threads));
	if (!thread_init(&threads, data->philo_n))
		return (free_n_exit(args, threads));
	return (sim_start(threads, args));
}
