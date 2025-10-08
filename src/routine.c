/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:44:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 23:00:00 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

static long	get_rel_time(t_simu *simu)
{
	return (get_time_ms() - simu->start_time);
}

void	thread_launch(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_create(&simu->philos[i].thread, NULL, routine, &simu->philos[i]);
		i++;
	}
	i = 0;
	while (i < simu->nb_philo)
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
	printf("%ld %d has taken a fork\n", get_rel_time(philo->simu), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	pthread_mutex_lock(&philo->simu->forks[right]);
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d has taken a fork\n", get_rel_time(philo->simu), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	timestamp = get_rel_time(philo->simu);
	philo->last_meal = get_rel_time(philo->simu);
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d is eating\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	usleep(philo->simu->time_to_eat * 1000L);
	pthread_mutex_unlock(&philo->simu->forks[left]);
	pthread_mutex_unlock(&philo->simu->forks[right]);
	philo->meals_eaten++;
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d is sleeping\n", get_rel_time(philo->simu), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	usleep(philo->simu->time_to_sleep * 1000L);
}

void	ft_die_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->stop_simu);
	if (!philo->simu->stop)
	{
		philo->simu->stop = 1;
		printf("%ld %d died\n", get_rel_time(philo->simu), philo->id);
	}
	pthread_mutex_unlock(&philo->simu->stop_simu);
}

int	ft_is_stopped(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->simu->stop_simu);
	ret = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->stop_simu);
	return (ret);
}


void	ft_think(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;
	long	remaining;
	long	think_time;

	current_time = get_time_ms();
	time_since_meal = current_time - philo->last_meal;
	remaining = philo->simu->time_to_die - time_since_meal;
	think_time = remaining / 2;
	if (think_time < 0)
		think_time = 0;
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d is thinking\n", get_rel_time(philo->simu), philo->id + 1);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	usleep(think_time * 1000L);
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!ft_is_stopped(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		ft_die_check(philo);
	}
	return (NULL);
}
