/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:38:27 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/08 15:40:55 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while(i < argc)
	{
		j = 0;
		while(argv[i][j])
		{
			if (!(argv[i][j] <= '9' && argv[i][j] >= '0'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
long	ft_atol(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while(s[i])
	{
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	return (res);
}

int	init_forks(t_simu *simu)
{
	int	i;

	i = 0;
	simu->forks = gc_malloc(simu->gc, sizeof(pthread_mutex_t) * simu->nb_philo);
	if (!simu->forks)
		return (-1);
	while(i < simu->nb_philo)
	{
		pthread_mutex_init(&simu->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&simu->print_mutex, NULL);
	pthread_mutex_init(&simu->stop_simu, NULL);
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_init(&simu->philos[i].meal_mutex, NULL);
		i++;
	}

	return (0);
}

int	init_args(t_simu *simu, char **argv, int argc)
{
	int	i;

	if(!all_number(argc, argv))
	{
		printf("Argument Invalide\n");
		return (-1);
	}
	i = 0;
	simu->nb_philo = (int)ft_atol(argv[1]);
	simu->time_to_die = ft_atol(argv[2]);
	simu->time_to_eat = ft_atol(argv[3]);
	simu->time_to_sleep = ft_atol(argv[4]);
	if (simu->nb_philo <= 0 || simu->time_to_die <= 0 ||
		simu->time_to_eat <= 0 || simu->time_to_sleep <= 0)
	{
		printf("Arguments invalides: valeurs doivent être positives\n");
		return (-1);
	}
	simu->stop = 0;
	simu->philos = gc_malloc(simu->gc, sizeof(t_philo) * simu->nb_philo);
	if (!simu->philos)
		return (-1);
	while (i < simu->nb_philo)
	{
		simu->philos[i].id = i;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].simu = simu;
		i++;
	}
	init_forks(simu);
	return (0);
}
