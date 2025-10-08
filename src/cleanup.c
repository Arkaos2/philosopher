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
