/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   philosophers.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:27:55 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:27:55 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	t_philo			*philosophers;
	long long		error_code;
	size_t			philo_count;

	philo_count = ft_atoi_mod(argv[1]);
	if ((check_arguments(argc, argv) != 0))
		return (1);
	philosophers = malloc(sizeof(t_philo) * philo_count);
	if (!philosophers)
	{
		write(2, "Error\nMalloc Error\n", 19);
		return (1);
	}
	init_philosophers(philosophers, argv, philo_count, argc);
	error_code = init_simulation(philosophers, philo_count);
	if (fail_free(philosophers, philo_count, error_code) != 0)
		return (1);
	free_philosophers(philosophers, philo_count);
	return (0);
}
