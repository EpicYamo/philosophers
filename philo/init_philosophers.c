/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_philosophers.c                                           :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/15 01:34:50 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/15 01:34:50 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"

static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count);

void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc)
{
	int				i;
	struct timeval	starting_time;

	i = 0;
	gettimeofday(&starting_time, NULL);
	while (i < philo_count)
	{
		philosophers[i].philo_id = i + 1;
		philosophers[i].left_fork = 1;
		philosophers[i].start_time = starting_time;
		philosophers[i].last_meal_time = get_timestamp_in_ms(starting_time);
		philosophers[i].num_of_philo = philo_count;
		philosophers[i].current_meals = 0;
		philosophers[i].done_eating = 0;
		philosophers[i].eat_perm_mutex_flag = 0;
		philosophers[i].to_die = ft_atoi_mod(argv[2]);
		philosophers[i].to_eat = ft_atoi_mod(argv[3]);
		philosophers[i].to_sleep = ft_atoi_mod(argv[4]);
		if (argc == 6)
			philosophers[i].required_meals = ft_atoi_mod(argv[5]);
		else
			philosophers[i].required_meals = -1;
		i++;
	}
	init_philosophers_pt_two(philosophers, philo_count);
}

static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 1;
	if (philo_count != 1)
	{
		philosophers[0].right_fork = &(philosophers[philo_count - 1].left_fork);
		while (i < philo_count)
		{
			philosophers[i].right_fork = &(philosophers[i - 1].left_fork);
			i++;
		}
	}
}
