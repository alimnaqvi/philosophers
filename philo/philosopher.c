/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:55:07 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/24 19:09:40 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_all_times_eaten(t_simulation *sim)
{
	unsigned int	i;
	unsigned int	count_sated;

	if (!(sim->num_eats_to_end))
		return ;
	count_sated = 0;
	i = 0;
	while (i < sim->num_philos)
	{
		if (sim->philos_array[i].times_eaten >= sim->num_eats_to_end)
			count_sated++;
		i++;
	}
	if (count_sated >= sim->num_philos)
		sim->sim_should_stop = 1;
}

static void	determine_fork_indexes(unsigned int *fork1_index,
unsigned int *fork2_index, t_philosopher *philo)
{
	if (!fork1_index || !fork2_index)
		return ;
	if (philo->philo_id != philo->sim->num_philos)
	{
		*fork1_index = philo->philo_id - 1;
		*fork2_index = philo->philo_id;
	}
	else
	{
		*fork1_index = 0;
		*fork2_index = philo->philo_id - 1;
	}
}

static void	philo_eat(t_philosopher *philo)
{
	t_simulation	*sim;
	unsigned int	philo_id;
	unsigned int	fork1_index;
	unsigned int	fork2_index;

	sim = philo->sim;
	philo_id = philo->philo_id;
	determine_fork_indexes(&fork1_index, &fork2_index, philo);
	pthread_mutex_lock(&(sim->forks_array[fork1_index]));
	print_state(TAKE_FORK, philo);
	pthread_mutex_lock(&(sim->forks_array[fork2_index]));
	print_state(TAKE_FORK, philo);
	print_state(EAT, philo);
	if (!(sim->sim_should_stop))
		usleep(sim->eat_duration * 1000);
	pthread_mutex_unlock(&(sim->forks_array[fork1_index]));
	pthread_mutex_unlock(&(sim->forks_array[fork2_index]));
	philo->times_eaten++;
	check_all_times_eaten(sim);
}

void	*philosophize(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	if (!philo || !(philo->sim))
		return (NULL);
	sim = philo->sim;
	while (!(sim->sim_should_stop))
	{
		philo_eat(philo);
		if (!(sim->sim_should_stop))
			philo_sleep(philo);
		if (!(sim->sim_should_stop))
			philo_think(philo);
		if (get_time_ms() - philo->sim->start_time > MAX_RUNTIME_MS)
			break ;
	}
	// printf("Philo %u has been created at %ld!\n", philo->philo_id, get_time_ms() - sim->start_time);
	return (NULL);
}
