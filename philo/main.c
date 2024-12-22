/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:59:04 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/22 14:32:57 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_threads(t_simulation *sim)
{
	unsigned int	i;

	sim->philos_array = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!(sim->philos_array))
		return (-1);
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&(sim->philos_array[i]), NULL, philosophize, (void *)sim))
			return (-1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_simulation sim;

	sim.philos_array = NULL;
	sim.forks_array = NULL;
	if (parse_args(argc, argv, &sim) == -1)
		return (EXIT_FAILURE);
	// initialize fork mutexes first?
	if (init_threads(&sim) == -1)
		return (ft_free_all(&sim));
	//
	return (EXIT_SUCCESS);
}