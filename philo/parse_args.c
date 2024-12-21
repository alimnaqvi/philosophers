/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:10:22 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/21 17:16:50 by anaqvi           ###   ########.fr       */
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
		return(printf(ARG_STR_FORMAT), -1);
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

static int input_num_too_long(char **argv)
{
	int len;

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

int parse_args(int argc, char **argv, t_main *main)
{
	if (argc != 5 && argc != 6)
	{
		printf(ARGS_FORMAT);
		return (-1);
	}
	if (input_num_too_long(argv) == -1
		|| ft_atoi_error(argv[1], &(main->num_philos)) == -1
		|| ft_atoi_error(argv[2], &(main->eat_to_die_duration)) == -1
		|| ft_atoi_error(argv[3], &(main->eat_duration)) == -1
		|| ft_atoi_error(argv[4], &(main->sleep_duration)) == -1)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi_error(argv[5], &(main->num_eats_to_end)) == -1)
			return (-1);
	}
	else
		main->num_eats_to_end = 0;
	/* if very small ms inputs are causing problems later, force to provide e.g. at least 100 ms or at least display a warning that behavior will be inconsistent/undefined*/
	return (0);
}