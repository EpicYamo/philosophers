/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:09:13 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:17:10 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	cleanup_resources(t_philo *philo)
{
	sem_close(philo[0].s_fork);
	sem_close(philo[0].s_print);
	sem_close(philo[0].s_death);
	sem_close(philo[0].ipc_sem_one);
	sem_close(philo[0].ipc_sem_two);
	sem_close(philo[0].ipc_sem_three);
	sem_unlink("/fork_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/death_semaphore");
	sem_unlink("/ipc_sem_one");
	sem_unlink("/ipc_sem_two");
	sem_unlink("/ipc_sem_three");
	free(philo);
}

int	check_sim(t_philo *philo)
{
	if (philo->sim_flag == 1)
		return (1);
	else
		return (0);
}

void	end_sim_func(t_philo *philo)
{
	int	i;

	i = -1;
	philo->sim_flag = 0;
	while (++i < philo->num_of_philo)
		sem_post(philo->s_death);
}
