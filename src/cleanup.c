/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:24:35 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/08 16:21:10 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_simu *simu)
{
	int	i;

	if (simu->forks)
	{
		i = 0;
		while (i < simu->nb_philo)
		{
			pthread_mutex_destroy(&simu->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&simu->stop_simu);
	pthread_mutex_destroy(&simu->print_mutex);
	if (simu->philos)
	{
		i = 0;
		while (i < simu->nb_philo)
		{
			pthread_mutex_destroy(&simu->philos[i].meal_mutex);
			i++;
		}
	}
}
int	check_stop(t_simu *simu)
{
	int	stopped;

	pthread_mutex_lock(&simu->stop_simu);
	stopped = simu->stop;
	pthread_mutex_unlock(&simu->stop_simu);
	return (stopped);
}

void	handle_death(t_simu *simu, int i)
{
	int should_print;

	pthread_mutex_lock(&simu->stop_simu);
	should_print = !simu->stop;
	simu->stop = 1;
	pthread_mutex_unlock(&simu->stop_simu);

	if (should_print)
	{
		pthread_mutex_lock(&simu->print_mutex);
		printf("%ld %d died\n", get_rel_time(simu), simu->philos[i].id + 1);
		pthread_mutex_unlock(&simu->print_mutex);
	}
}

void all_eaten(t_simu *simu)
{
	int	i;
	int	all_done;

	if (simu->nb_must_eat == -1 || simu->nb_philo <= 0)
		return ;
	all_done = 1;
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_lock(&simu->philos[i].meal_mutex);
		if (simu->philos[i].meals_eaten < simu->nb_must_eat)
			all_done = 0;
		pthread_mutex_unlock(&simu->philos[i].meal_mutex);
		if (!all_done)
			break ;
		i++;
	}
	if (all_done)
	{
		pthread_mutex_lock(&simu->stop_simu);
		simu->stop = 1;
		pthread_mutex_unlock(&simu->stop_simu);
	}
}

void	sleep_interruptible(t_philo *philo, long duration_ms)
{
	long start;

	start = get_time_ms();
	while (!ft_is_stopped(philo) && (get_time_ms() - start) < duration_ms)
		usleep(1000);
}
