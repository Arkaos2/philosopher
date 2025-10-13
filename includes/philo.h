/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:37:01 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/13 15:49:20 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_gcnode
{
	void			*ptr;
	struct s_gcnode	*next;
}					t_gcnode;

typedef struct s_gc
{
	t_gcnode	*head;
}				t_gc;

typedef struct s_simu	t_simu;

typedef struct s_simu
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	int				stop;
	long			start_time;
	pthread_mutex_t	stop_simu;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	t_gc			*gc;
}	t_simu;

char		*gc_strdup(t_gc *gc, const char *s);
void		gc_destroy(t_gc *gc);
void		*gc_malloc(t_gc *gc, size_t size);
t_gc		*gc_new(void);
t_gcnode	*new_node(void *ptr);

void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		*routine(void *arg);
void		run_philo_loop(t_philo *philo);
void		thread_launch(t_simu *simu);
void		*monitor(void *arg);
void		all_eaten(t_simu *simu);

void		ft_get_forks(t_philo *philo, int *first, int *second);
int			ft_take_forks(t_philo *philo, int first, int second);

long		get_time_ms(void);
long		get_rel_time(t_simu *simu);
void		ft_print(t_philo *philo, char *msg);
int			ft_is_stopped(t_philo *philo);
void		handle_single_philo(t_philo *philo);

int			check_stop(t_simu *simu);
int			check_philo_death(t_simu *simu, int i);
void		handle_death(t_simu *simu, int i);
void		ft_die_check(t_philo *philo);

int			init_forks(t_simu *simu);
int			init_args(t_simu *simu, char **argv, int argc);
int			all_number(int argc, char **argv);
long		ft_atol(char *s);

void		destroy_mutexes(t_simu *simu);
void		ft_print(t_philo *philo, char *msg);

void		sleep_interruptible(t_philo *philo, long duration_ms);

#endif
