/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_two.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:19:06 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:19:06 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int mutex_count, int option);

long long	get_timestamp_in_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long long		ms;

	gettimeofday(&current_time, NULL);
	ms = (current_time.tv_sec - start_time.tv_sec) * 1000;
	ms += (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

void	print_message(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(philo->print_mutex);
	timestamp = get_timestamp_in_ms(philo->start_time);
	if (*(philo->sim_flag) == 1)
		printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	pthread_mutex_unlock(philo->print_mutex);
}

void mutex_destroy_func(t_philo *philosophers, int mutex_count, int option)
{
	int	i;

	mutex_destroy_func_pt_two(philosophers, mutex_count, option);
	if (option == 1)
	{
		i = -1;
		while (++i < mutex_count)
			pthread_mutex_destroy(&philosophers[i].mutex_fork_left);
		i = -1;
		while (++i < mutex_count)
			pthread_mutex_destroy(&philosophers[i].eat_perm_mutex);
		if (philosophers[0].print_mutex)
		{
			pthread_mutex_destroy(philosophers[0].print_mutex);
			free(philosophers[0].print_mutex);
		}
	}
}

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int mutex_count, int option)
{
	int i;

	if (option == 0)
	{
		i = -1;
		while (++i < mutex_count)
			pthread_mutex_destroy(&philosophers[i].mutex_fork_left);
	}
	if (option == 2)
	{
		i = -1;
		while (++i < philosophers[0].num_of_philo)
			pthread_mutex_destroy(&philosophers[i].mutex_fork_left);
		i = -1;
		while (++i < mutex_count)
			pthread_mutex_destroy(&philosophers[i].eat_perm_mutex);
	}
}

void	smart_sleep(long long time_in_ms, t_philo *philo)
{
	long long	start_time;

	start_time = get_timestamp_in_ms(philo->start_time);
	while (*(philo->sim_flag) == 1)
	{
		if (get_timestamp_in_ms(philo->start_time) - start_time >= time_in_ms)
			break;
		usleep(500);
	}
}
