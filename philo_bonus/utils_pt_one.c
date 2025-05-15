/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_one.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:27:32 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:27:32 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

static void	fail_free_pt_two(t_philo *philosophers, int philo_count, long long error_code);

long long	ft_atoll(const char *str)
{
	int			i;
	long long	strg;

	strg = 0;
	i = 0;
	while (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		strg = (10 * strg) + (str[i] - '0');
		i++;
	}
	return (strg);
}

void	free_philosophers(t_philo *philosophers, int philo_count, int option)
{
	destroy_semaphores(philosophers, philo_count, option);
	free(philosophers->sim_flag);
	free(philosophers);
}

int	fail_free(t_philo *philosophers, int philo_count, long long error_code)
{
	if (error_code == LLONG_MAX)
		return (0);
	else if (error_code == LLONG_MAX - 1)
	{
		free(philosophers);
		write(2, "Error\nMalloc Error\n", 19);
	}
	else if (error_code == LLONG_MAX - 2)
	{
		free(philosophers->sim_flag);
		free(philosophers);
		write(2, "Error\nFork Semaphore Init Failed\n", 33);
	}
	else if (error_code == LLONG_MAX - 3)
	{
		free_philosophers(philosophers, philo_count, 1);
		write(2, "Error\nPrint Semaphore Init Failed\n", 34);
	}
	else
		fail_free_pt_two(philosophers, philo_count, error_code);
	return (1);
}

static void	fail_free_pt_two(t_philo *philosophers, int philo_count, long long error_code)
{
	if (error_code == LLONG_MAX - 4)
	{
		free_philosophers(philosophers, philo_count, 2);
		write(2, "Error\nSimulation Semaphore Init Failed\n", 39);
	}
	else if (error_code == LLONG_MAX - 5)
	{
		free_philosophers(philosophers, philo_count, 3);
		write(2, "Error\nPhilo Semaphores Init Failed\n", 35);
	}
	else if (error_code == LLONG_MAX - 6)
	{
		free_philosophers(philosophers, philo_count, 7);
		write(2, "Error\nMalloc Error\n", 19);
	}
	else if (error_code > 0)
	{
		free_philosophers(philosophers, philo_count, 7);
		write(2, "Error\nThread Creation Error\n", 28);
	}
	else if (error_code < 0)
	{
		free_philosophers(philosophers, philo_count, 7);
		write(2, "Error\nThread Join Error\n", 24);
	}
}
