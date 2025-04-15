/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_and_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:51:10 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/15 19:51:10 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static void	*philo_routine(void *philosophers);

long long	init_process(t_philo *philosophers)
{
	pthread_t		th[philosophers->num_of_philo];
	int				i;

	if (pthread_mutex_init(&philosophers->mutex, NULL) != 0)
		return (LONG_LONG_MAX);
	i = 0;
	while (i < philosophers->num_of_philo)
	{
		if (pthread_create(&th[i], NULL, &philo_routine, &philosophers) != 0)
			return (i);
		i++;
	}
	i = 0;
	while (i < philosophers->num_of_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (i *= -1);
		i++;
	}
	pthread_mutex_destroy(&philosophers->mutex);
	return (LONG_LONG_MAX - 1);
}

static void	*philo_routine(void *philosophers)
{
	//t_philo *philosophers = philosopherso;
	int	i;

	i = 0;
	while(i < 100000)
	{
		pthread_mutex_lock(&philosophers->mutex);
		philosophers->test_counter += 1;
		pthread_mutex_unlock(&philosophers->mutex);
	}
}
