/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:55:07 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/27 13:54:21 by anaqvi           ###   ########.fr       */
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
		if (get_times_eaten(&(sim->philos_array[i])) >= sim->num_eats_to_end)
			count_sated++;
		i++;
	}
	if (count_sated >= sim->num_philos)
	{
		pthread_mutex_lock(&(sim->sim_stop_lock));
		sim->sim_should_stop = 1;
		pthread_mutex_unlock(&(sim->sim_stop_lock));
	}
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
	if (!sim_should_stop(sim) && sim->num_philos != 1)
	{
		determine_fork_indexes(&fork1_index, &fork2_index, philo);
		pthread_mutex_lock(&(sim->forks_array[fork1_index]));
		print_state(TAKE_FORK, philo);
		pthread_mutex_lock(&(sim->forks_array[fork2_index]));
		print_state(TAKE_FORK, philo);
		print_state(EAT, philo);
		pthread_mutex_lock(&(sim->last_meal_time_lock));
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&(sim->last_meal_time_lock));
		if (!sim_should_stop(sim))
			ft_mssleep(sim->time_to_eat, sim);
		pthread_mutex_unlock(&(sim->forks_array[fork1_index]));
		pthread_mutex_unlock(&(sim->forks_array[fork2_index]));
		pthread_mutex_lock(&(sim->times_eaten_lock));
		philo->times_eaten++;
		pthread_mutex_unlock(&(sim->times_eaten_lock));
		check_all_times_eaten(sim);
	}
}

static void	philo_sleep(t_philosopher *philo)
{
	t_simulation	*sim;
	long			wakeup_time;
	long			death_time;
	long			cur_time;

	sim = philo->sim;
	cur_time = get_time_ms();
	wakeup_time = cur_time + sim->time_to_sleep;
	death_time = cur_time + (philo->last_meal_time - sim->time_to_die);
	if (wakeup_time + BUFFER_TIME_MS < death_time
		&& !sim_should_stop(sim))
	{
		print_state(SLEEP, philo);
		ft_mssleep(sim->time_to_sleep, sim);
	}
}

static void	philo_think(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	if (!sim_should_stop(sim))
	{
		print_state(THINK, philo);
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
	if (philo->sim->num_philos == 1)
		return (ft_mssleep(sim->time_to_die, sim), NULL);
	while (!sim_should_stop(sim))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (get_time_ms() - philo->sim->start_time > MAX_RUNTIME_MS)
			break ;
	}
	return (NULL);
}
