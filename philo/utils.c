/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:41:55 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/24 18:52:25 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	ft_free_all(t_simulation *sim)
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

void	print_state(t_action action, t_philosopher *philo)
{
	long	cur_time;

	if (!(philo->sim->sim_should_stop))
	{
		pthread_mutex_lock(philo->sim->print_lock);
		cur_time = get_time_ms() - philo->sim->start_time;
		if (action == TAKE_FORK)
			printf("%ld %u has taken a fork\n", cur_time, philo->philo_id);
		else if (action == EAT)
			printf("%ld %u is eating\n", cur_time, philo->philo_id);
		else if (action == SLEEP)
			printf("%ld %u is sleeping\n", cur_time, philo->philo_id);
		else if (action == THINK)
			printf("%ld %u is thinking\n", cur_time, philo->philo_id);
		else if (action == DIE)
			printf("%ld %u died\n", cur_time, philo->philo_id);
		pthread_mutex_unlock(philo->sim->print_lock);
	}	
}
