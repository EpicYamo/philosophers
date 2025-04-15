/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:22:23 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/14 18:22:23 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

typedef struct s_philosopher
{
	int				*philo_id;
	int				*dead;
	int				*time_left;
	int				*wait_time;
	pthread_mutex_t	mutex;
	int				num_of_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				eat_count;
	int				test_counter;
}t_philo;

int			ft_atoi_mod(const char *str);
int			check_arguments(int argc, char **argv);
int			init_philosophers(t_philo *philosophers, char **argv);
long long	init_process(t_philo *philosophers);

#endif