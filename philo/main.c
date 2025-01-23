/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:59:04 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/23 19:02:21 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	get_timestamp_ms()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void	*philosophize(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	//
	printf("Philo %u has been created at %lu!\n", philo->philo_id, get_timestamp_ms() - sim->start_time);
	return NULL;
}

static int init_threads(t_simulation *sim)
{
	unsigned int	i;

	sim->philos_array = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!(sim->philos_array))
		return (-1);
	sim->start_time = get_timestamp_ms();
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&(sim->philos_array[i].thread_id), NULL, philosophize, &(sim->philos_array[i])))
			return (printf("Failed to create thread %d\n", i + 1), -1);
		sim->philos_array[i].philo_id = i + 1;
		sim->philos_array[i].sim = sim;
		i++;
	}
	return (0);
}

static int init_mutexes(t_simulation *sim)
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
	return (0);
}

static int wait_threads(t_simulation *sim)
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

static void	ft_free_all(t_simulation *sim)
{
	if (sim && sim->forks_array)
	{
		free(sim->forks_array);
		sim->forks_array = NULL;
	}
	if (sim && sim->philos_array)
	{
		free(sim->philos_array);
		sim->philos_array = NULL;
	}
}

static void	destroy_mutexes(t_simulation *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_destroy(&(sim->forks_array[i])))
			printf("Failed to destroy fork mutex %d\n", i + 1);
		i++;
	}
	// destroy other mutexes such as print
}

int main(int argc, char **argv)
{
	t_simulation sim;

	sim.philos_array = NULL;
	sim.forks_array = NULL;
	if (parse_args(argc, argv, &sim) == -1)
		return (EXIT_FAILURE);
	if (init_mutexes(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	if (init_threads(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	if (wait_threads(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	destroy_mutexes(&sim);
	//
	return (ft_free_all(&sim), EXIT_SUCCESS);
}