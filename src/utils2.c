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
	int should_print;

	pthread_mutex_lock(&philo->simu->stop_simu);
	should_print = !philo->simu->stop;
	philo->simu->stop = 1;
	pthread_mutex_unlock(&philo->simu->stop_simu);
	if (should_print)
	{
		pthread_mutex_lock(&philo->simu->print_mutex);
		printf("%ld %d died\n", get_rel_time(philo->simu), philo->id + 1);
		pthread_mutex_unlock(&philo->simu->print_mutex);
	}
}
void run_philo_loop(t_philo *philo)
{
	while (!ft_is_stopped(philo))
	{
		ft_eat(philo);
		if (ft_is_stopped(philo))
			break;
		if (philo->simu->nb_must_eat != -1)
		{
			pthread_mutex_lock(&philo->meal_mutex);
			if (philo->meals_eaten >= philo->simu->nb_must_eat)
			{
				pthread_mutex_unlock(&philo->meal_mutex);
				break;
			}
			pthread_mutex_unlock(&philo->meal_mutex);
		}
		ft_sleep(philo);
		if (ft_is_stopped(philo))
			break;
		ft_think(philo);
	}
}
