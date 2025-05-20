/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_two.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:25:07 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:25:07 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	init_sim_flag(t_philo *philosophers, int philo_count)
{
	int	i;
	int	*simulation_flag;

	simulation_flag = malloc(sizeof(int));
	if (!simulation_flag)
		return (1);
	*simulation_flag = 1;
	i = -1;
	while (++i < philo_count)
		philosophers[i].sim_flag = simulation_flag;
	return (0);
}

int	init_fork_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*fork_semaphore;
	int		i;

	fork_semaphore = malloc(sizeof(sem_t));
	if (!fork_semaphore)
		return (1);
	if (sem_init(fork_semaphore, 0, philo_count) != 0)
	{
		free(fork_semaphore);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].s_fork = fork_semaphore;
		i++;
	}
	return (0);
}

int	init_print_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*printf_semaphore;
	int		i;

	printf_semaphore = malloc(sizeof(sem_t));
	if (!printf_semaphore)
		return (1);
	if (sem_init(printf_semaphore, 0, 1) != 0)
	{
		free(printf_semaphore);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].s_print = printf_semaphore;
		i++;
	}
	return (0);
}

int	init_sim_semaphore(t_philo *philosophers, int philo_count)
{
	sem_t	*sim_semaphore;
	int		i;

	sim_semaphore = malloc(sizeof(sem_t));
	if (!sim_semaphore)
		return (1);
	if (sem_init(sim_semaphore, 0, 1) != 0)
	{
		free(sim_semaphore);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].s_simulation = sim_semaphore;
		i++;
	}
	return (0);
}
