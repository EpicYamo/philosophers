/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   philosophers.h                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:27:45 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:27:45 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				philo_id;
	int				current_meals;
	int				done_eating;

	long long		last_meal_time;
	struct timeval	start_time;
	
	pid_t			philo_pid;

	//arguments
	int				num_of_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				required_meals;
	//arguments	

	sem_t			*s_fork;
	sem_t			*s_print;
}t_philo;

void	check_arguments(int argc, char **argv);
void	init_simulation(t_philo *philosophers, int philo_count);

#endif