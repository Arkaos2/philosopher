/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:37:01 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 16:19:34 by saibelab         ###   ########.fr       */
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

typedef struct	s_gcnode
{
	void				*ptr;
	struct	s_gcnode	*next;
}						t_gcnode;

typedef struct	s_gc
{
	t_gcnode	*head;
}				t_gc;

typedef struct s_simu	t_simu;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_simu			*simu;
}	t_philo;

typedef struct s_simu
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	t_gc			*gc;
}	t_simu;

char	*gc_strdup(t_gc *gc, const char *s);
void	gc_destroy(t_gc *gc);
void	*gc_malloc(t_gc *gc, size_t size);
t_gc	*gc_new(void);
t_gcnode	*new_node(void *ptr);

int		all_number(int argc, char **argv);
long	ft_atol(char *s);

#endif

