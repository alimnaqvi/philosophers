/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:58:29 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/23 18:53:54 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_RUNTIME_MS 37200000U // 1 hour (60 * 60 * 1000)
# define ARGS_FORMAT "Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ARG_STR_FORMAT "Each argument must be a positive (non-zero) number \
(without non_numeric characters) that fits inside UINT_MAX (4,294,967,295)\n"

typedef struct s_philosopher	t_philosopher;
typedef struct s_simulation		t_simulation;

struct s_philosopher
{
	unsigned int	philo_id;
	pthread_t		thread_id;
	t_simulation	*sim;
	//
};

struct s_simulation
{
	unsigned long	start_time;
	unsigned int	num_philos;
	unsigned int	eat_to_die_duration;
	unsigned int	eat_duration;
	unsigned int	sleep_duration;
	unsigned int	num_eats_to_end;
	t_philosopher	*philos_array;
	pthread_mutex_t	*forks_array;
	int				sim_should_stop;
	//
};

int	parse_args(int argc, char **argv, t_simulation *main);

#endif