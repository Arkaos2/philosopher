/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:41:56 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/16 15:21:13 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_forks(t_philo *philo, int *first, int *second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->id;
		*second = (philo->id + 1) % philo->simu->nb_philo;
	}
	else
	{
		*first = (philo->id + 1) % philo->simu->nb_philo;
		*second = philo->id;
	}
}

void	ft_print(t_philo *philo, char *msg)
{
	int	stopped;

	pthread_mutex_lock(&philo->simu->stop_simu);
	stopped = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->stop_simu);
	pthread_mutex_lock(&philo->simu->print_mutex);
	if (!stopped)
		printf("%ld %d %s\n", get_rel_time(philo->simu), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->simu->print_mutex);
}

int	ft_take_forks(t_philo *philo, int first, int second)
{
	int	stopped;

	pthread_mutex_lock(&philo->simu->stop_simu);
	stopped = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->stop_simu);
	if (stopped)
		return (0);
	pthread_mutex_lock(&philo->simu->forks[first]);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->simu->stop_simu);
	stopped = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->stop_simu);
	if (stopped)
	{
		pthread_mutex_unlock(&philo->simu->forks[first]);
		return (0);
	}
	pthread_mutex_lock(&philo->simu->forks[second]);
	ft_print(philo, "has taken a fork");
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	get_rel_time(t_simu *simu)
{
	return (get_time_ms() - simu->start_time);
}
