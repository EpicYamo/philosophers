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
#include "stdlib.h"
#include "unistd.h"

int	ft_atoi_mod(const char *str)
{
	int	i;
	int	strg;

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

void mutex_destroy_func(t_philo *philosophers, int mutex_count)
{
	int	i;

	i = 0;
	while (i < mutex_count)
	{
		pthread_mutex_destroy(&philosophers[i].mutex_fork);
		i++;
	}
}

int	fail_free(t_philo *philosophers, int philo_count, long long error_code)
{
	if (error_code == LONG_LONG_MAX - 1)
		return (0);
	else if (error_code == LONG_LONG_MAX)
	{
		write(2, "Error\nMutex Init Failed\n", 24);
		free(philosophers);
		return (1);
	}
	else if (error_code > 0)
	{
		free_philosophers(philosophers, philo_count);
		write(2, "Error\nThread Creation Error\n", 28);
		return (1);
	}
	else if (error_code < 0)
	{
		free_philosophers(philosophers, philo_count);
		write(2, "Error\nThread Join Error\n", 24);
		return (1);
	}
}

void	free_philosophers(t_philo *philosophers, int philo_count)
{
	mutex_destroy_func(philosophers, philo_count);
	free(philosophers);
}