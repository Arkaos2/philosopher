/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:38:27 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 16:19:47 by saibelab         ###   ########.fr       */
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
		res += res - '0';
	}
	return (res);
}

int	init_args(t_simu *simu, char **argv)
{
	int	i;

	if(!all_number)
	{
		printf("Argument Invalide\n");
		return (-1);
	}
	i = 0;
	simu->nb_philo = (int)ft_atol(argv[1]);
	simu->time_to_die = ft_atol(argv[2]);
	simu->time_to_eat = ft_atol(argv[3]);
	simu->time_to_sleep = ft_atol(argv[4]);
	//a pas oublier de free
	simu->philos = gc_malloc(simu->gc, sizeof(t_philo) * simu->nb_philo);
	if (!simu->philos)
		return ;
	while (i < simu->nb_philo)
	{
		simu->philos[i].id = i;
		simu->philos[i].last_meal = 0;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].simu = simu;
		i++;
	}
	return (0);
}

void init_forks(t_simu *simu)
{
	int	i;

	i = 0;
	//a pas oublier de free
	simu->forks = gc_malloc(simu->gc, sizeof(pthread_mutex_t) * simu->nb_philo);
	if (!simu->forks)
		return;
	while(i < simu->nb_philo)
	{
		pthread_mutex_init(&simu->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&simu->print_mutex, NULL);
}
