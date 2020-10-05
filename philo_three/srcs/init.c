/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:27:16 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 14:21:35 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_phil *philosopher, long name)
{
	philosopher->nbr = name + 1;
	philosopher->birth = mtime();
	philosopher->meal = philosopher->birth;
}

int		args_init(t_list **list, sem_t **sem, sem_t **death,
														t_initd *data)
{
	unsigned int	i;
	t_args			*args;
	t_list			*tmp;

	i = 0;
	while (i < data->philo_n)
	{
		if (!(args = malloc(sizeof(t_args))))
			return (0);
		if (!(args->phil = malloc(sizeof(t_phil))))
			return (0);
		philo_init(args->phil, i);
		args->sem = *sem;
		args->death = *death;
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
	t_list		*args;
	sem_t		*sem;
	sem_t		*death;

	args = 0;
	sem = sem_open("/sem", O_CREAT, S_IRWXU, data->philo_n);
	death = sem_open("/death", O_CREAT, S_IRWXU, 2);
	if (!args_init(&args, &sem, &death, data))
		return (free_n_exit(args));
	return (sim_start(args, data->philo_n));
}
