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

static void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc);

int main(int argc, char **argv)
{
	t_philo			*philosophers;

	check_arguments(argc, argv);
	philosophers = malloc(sizeof(t_philo) * ft_atoi_mod(argv[1]));
	if (!philosophers)
	{
		write(2, "Error\nMalloc Error\n", 19);
		exit(EXIT_FAILURE);
	}
	init_philosophers(philosophers, argv, ft_atoi_mod(argv[1]), argc);
	if (ft_atoi_mod(argv[1]) == 1)
		alone_philosopher(philosophers); //alone_philosopher should start another process with fork and exit program.
	init_simulation(philosophers, ft_atoi_mod(argv[1]));
	return (0);
}

static void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc)
{
	int				i;
	struct timeval	starting_time;

	i = 0;
	gettimeofday(&starting_time, NULL);
	while (i < philo_count)
	{
		philosophers[i].philo_id = i + 1;
		philosophers[i].current_meals = 0;
		philosophers[i].done_eating = 0;
		philosophers[i].num_of_philo = philo_count;
		philosophers[i].to_die = ft_atoi_mod(argv[2]);
		philosophers[i].to_eat = ft_atoi_mod(argv[3]);
		philosophers[i].to_sleep = ft_atoi_mod(argv[4]);
		philosophers[i].last_meal_time = get_timestamp_in_ms(starting_time);
		philosophers[i].start_time = starting_time;
		if (argc == 6)
			philosophers[i].required_meals = ft_atoi_mod(argv[5]);
		else
			philosophers[i].required_meals = -1;
		i++;
	}
}
