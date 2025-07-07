/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:09:08 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:25:47 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

long long	ft_atoll(const char *str)
{
	int			i;
	long long	strg;

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

	timestamp = get_timestamp_in_ms(philo->start_time);
	sem_wait(philo->s_print);
	if (check_sim(philo))
		printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	sem_post(philo->s_print);
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
		if (((get_timestamp_in_ms(philo->start_time) - philo->last_meal_time)
				>= philo->to_die) && (philo->done_eating == 0))
		{
			sem_wait(philo->s_print);
			if (check_sim(philo))
			{
				printf("%lld %d died\n", get_timestamp_in_ms(philo->start_time),
					philo->philo_id);
				end_sim_func(philo);
				usleep(20000);
			}
			sem_post(philo->s_print);
			philo->dead_flag = 1;
			philo->sim_flag = 0;
		}
	}
}
