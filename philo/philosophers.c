/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:14 by aaycan            #+#    #+#             */
/*   Updated: 2025/07/15 23:15:40 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_philosophers(t_philo *philosophers, char **argv,
				int philo_count, int argc);
static int	alone_philosopher(t_philo *philosophers);
static void	*alone_routine(void *philosopher);

int	main(int argc, char **argv)
{
	t_philo			*philosophers;
	long long		error_code;

	if ((check_arguments(argc, argv) != 0))
		return (1);
	philosophers = malloc(sizeof(t_philo) * ft_atoi_mod(argv[1]));
	if (!philosophers)
	{
		write(2, "Error\nMalloc Error\n", 19);
		return (1);
	}
	init_philosophers(philosophers, argv, ft_atoi_mod(argv[1]), argc);
	if (ft_atoi_mod(argv[1]) == 1)
	{
		if (alone_philosopher(philosophers) != 0)
			return (1);
	}
	else
	{
		error_code = init_simulation(philosophers, ft_atoi_mod(argv[1]));
		if (fail_free(philosophers, ft_atoi_mod(argv[1]), error_code) != 0)
			return (1);
		free_philosophers(philosophers, ft_atoi_mod(argv[1]), 4);
	}
	return (0);
}

static void	init_philosophers(t_philo *philosophers, char **argv,
	int philo_count, int argc)
{
	int				i;
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].philo_id = i + 1;
		philosophers[i].current_meals = 0;
		philosophers[i].done_eating = 0;
		philosophers[i].last_meal_time = get_timestamp_in_ms(curr_time);
		philosophers[i].num_of_philo = philo_count;
		philosophers[i].to_die = ft_atoi_mod(argv[2]);
		philosophers[i].to_eat = ft_atoi_mod(argv[3]);
		philosophers[i].to_sleep = ft_atoi_mod(argv[4]);
		philosophers[i].start_time = curr_time;
		if (argc == 6)
			philosophers[i].required_meals = ft_atoi_mod(argv[5]);
		else
			philosophers[i].required_meals = -1;
		i++;
	}
}

static int	alone_philosopher(t_philo *philosophers)
{
	if (pthread_mutex_init(&philosophers[0].mutex_fork_left, NULL) != 0)
	{
		write(2, "Error\nMutex Init Failed\n", 24);
		free(philosophers);
	}
	if (pthread_create(&philosophers[0].philo_thread, NULL, &alone_routine,
			&philosophers[0]) != 0)
	{
		free(philosophers);
		write(2, "Error\nThread Creation Error\n", 28);
		return (1);
	}
	if (pthread_join(philosophers[0].philo_thread, NULL) != 0)
	{
		free(philosophers);
		write(2, "Error\nThread Join Error\n", 24);
		return (1);
	}
	pthread_mutex_destroy(&philosophers[0].mutex_fork_left);
	free(philosophers);
	return (0);
}

static void	*alone_routine(void *philosopher)
{
	long long	timestamp;
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	timestamp = get_timestamp_in_ms(philo[0].start_time);
	pthread_mutex_lock(&philo->mutex_fork_left);
	printf("%lld %d %s\n", timestamp, philo[0].philo_id, "has taken a fork");
	while (1)
	{
		if (get_timestamp_in_ms(
				philo[0].start_time) - timestamp >= philo[0].to_die)
			break ;
		usleep(500);
	}
	pthread_mutex_unlock(&philo->mutex_fork_left);
	timestamp = get_timestamp_in_ms(philo[0].start_time);
	printf("%lld %d %s\n", timestamp, philo[0].philo_id, "died");
	return (NULL);
}
