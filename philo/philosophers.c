/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:22:30 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/14 18:22:30 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	t_philo			*philosophers;
	long long		error_code;

	if (check_arguments(argc, argv) != 0)
		return (1);
	philosophers = malloc(sizeof(t_philo));
	if (!philosophers)
	{
		write(2, "Malloc Error\n", 13);
		return (1);
	}
	if (init_philosophers(philosophers, argv) != 0)
		return (1);
	error_code = init_process(philosophers);
	printf("%d\n",philosophers->test_counter);
	//if (fail_free(philosophers, error_code) != 0)
	//	return (1);
	//free_philosophers(philosophers);
	return (0);
}
