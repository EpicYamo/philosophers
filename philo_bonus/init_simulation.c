/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_simulation.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/27 21:16:05 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/27 21:16:05 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

static void	init_fork_semaphore(t_philo *philo, int philo_c);
static void	init_print_semaphore(t_philo *philo, int philo_c);
static void	init_death_semaphore(t_philo *philo, int philo_c);

void	init_simulation(t_philo *philo, int philo_c)
{
	int		i;
	pid_t	proc_pid;

	sem_unlink("/print_semaphore");
	sem_unlink("/fork_semaphore");
	sem_unlink("/death_semaphore");
	init_fork_semaphore(philo, philo_c);
	init_print_semaphore(philo, philo_c);
	init_death_semaphore(philo, philo_c);
	i = -1;
	while (++i < philo_c)
	{
		proc_pid = fork();
		if (proc_pid < 0)
		{
			end_sim_func(&philo[0]);
			printf("Fork Function Failed Ending The Simulation\n");
			break;
		}
		else if (proc_pid == 0)
			philo_routine(&philo[i]);
		else
			philo[i].philo_pid = proc_pid;
	}	
}

static void	init_fork_semaphore(t_philo *philo, int philo_c)
{
	sem_t	*fork_semaphore;
	int		i;

	fork_semaphore = sem_open("/fork_semaphore", O_CREAT | O_EXCL, 0644, philo_c);
	if (fork_semaphore == SEM_FAILED)
	{
		printf("fork semaphore init failed\n");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].s_fork = fork_semaphore;
}

static void	init_print_semaphore(t_philo *philo, int philo_c)
{
	sem_t	*printf_semaphore;
	int		i;

	printf_semaphore = sem_open("/print_semaphore", O_CREAT | O_EXCL, 0644, 1);
	if (printf_semaphore == SEM_FAILED)
	{
		printf("print semaphore init failed\n");
		sem_close(philo[0].s_fork);
		sem_unlink("/fork_semaphore");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].s_print = printf_semaphore;
}

static void	init_death_semaphore(t_philo *philo, int philo_c)
{
	sem_t	*death_semaphore;
	int		i;

	death_semaphore = sem_open("/death_semaphore", O_CREAT | O_EXCL, 0644, 0);
	if (death_semaphore == SEM_FAILED)
	{
		printf("death semaphore init failed\n");
		sem_close(philo[0].s_fork);
		sem_close(philo[0].s_print);
		sem_unlink("/fork_semaphore");
		sem_unlink("/print_semaphore");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].s_death = death_semaphore;
}
