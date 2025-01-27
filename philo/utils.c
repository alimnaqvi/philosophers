/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:41:55 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/27 14:58:14 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_state(t_action action, t_philosopher *philo)
{
	long	cur_time;

	pthread_mutex_lock(&(philo->sim->print_lock));
	cur_time = get_time_ms() - philo->sim->start_time;
	if (!sim_should_stop(philo->sim))
	{
		if (action == TAKE_FORK)
			printf("%ld %u has taken a fork\n", cur_time, philo->philo_id);
		else if (action == EAT)
			printf("%ld %u is eating\n", cur_time, philo->philo_id);
		else if (action == SLEEP)
			printf("%ld %u is sleeping\n", cur_time, philo->philo_id);
		else if (action == THINK)
			printf("%ld %u is thinking\n", cur_time, philo->philo_id);
	}
	if (action == DIE)
		printf("%ld %u died\n", cur_time, philo->philo_id);
	pthread_mutex_unlock(&(philo->sim->print_lock));
}

int	sim_should_stop(t_simulation *sim)
{
	int	should_stop;

	pthread_mutex_lock(&(sim->sim_stop_lock));
	should_stop = sim->sim_should_stop;
	pthread_mutex_unlock(&(sim->sim_stop_lock));
	return (should_stop);
}

void	ft_mssleep(unsigned int ms, t_simulation *sim)
{
	long	sleep_start_time;

	sleep_start_time = get_time_ms();
	while (get_time_ms() < sleep_start_time + ms && !sim_should_stop(sim))
		usleep(100);
}

long	get_last_meal_time(t_philosopher *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&(philo->sim->last_meal_time_lock));
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->sim->last_meal_time_lock));
	return (last_meal_time);
}
