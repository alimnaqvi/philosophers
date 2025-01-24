/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:59:04 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/24 18:41:56 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_simulation sim;

	sim.philos_array = NULL;
	sim.forks_array = NULL;
	sim.sim_should_stop = 0;
	if (parse_args(argc, argv, &sim) == -1)
		return (EXIT_FAILURE);
	if (init_mutexes(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	if (init_threads(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	if (wait_threads(&sim) == -1)
		return (ft_free_all(&sim), EXIT_FAILURE);
	destroy_mutexes(&sim);
	//
	return (ft_free_all(&sim), EXIT_SUCCESS);
}