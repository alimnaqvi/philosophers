/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:10:22 by anaqvi            #+#    #+#             */
/*   Updated: 2025/01/27 14:39:11 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	determine_sign(char *str)
{
	if (*str == '-')
		return (-1);
	return (1);
}

static int	ft_atoi_error(char *s, unsigned int *num)
{
	unsigned long long	result;

	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (determine_sign(s) == -1)
		return (printf(ARG_STR_FORMAT), -1);
	while (*s == '+')
		s++;
	if (!*s)
		return (printf(ARG_STR_FORMAT), -1);
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');
		else
			return (printf(ARG_STR_FORMAT), -1);
		if (result > UINT_MAX)
			return (printf(ARG_STR_FORMAT), -1);
		s++;
	}
	if (result == 0)
		return (printf(ARG_STR_FORMAT), -1);
	*num = (unsigned int)result;
	return (0);
}

static int	input_num_too_long(char **argv)
{
	int	len;

	argv++;
	while (*argv)
	{
		len = 0;
		while ((*argv)[len])
			len++;
		if (len > 10)
		{
			printf("%s: " ARG_STR_FORMAT, *argv);
			return (-1);
		}
		argv++;
	}
	return (0);
}

static int	ms_too_small(t_simulation *sim)
{
	if (sim->time_to_die < 10)
		return (printf("%u: " ARG_STR_FORMAT, sim->time_to_die), 1);
	if (sim->time_to_eat < 10)
		return (printf("%u: " ARG_STR_FORMAT, sim->time_to_eat), 1);
	if (sim->time_to_sleep < 10)
		return (printf("%u: " ARG_STR_FORMAT, sim->time_to_sleep), 1);
	return (0);
}

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	if (argc != 5 && argc != 6)
	{
		printf(ARGS_FORMAT);
		return (-1);
	}
	if (input_num_too_long(argv) == -1
		|| ft_atoi_error(argv[1], &(sim->num_philos)) == -1
		|| ft_atoi_error(argv[2], &(sim->time_to_die)) == -1
		|| ft_atoi_error(argv[3], &(sim->time_to_eat)) == -1
		|| ft_atoi_error(argv[4], &(sim->time_to_sleep)) == -1)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi_error(argv[5], &(sim->num_eats_to_end)) == -1)
			return (-1);
	}
	else
		sim->num_eats_to_end = 0;
	if (sim->num_philos > 1000)
		return(printf("%s: " PHILO_N_FORMAT, argv[1]), -1);
	if (ms_too_small(sim))
		return (-1);
	return (0);
}
