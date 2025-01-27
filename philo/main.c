/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:59:04 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/27 14:45:26 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_all(t_simulation *sim)
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

int	main(int argc, char **argv)
{
	t_simulation	sim;

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
