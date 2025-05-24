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
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

static void	init_fork_semaphore(t_philo *philosophers, int philo_count);
static void	init_print_semaphore(t_philo *philosophers, int philo_count);

void	init_simulation(t_philo *philosophers, int philo_count)
{
	int		i;
	pid_t	proc_pid;

	init_fork_semaphore(philosophers, philo_count);
	init_print_semaphore(philosophers, philo_count);
	i = 0;
	while (i < philo_count)
	{
		proc_pid = fork();
		if (proc_pid < 0)
		{
			printf("fork failed\n");
			sem_close(philosophers[0].s_fork);
			sem_close(philosophers[0].s_print);
			sem_unlink("/fork_semaphore");
			sem_unlink("/print_semaphore");
			free(philosophers);
			exit(EXIT_FAILURE);
		}
		else if (proc_pid == 0)
			philo_routine(&philosophers[i]);
		else
			philosophers[i].philo_pid = proc_pid;
		i++;
	}	
}

static void	init_fork_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*fork_semaphore;
	int		i;

	fork_semaphore = sem_open("/fork_semaphore", O_CREAT | O_EXCL, 0644, philo_count);
	if (fork_semaphore == SEM_FAILED)
	{
		printf("fork semaphore init failed\n");
		free(philosophers);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_count)
		philosophers[i].s_fork = fork_semaphore;
}

static void	init_print_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*printf_semaphore;
	int		i;

	printf_semaphore = sem_open("/print_semaphore", O_CREAT | O_EXCL, 0644, 1);
	if (printf_semaphore == SEM_FAILED)
	{
		printf("print semaphore init failed\n");
		sem_close(philosophers[0].s_fork);
		sem_unlink("/fork_semaphore");
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
