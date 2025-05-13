/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   philo_utils_pt_one.c                                          :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:28:04 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:28:04 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

static void	error_message_func(int option, int *error_flag);
static void	check_arguments_pt_two(int argc, char **argv, int *error_flag);

int	check_arguments(int argc, char **argv)
{
	int	i;
	int j;
	int	error;

	error = 0;
	if (!(argc == 6 || argc == 5))
		error_message_func(0, &error);
	if (error != 0)
		return (1);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j] < '0') || (argv[i][j] > '9'))
				error_message_func(1, &error);
		}
	}
	check_arguments_pt_two(argc, argv, &error);
	if (error != 0)
		return (1);
	return (0);
}

static void	check_arguments_pt_two(int argc, char **argv, int *error_flag)
{
	int	error;

	error = 0;
	if (ft_atoi_mod(argv[1]) <= 0)
		error = 1;
	if (ft_atoi_mod(argv[2]) <= 0)
		error = 1;
	if (ft_atoi_mod(argv[3]) <= 0)
		error = 1;
	if (ft_atoi_mod(argv[4]) <= 0)
		error = 1;
	if (argc == 6)
	{
		if (ft_atoi_mod(argv[5]) <= 0)
			error = 1;
	}
	if (error == 1)
		error_message_func(1, error_flag);
}

static void	error_message_func(int option, int *error_flag)
{
	if (option == 0)
	{
		write(2, "Error\nArguments should look like:\n", 34);
		write(2, "number_of_philosophers time_to_die time_to_eat time_to_sleep", 60);
		write(2, " (optional)number_of_times_each_philosopher_must_eat\n", 53);
	}
	if ((option == 1) && (*error_flag == 0))
		write(2, "Error\nAll arguments must only contain positive numbers.(without signs)\n", 71);
	*error_flag = 1;
}
