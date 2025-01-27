/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:57:03 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/27 14:43:59 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	get_times_eaten(t_philosopher *philo)
{
	unsigned int	times_eaten;

	pthread_mutex_lock(&(philo->sim->times_eaten_lock));
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&(philo->sim->times_eaten_lock));
	return (times_eaten);
}

void	check_all_times_eaten(t_simulation *sim)
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

void	*death_monitoring(void *arg)
{
	unsigned int	i;
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!sim_should_stop(sim))
	{
		i = 0;
		while (i < sim->num_philos && !sim_should_stop(sim))
		{
			if (get_time_ms() - get_last_meal_time(&(sim->philos_array[i]))
				> sim->time_to_die)
			{
				pthread_mutex_lock(&(sim->sim_stop_lock));
				sim->sim_should_stop = 1;
				pthread_mutex_unlock(&(sim->sim_stop_lock));
				print_state(DIE, &(sim->philos_array[i]));
				usleep(500);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
