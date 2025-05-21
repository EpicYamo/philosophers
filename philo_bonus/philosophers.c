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
#include <signal.h>
#include <sys/wait.h>

static void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc);
static void	cleanup_resources(t_philo *philosophers);

int main(int argc, char **argv)
{
	t_philo	*philosophers;
	int		proc_pid;
	int		status;
	int		i;

	check_arguments(argc, argv);
	philosophers = malloc(sizeof(t_philo) * ft_atoi_mod(argv[1]));
	if (!philosophers)
	{
		write(2, "Error\nMalloc Error\n", 19);
		exit(EXIT_FAILURE);
	}
	init_philosophers(philosophers, argv, ft_atoi_mod(argv[1]), argc);
	init_simulation(philosophers, ft_atoi_mod(argv[1]));
	while ((proc_pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
		{
			int code = WEXITSTATUS(status);
			if (code == 1)
				printf("Philosopher (PID: %d) finished eating.\n", proc_pid);
			else if (code == 2)
			{
				printf("Philosopher (PID: %d) died! Killing others.\n", proc_pid);
				i = -1;
				while (++i < (philosophers[0].num_of_philo - 1))
				{
					if (philosophers[i].philo_pid != proc_pid)
						kill(philosophers[i].philo_pid, SIGTERM);
				}
				cleanup_resources(philosophers);
				exit (0);
			}
			else
				printf("Philosopher (PID: %d) exited with code %d.\n", proc_pid, code);
		}
	}
	cleanup_resources(philosophers);
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
		philosophers[i].philo_pid = 0;
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

static void	cleanup_resources(t_philo *philosophers)
{
	if (philosophers[0].s_fork)
	{
		sem_close(philosophers[0].s_fork);
		sem_unlink("/fork_semaphore");
	}
	if (philosophers[0].s_print)
	{
		sem_close(philosophers[0].s_print);
		sem_unlink("/print_semaphore");
	}
	free(philosophers);
}
