/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_two.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/21 23:23:01 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/21 23:23:01 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	print_message(t_philo *philo, char *message)
{
	long long	timestamp;
	sem_wait(philo->s_print);
	timestamp = get_timestamp_in_ms(philo->start_time);
	printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	sem_post(philo->s_print);
}

void	smart_sleep(long long time_in_ms, t_philo *philo)
{
	long long	start_time;

	start_time = get_timestamp_in_ms(philo->start_time);
	while (1)
	{
		if (get_timestamp_in_ms(philo->start_time) - start_time >= time_in_ms)
			break;
		usleep(500);
	}
}
