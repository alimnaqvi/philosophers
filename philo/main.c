/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:59:04 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/26 14:59:05 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitoring(void *arg)
{
	unsigned int	i;
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->num_philos)
		{
			if (get_time_ms() - sim->philos_array[i].last_meal_time > sim->time_to_die)
			{
				sim->sim_should_stop = 1;
				pthread_mutex_lock(&(sim->print_lock));
				printf("%ld %u died\n", get_time_ms() - sim->start_time, sim->philos_array[i].philo_id);
				pthread_mutex_unlock(&(sim->print_lock));
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_simulation sim;

	sim.philos_array = NULL;
	sim.forks_array = NULL;
	sim.sim_should_stop = 0;
	if (parse_args(argc, argv, &sim) == -1)
		return (EXIT_FAILURE);
	if (init_mutexes(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	if (init_threads(&sim) == -1)
		return (destroy_mutexes(&sim), ft_free_all(&sim), EXIT_FAILURE);
	if (wait_threads(&sim) == -1)
		return (destroy_mutexes(&sim), ft_free_all(&sim), EXIT_FAILURE);
	return (destroy_mutexes(&sim), ft_free_all(&sim), EXIT_SUCCESS);
}
