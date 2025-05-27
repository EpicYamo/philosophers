/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_two.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/27 21:22:07 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/27 21:22:07 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	cleanup_resources(t_philo *philo)
{
	if (philo[0].s_fork)
	{
		sem_close(philo[0].s_fork);
		sem_unlink("/fork_semaphore");
	}
	if (philo[0].s_print)
	{
		sem_close(philo[0].s_print);
		sem_unlink("/print_semaphore");
	}
	free(philo);
}
