/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:42:52 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/08 16:25:30 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->forks[0]);
	ft_print(philo, "has taken a fork");
	while (!ft_is_stopped(philo))
		usleep(1000);
	pthread_mutex_unlock(&philo->simu->forks[0]);
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

int	check_philo_death(t_simu *simu, int i)
{
	long	current_time;
	long	diff;

	pthread_mutex_lock(&simu->philos[i].meal_mutex);
	current_time = get_time_ms();
	diff = current_time - simu->philos[i].last_meal;
	pthread_mutex_unlock(&simu->philos[i].meal_mutex);
	if (diff > simu->time_to_die)
	{
		handle_death(simu, i);
		return (1);
	}
	return (0);
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
