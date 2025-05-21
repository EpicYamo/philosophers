/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_one.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:21:34 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:21:34 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>

static void	init_fork_semaphore(t_philo *philosophers, int philo_count);
static void	init_print_semaphore(t_philo *philosophers, int philo_count);

void	init_simulation(t_philo *philosophers, int philo_count)
{
	int		i;
	pid_t	proc_pid;

	init_fork_semaphore(philosophers, philo_count);
	init_print_semaphore(philosophers, philo_count);	
	while ((i < philo_count) && (proc_pid > 0))
	{
		//fork
	}
}

static void	init_fork_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*fork_semaphore;
	int		i;

	fork_semaphore = malloc(sizeof(sem_t));
	if (!fork_semaphore)
	{
		free(philosophers);
		exit(EXIT_FAILURE);
	}
	if (sem_init(fork_semaphore, 0, philo_count) != 0)
	{
		free(fork_semaphore);
		free(philosophers);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].s_fork = fork_semaphore;
		i++;
	}
}

static void	init_print_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*printf_semaphore;
	int		i;

	printf_semaphore = malloc(sizeof(sem_t));
	if (!printf_semaphore)
	{
		free(philosophers[0].s_fork);
		free(philosophers);
		exit(EXIT_FAILURE);
	}
	if (sem_init(printf_semaphore, 0, 1) != 0)
	{
		free(printf_semaphore);
		free(philosophers[0].s_fork);
		free(philosophers);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].s_print = printf_semaphore;
		i++;
	}
}
