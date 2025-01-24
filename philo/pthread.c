/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:39:10 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/24 19:03:03 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_threads(t_simulation *sim)
{
	unsigned int	i;

	sim->philos_array = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!(sim->philos_array))
		return (-1);
	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&(sim->philos_array[i].thread_id), NULL, philosophize, &(sim->philos_array[i])))
			return (printf("Failed to create thread %d\n", i + 1), -1);
		sim->philos_array[i].philo_id = i + 1;
		sim->philos_array[i].sim = sim;
		sim->philos_array[i].times_eaten = 0;
		sim->philos_array[i].is_sated = 0;
		i++;
	}
	return (0);
}

int init_mutexes(t_simulation *sim)
{
	unsigned int	i;

	sim->forks_array = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (!(sim->forks_array))
		return (-1);
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&(sim->forks_array[i]), NULL))
			return (printf("Failed to create fork mutex %d\n", i + 1), -1);
		i++;
	}
	if (pthread_mutex_init(sim->print_lock, NULL))
		return (printf("Failed to create print mutex\n"), -1);
	return (0);
}

int wait_threads(t_simulation *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_join(sim->philos_array[i].thread_id, NULL))
			return (printf("Failed to join thread %d\n", i + 1), -1);
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_simulation *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_destroy(&(sim->forks_array[i])))
			printf("Failed to destroy fork mutex %d\n", i + 1);
		i++;
	}
	if (pthread_mutex_destroy(sim->print_lock))
		printf("Failed to destroy print mutex\n");
	// destroy any other mutexes, if any
}
