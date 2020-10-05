/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:08:29 by jalvaro           #+#    #+#             */
/*   Updated: 2020/08/17 00:52:04 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define NARG "Wrong number of arguments\n"
# define MALLOC "Malloc error\n"
# define WARG "Wrong argument\n"

int				g_dead;

typedef struct	s_initd
{
	long philo_n;
	long dead_t;
	long eat_t;
	long sleep_t;
	long count;
}				t_initd;

typedef struct	s_phil
{
	unsigned int	nbr;
	unsigned int	left_fork;
	unsigned int	right_fork;
	long			birth;
	long			meal;
}				t_phil;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_args
{
	t_phil			*phil;
	t_list			*forks;
	t_initd			*vars;
}				t_args;

typedef struct	s_life
{
	t_args			*arg;
	t_initd			*var;
	t_list			*fork;
	t_phil			*phil;
	long			i;
}				t_life;

long			ft_atol(char const *str);
int				ft_check_sign_n_nbr(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
void			*ft_calloc(size_t num, size_t size);
void			*ft_memset(void *dest, int c, size_t n);
int				sim_init(t_initd *data);
int				fork_init(t_list **list, unsigned int count);
int				args_init(t_list **list, t_list **forks, unsigned int count,
														t_initd *data);
void			philo_init(t_phil *philosopher, unsigned left_fork,
												unsigned right_fork);
int				thread_init(t_list **list, unsigned int count);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
int				print_status(int nbr, long t, char *chr);
char			*ft_itoa(long int n);
void			ft_putendl_fd(char *s, int fd);
int				ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
int				sim_start(t_list *threads, t_list *args);
void			*life(void *args);
int				ph_sleep(t_phil *phil, long sleep);
int				eat(t_initd *var, t_phil *phil, t_list *fork);
int				take_forks(t_phil *phil, t_list *fork, t_initd *var, int l);
int				put_forks(t_phil *phil, t_list *fork, int l);
int				check_die(long time, long st, int nbr, long ttd);
void			usleep_fix(long time);
long			mtime(void);
int				free_n_exit(t_list *arg, t_list *threads);
void			destroy_philo(t_list *philo);
int				destroy_mutex(t_list *fork);

#endif
