/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:58:29 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/26 18:13:32 by anaqvi           ###   ########.fr       */
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

# define BUFFER_TIME_MS 5U
# define MAX_RUNTIME_MS 37200000U // 1 hour (60 * 60 * 1000)
# define ARGS_FORMAT "Invalid arguments.\n\
Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ARG_STR_FORMAT "Invalid arguments.\n\
Each argument must be a positive (non-zero) number \
(without non_numeric characters) that fits inside UINT_MAX (4,294,967,295)\n"

typedef struct s_philosopher	t_philosopher;
typedef struct s_simulation		t_simulation;

struct s_philosopher
{
	unsigned int	philo_id;
	pthread_t		thread_id;
	long			last_meal_time;
	unsigned int	times_eaten;
	t_simulation	*sim;
};

struct s_simulation
{
	long	start_time;
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eats_to_end;
	t_philosopher	*philos_array;
	pthread_mutex_t	*forks_array;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_stop_lock;
	pthread_t		monitoring_thread;
	int				sim_should_stop;
};

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_action;

int		parse_args(int argc, char **argv, t_simulation *main);

int		init_threads(t_simulation *sim);
int		init_mutexes(t_simulation *sim);
int		wait_threads(t_simulation *sim);
void	destroy_mutexes(t_simulation *sim);

void	*philosophize(void *arg);

void	*death_monitoring(void *arg);

long	get_time_ms();
void	ft_free_all(t_simulation *sim);
void	print_state(t_action action, t_philosopher *philo);
int		sim_should_stop(t_simulation *sim);
void	ft_mssleep(unsigned int ms, t_simulation *sim);

#endif