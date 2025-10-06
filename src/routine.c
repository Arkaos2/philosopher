/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:44:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 19:14:21 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread_launch(t_simu *simu)
{
	int	i;

	i = 0;
	while(i < simu->nb_philo)
	{
		pthread_create(&simu->philos[i].thread, NULL, routine, &simu->philos[i]);
		i++;
	}
	i = 0;
	while(i < simu->nb_philo)
	{
		pthread_join(simu->philos[i].thread, NULL);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	int		left;
	int		right;
	long	timestamp;

	left = philo->id;
	right = (philo->id + 1) % philo->simu->nb_philo;
	pthread_mutex_lock(&philo->simu->forks[left]);
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	pthread_mutex_lock(&philo->simu->forks[right]);
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	timestamp = get_timestamp_ms();
	philo->last_meal = timestamp;
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d is eating\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	usleep(philo->simu->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->simu->forks[left]);
	pthread_mutex_unlock(&philo->simu->forks[right]);
	philo->meals_eaten++;
}


long get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

