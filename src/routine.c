/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:44:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 17:41:18 by saibelab         ###   ########.fr       */
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
