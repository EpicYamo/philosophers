/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:08:55 by aaycan            #+#    #+#             */
/*   Updated: 2025/07/07 21:40:36 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

static void	init_philo(t_philo *philo, char **argv, int philo_c, int argc);
static void	wait_process(void);

int	main(int argc, char **argv)
{
	t_philo	*philo;

	check_arguments(argc, argv);
	philo = malloc(sizeof(t_philo) * ft_atoi_mod(argv[1]));
	if (!philo)
	{
		write(2, "Error\nMalloc Error\n", 19);
		exit(EXIT_FAILURE);
	}
	init_philo(philo, argv, ft_atoi_mod(argv[1]), argc);
	init_simulation(philo, ft_atoi_mod(argv[1]));
	wait_process();
	cleanup_resources(philo);
	exit(EXIT_SUCCESS);
}

static void	init_philo(t_philo *philo, char **argv, int philo_c, int argc)
{
	int				i;
	struct timeval	starting_time;

	i = 0;
	gettimeofday(&starting_time, NULL);
	while (i < philo_c)
	{
		philo[i].philo_id = i + 1;
		philo[i].philo_pid = 0;
		philo[i].current_meals = 0;
		philo[i].done_eating = 0;
		philo[i].dead_flag = 0;
		philo[i].num_of_philo = philo_c;
		philo[i].to_die = ft_atoi_mod(argv[2]);
		philo[i].to_eat = ft_atoi_mod(argv[3]);
		philo[i].to_sleep = ft_atoi_mod(argv[4]);
		philo[i].last_meal_time = 0;
		philo[i].sim_flag = 1;
		philo[i].start_time = starting_time;
		if (argc == 6)
			philo[i].required_meals = ft_atoi_mod(argv[5]);
		else
			philo[i].required_meals = -1;
		i++;
	}
}

static void	wait_process(void)
{
	int	proc_pid;
	int	status;

	proc_pid = waitpid(-1, &status, 0);
	while (proc_pid > 0)
		proc_pid = waitpid(-1, &status, 0);
}
