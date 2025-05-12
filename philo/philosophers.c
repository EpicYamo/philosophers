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
#include <limits.h>

static void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc);
static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count);
static void	alone_philosopher(t_philo *philo);

int main(int argc, char **argv)
{
	t_philo			*philosophers;
	long long		error_code;
	size_t			philo_count;

	if ((check_arguments(argc, argv) != 0))
		return (1);
	philo_count = ft_atoi_mod(argv[1]);
	philosophers = malloc(sizeof(t_philo) * philo_count);
	if (!philosophers)
	{
		write(2, "Error\nMalloc Error\n", 19);
		return (1);
	}
	init_philosophers(philosophers, argv, philo_count, argc);
	if (philo_count == 1)
		alone_philosopher(philosophers);
	else
	{
		error_code = init_simulation(philosophers, philo_count);
		if (fail_free(philosophers, philo_count, error_code) != 0)
			return (1);
		free_philosophers(philosophers, philo_count, 1);
	}	
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
		philosophers[i].left_fork = 1;
		philosophers[i].start_time = starting_time;
		philosophers[i].last_meal_time = get_timestamp_in_ms(starting_time);
		philosophers[i].num_of_philo = philo_count;
		philosophers[i].current_meals = 0;
		philosophers[i].done_eating = 0;
		philosophers[i].who_locked_me = 0;
		philosophers[i].to_die = ft_atoi_mod(argv[2]);
		philosophers[i].to_eat = ft_atoi_mod(argv[3]);
		philosophers[i].to_sleep = ft_atoi_mod(argv[4]);
		if (argc == 6)
			philosophers[i].required_meals = ft_atoi_mod(argv[5]);
		else
			philosophers[i].required_meals = -1;
		i++;
	}
	init_philosophers_pt_two(philosophers, philo_count);
}

static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 1;
	if (philo_count != 1)
	{
		philosophers[0].right_fork = &(philosophers[philo_count - 1].left_fork);
		while (i < philo_count)
		{
			philosophers[i].right_fork = &(philosophers[i - 1].left_fork);
			i++;
		}
	}
}

static void	alone_philosopher(t_philo *philosophers)
{
	long long	timestamp;

	timestamp = get_timestamp_in_ms(philosophers->start_time);
	printf("%lld %d %s\n", timestamp, philosophers->philo_id, "is thinking");
	timestamp = get_timestamp_in_ms(philosophers->start_time);
	printf("%lld %d %s\n", timestamp, philosophers->philo_id, "has taken a fork");
	usleep(philosophers->to_die * 1000);
	timestamp = get_timestamp_in_ms(philosophers->start_time);
	printf("%lld %d %s\n", timestamp, philosophers->philo_id, "died");
	free(philosophers);
}
