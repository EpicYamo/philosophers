/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_pt_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:04 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 16:48:04 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	init_print_mutex(t_philo *philosophers, int philo_count)
{
	int				i;
	pthread_mutex_t	*m_print_mutex;

	m_print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!m_print_mutex)
		return (1);
	if (pthread_mutex_init(m_print_mutex, NULL) != 0)
	{
		free(m_print_mutex);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].print_mutex = m_print_mutex;
		i++;
	}
	return (0);
}

int	init_sim_mutex(t_philo *philosophers, int philo_count)
{
	int				i;
	pthread_mutex_t	*m_sim_mutex;

	m_sim_mutex = malloc(sizeof(pthread_mutex_t));
	if (!m_sim_mutex)
		return (1);
	if (pthread_mutex_init(m_sim_mutex, NULL) != 0)
	{
		free(m_sim_mutex);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].sim_mutex = m_sim_mutex;
		i++;
	}
	return (0);
}
