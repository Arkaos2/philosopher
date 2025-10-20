/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:23:11 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/20 15:12:31 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_simu	*simu;
	int		i;

	simu = (t_simu *)arg;
	while (!check_stop(simu))
	{
		i = 0;
		while (i < simu->nb_philo && !check_stop(simu))
		{
			if (check_philo_death(simu, i))
				return (NULL);
			i++;
		}
		all_eaten(simu);
		usleep(1000);
	}
	return (NULL);
}

int	thread_launch(t_simu *simu)
{
	int			i;
	pthread_t	monitor_thread;

	simu->start_time = get_time_ms();
	i = 0;
	while (i < simu->nb_philo)
	{
		simu->philos[i].last_meal = simu->start_time;
		if (pthread_create(&simu->philos[i].thread, NULL,
				routine, &simu->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, simu) != 0)
		return (-1);
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_join(simu->philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_simu	*simu;
	t_gc	*gc;

	if (argc != 5 && argc != 6)
	{
		printf("./philo nb_philo time_die time_eat time_sleep [nb_meal]\n");
		return (1);
	}
	gc = gc_new();
	if (!gc)
		return (1);
	simu = gc_malloc(gc, sizeof(t_simu));
	if (!simu)
		return (gc_destroy(gc), 1);
	simu->gc = gc;
	if (init_args(simu, argv, argc) == -1)
		return (gc_destroy(gc), 1);
	if (thread_launch(simu) != 0)
	{
		destroy_mutexes(simu);
		return (gc_destroy(gc), 1);
	}
	destroy_mutexes(simu);
	return (gc_destroy(gc), 0);
}
