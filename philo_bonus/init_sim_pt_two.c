/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_pt_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:08:49 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:22:26 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	init_ipc_semaphore_one(t_philo *philo, int philo_c)
{
	sem_t	*ipc_semaphore_one;
	int		i;

	ipc_semaphore_one = sem_open("/ipc_sem_one", O_CREAT | O_EXCL, 0644, 0);
	if (ipc_semaphore_one == SEM_FAILED)
	{
		printf("ipc_sem_one init failed\n");
		sem_close(philo[0].s_fork);
		sem_close(philo[0].s_print);
		sem_close(philo[0].s_death);
		sem_unlink("/fork_semaphore");
		sem_unlink("/print_semaphore");
		sem_unlink("/death_semaphore");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].ipc_sem_one = ipc_semaphore_one;
}

void	init_ipc_semaphore_two(t_philo *philo, int philo_c)
{
	sem_t	*ipc_semaphore_two;
	int		i;

	ipc_semaphore_two = sem_open("/ipc_sem_two", O_CREAT | O_EXCL, 0644, 1);
	if (ipc_semaphore_two == SEM_FAILED)
	{
		printf("ipc_sem_two init failed\n");
		sem_close(philo[0].s_fork);
		sem_close(philo[0].s_print);
		sem_close(philo[0].s_death);
		sem_close(philo[0].ipc_sem_one);
		sem_unlink("/fork_semaphore");
		sem_unlink("/print_semaphore");
		sem_unlink("/death_semaphore");
		sem_unlink("/ipc_sem_one");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].ipc_sem_two = ipc_semaphore_two;
}

void	init_ipc_semaphore_three(t_philo *philo, int philo_c)
{
	sem_t	*ipc_semaphore_three;
	int		i;

	ipc_semaphore_three = sem_open("/ipc_sem_three", O_CREAT | O_EXCL, 0644, 1);
	if (ipc_semaphore_three == SEM_FAILED)
	{
		printf("ipc_sem_three init failed\n");
		sem_close(philo[0].s_fork);
		sem_close(philo[0].s_print);
		sem_close(philo[0].s_death);
		sem_close(philo[0].ipc_sem_one);
		sem_close(philo[0].ipc_sem_two);
		sem_unlink("/fork_semaphore");
		sem_unlink("/print_semaphore");
		sem_unlink("/death_semaphore");
		sem_unlink("/ipc_sem_one");
		sem_unlink("/ipc_sem_two");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < philo_c)
		philo[i].ipc_sem_three = ipc_semaphore_three;
}
