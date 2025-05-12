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

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				philo_id;
	int				left_fork;
	int				*right_fork;
	int				*sim_flag;
	long long		last_meal_time;
	struct timeval	start_time;
	int				current_meals;
	int				done_eating;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	eat_perm_mutex;
	int				who_locked_me;
	pthread_mutex_t	mutex_fork_left;
	pthread_mutex_t	*mutex_fork_right;
	pthread_t		philo_thread;
	int				num_of_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				required_meals;
}t_philo;

int			ft_atoi_mod(const char *str);
int			check_arguments(int argc, char **argv);
long long	init_simulation(t_philo *philosophers, int philo_count);
int			init_sim_flag(t_philo *philosophers, int philo_count);
int			init_philo_mutex(t_philo *philosophers, int philo_count);
int			init_print_mutex(t_philo *philosophers, int philo_count);
int			fail_free(t_philo *philosophers, int philo_count, long long error_code);
void		mutex_destroy_func(t_philo *philosophers, int mutex_count, int option);
void		free_philosophers(t_philo *philosophers, int philo_count, int option);
void		*philo_routine(void *philosopher);
void		*monitor(void *philosophers);
long long	get_timestamp_in_ms(struct timeval start_time);
void		print_message(t_philo *philo, char *message);

#endif