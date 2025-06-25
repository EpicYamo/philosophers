/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:35 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:05:55 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

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
	if (check_sim(philo))
		printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	pthread_mutex_unlock(philo->print_mutex);
}

void	smart_sleep(long long time_in_ms, t_philo *philo)
{
	long long	start_time;

	start_time = get_timestamp_in_ms(philo->start_time);
	while (check_sim(philo))
	{
		if (get_timestamp_in_ms(philo->start_time) - start_time >= time_in_ms)
			break ;
		usleep(500);
	}
}

int	check_sim(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->sim_mutex);
	if (*(philo->sim_flag) == 1)
		flag = 1;
	pthread_mutex_unlock(philo->sim_mutex);
	return (flag);
}

int	ft_atoi_mod(const char *str)
{
	int	i;
	int	strg;

	strg = 0;
	i = 0;
	while (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		strg = (10 * strg) + (str[i] - '0');
		i++;
	}
	return (strg);
}
