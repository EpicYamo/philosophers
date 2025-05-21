/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   check_arguments.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/15 15:32:50 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/15 15:32:50 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>

static void	error_message_func(int option);
static void	check_arguments_pt_two(char **argv);
static void	check_arguments_pt_three(int argc, char **argv);

void	check_arguments(int argc, char **argv)
{
	if (!(argc == 6 || argc == 5))
	{
		error_message_func(0);
		exit(EXIT_FAILURE);
	}
	check_arguments_pt_two(argv);
	check_arguments_pt_three(argc, argv);
}

static void	check_arguments_pt_two(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (((argv[i][j] < '0') || (argv[i][j] > '9')) || (j > 10))
			{
				error_message_func(1);
				exit(EXIT_FAILURE);
			}
		}
	}
}

static void	check_arguments_pt_three(int argc, char **argv)
{
	int	error;

	error = 0;
	if ((ft_atoll(argv[1]) <= 0) || (ft_atoll(argv[1]) > 2147483647))
		error = 1;
	if ((ft_atoll(argv[2]) <= 0) || (ft_atoll(argv[2]) > 2147483647))
		error = 1;
	if ((ft_atoll(argv[3]) <= 0) || (ft_atoll(argv[3]) > 2147483647))
		error = 1;
	if ((ft_atoll(argv[4]) <= 0) || (ft_atoll(argv[4]) > 2147483647))
		error = 1;
	if (argc == 6)
	{
		if ((ft_atoll(argv[5]) <= 0) || (ft_atoll(argv[5]) > 2147483647))
			error = 1;
	}
	if (error == 1)
	{
		error_message_func(1);
		exit(EXIT_FAILURE);
	}
}

static void	error_message_func(int option)
{
	if (option == 0)
	{
		write(2, "Error\nArguments should look like:\nnumber_", 41);
		write(2, "of_philosophers time_to_die time_to_eat time_to_sleep", 53);
		write(2, " (optional)number_of_times_each_philosopher_must_eat\n", 53);
	}
	if ((option == 1))
	{
		write(2, "Error\nAll arguments must only contain positive ", 47);
		write(2, "numbers within the integer limit range. (unsigned)\n", 51);
	}	
}
