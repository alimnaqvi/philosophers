/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:55:07 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/26 15:55:37 by anaqvi           ###   ########.fr       */
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
	unsigned int	fork1_index;
	unsigned int	fork2_index;

	sim = philo->sim;
	if (philo->sim->num_philos == 1)
		usleep(sim->time_to_die * 1000);
	if (!(sim->sim_should_stop))
	{
		determine_fork_indexes(&fork1_index, &fork2_index, philo);
		pthread_mutex_lock(&(sim->forks_array[fork1_index]));
		print_state(TAKE_FORK, philo);
		pthread_mutex_lock(&(sim->forks_array[fork2_index]));
		print_state(TAKE_FORK, philo);
		print_state(EAT, philo);
		if (!(sim->sim_should_stop))
			usleep(sim->time_to_eat * 1000);
		pthread_mutex_unlock(&(sim->forks_array[fork1_index]));
		pthread_mutex_unlock(&(sim->forks_array[fork2_index]));
		philo->last_meal_time = get_time_ms();
		philo->times_eaten++;
		check_all_times_eaten(sim);
	}
}

static void	philo_sleep(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	if (sim->time_to_sleep + BUFFER_TIME_MS < sim->time_to_die
		&& !(sim->sim_should_stop))
	{
		print_state(SLEEP, philo);
		usleep(sim->time_to_sleep * 1000);
	}
}

static void	philo_think(t_philosopher *philo)
{
	t_simulation	*sim;
	unsigned int	time_since_meal;
	int				time_to_think;

	sim = philo->sim;
	time_since_meal = get_time_ms() - philo->last_meal_time;
	time_to_think = sim->time_to_die - time_since_meal - BUFFER_TIME_MS;
	if (time_to_think > 0 && !(sim->sim_should_stop))
	{
		print_state(THINK, philo);
		usleep(time_to_think * 1000);
	}
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
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (get_time_ms() - philo->sim->start_time > MAX_RUNTIME_MS)
			break ;
	}
	return (NULL);
}
