/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   philo.c                                                :+:      :+:    :+:    */
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
#include <sys/wait.h>
#include <stdio.h>

static void	init_philo(t_philo *philo, char **argv, int philo_c, int argc);
static void	wait_process(t_philo *philo);
static void	find_dead_philo(int proc_pid, t_philo *philo, int *philo_index, int *flag);

int main(int argc, char **argv)
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
	wait_process(philo);
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

static void	wait_process(t_philo *philo)
{
	int	proc_pid;
	int	status;
	int	code;
	int	philo_index;
	int	flag;

	flag = 0;
	philo_index = -1;
	while ((proc_pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			if (code == 3)
				find_dead_philo(proc_pid, philo, &philo_index, &flag);
		}
	}
	if (philo_index != -1)
		printf("%lld %d died\n", get_timestamp_in_ms(philo[philo_index].start_time), philo[philo_index].philo_id);
}

static void	find_dead_philo(int proc_pid, t_philo *philo, int *philo_index, int *flag)
{
	int	i;

	i = -1;
	while (++i < philo[0].num_of_philo)
	{
		if ((philo[i].philo_pid == proc_pid) && (*flag == 0))
		{
			*flag = 1;
			*philo_index = i;
		}
	}
}
