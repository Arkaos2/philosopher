/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:44:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/08 16:26:33 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	int		first_fork;
	int		second_fork;
	long	timestamp;
	int		forks_taken;

	ft_get_forks(philo, &first_fork, &second_fork);
	forks_taken = ft_take_forks(philo, first_fork, second_fork);
	if (!forks_taken)
		return;
	timestamp = get_rel_time(philo->simu);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_print(philo, "is eating");
	sleep_interruptible(philo, philo->simu->time_to_eat);
	pthread_mutex_unlock(&philo->simu->forks[first_fork]);
	pthread_mutex_unlock(&philo->simu->forks[second_fork]);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	sleep_interruptible(philo, philo->simu->time_to_sleep);
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
	pthread_mutex_lock(&philo->meal_mutex);
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	remaining = philo->simu->time_to_die - time_since_meal;
	think_time = remaining / 2;
	if (think_time < 0)
		think_time = 0;
	ft_print(philo, "is thinking");
	sleep_interruptible(philo, think_time);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		usleep(100);
	if (philo->simu->nb_philo == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	run_philo_loop(philo);
	return (NULL);
}
