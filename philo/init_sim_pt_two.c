/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_pt_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:09 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 16:53:54 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	init_philo_mutex_pt_two(t_philo *philo, int philo_c);

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

int	init_philo_mutex(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].mutex_fork_left, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 1);
			return (1);
		}
	}
	init_philo_mutex_pt_two(philosophers, philo_count);
	return (0);
}

static void	init_philo_mutex_pt_two(t_philo *philo, int philo_c)
{
	int	i;

	if (philo->num_of_philo == 1)
		philo[0].mutex_fork_right = NULL;
	else
	{
		i = 1;
		philo[0].mutex_fork_right = &(philo[philo_c - 1].mutex_fork_left);
		while (i < philo_c)
		{
			philo[i].mutex_fork_right = &(philo[i - 1].mutex_fork_left);
			i++;
		}
	}
}
