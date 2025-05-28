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
# include <pthread.h>

typedef struct s_philosopher
{
	int				philo_id;
	int				current_meals;
	int				done_eating;
	long long		last_meal_time;
	int				sim_flag;
	int				dead_flag;
	struct timeval	start_time;
	pid_t			philo_pid;
	int				num_of_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				required_meals;
	sem_t			*s_fork;
	sem_t			*s_print;
	sem_t			*s_death;
	pthread_t		end_sim_mon;
}t_philo;

void		check_arguments(int argc, char **argv);
void		init_simulation(t_philo *philo, int philo_c);
long long	ft_atoll(const char *str);
int			ft_atoi_mod(const char *str);
long long	get_timestamp_in_ms(struct timeval start_time);
void		*philo_routine(t_philo *philo);
void		print_message(t_philo *philo, char *message);
void		smart_sleep(long long time_in_ms, t_philo *philo);
void		cleanup_resources(t_philo *philo);
void		end_sim_func(t_philo *philo);
int			check_sim(t_philo *philo);

#endif