/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:23:11 by saibelab          #+#    #+#             */
/*   Updated: 2025/10/06 16:21:59 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_simu *simu;
	t_gc gc;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_meals]\n");
		return (-1);
	}
	simu = malloc(sizeof(t_simu));
	if (!simu)
		return (-1);
	simu->gc = gc_new();
	if (init_args(simu, argv, argc) == -1)
		return (-1);
	simu->start_time = get_time_ms();
	thread_launch(simu);
	return(0);
}
