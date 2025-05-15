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
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				philo_id;
	int				current_meals;
	int				done_eating;
	int				eat_perm_mutex_flag;
	int				num_of_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				required_meals;
	long long		last_meal_time;
	struct timeval	start_time;
	int				*sim_flag;
	sem_t			s_eat_perm;
	sem_t			s_last_meal_time;
	sem_t			s_done_eating;
	sem_t			*s_fork;
	sem_t			*s_print;
	sem_t			*s_simulation;
	pthread_t		philo_thread;
}t_philo;

typedef struct s_monitors
{
	pthread_t	t_death_monitor;
	pthread_t	t_meals_monitor;
	pthread_t	t_eat_perm_monitor;
}t_monitors;

int			ft_atoi_mod(const char *str);
long long	ft_atoll(const char *str);
int			check_arguments(int argc, char **argv);
long long	init_simulation(t_philo *philosophers, int philo_count);
int			init_sim_flag(t_philo *philosophers, int philo_count);
int			init_fork_semaphore(t_philo *philosophers, int philo_count);
int			init_print_semaphore(t_philo *philosophers, int philo_count);
int			init_sim_semaphore(t_philo *philosophers, int philo_count);
int			init_philo_semaphores(t_philo *philosophers, int philo_count);
int			fail_free(t_philo *philosophers, int philo_count, long long error_code);
void		free_philosophers(t_philo *philosophers, int philo_count, int option);
void		destroy_semaphores(t_philo *philosophers, int sem_count, int option);
void		*philo_routine(void *philosopher);
void		*death_monitor(void *philosophers);
void		*eat_perm_monitor(void *philosophers);
void		*meals_monitor(void *philosophers);
long long	get_timestamp_in_ms(struct timeval start_time);
void		print_message(t_philo *philo, char *message);
void		smart_sleep(long long time_in_ms, t_philo *philo);
int			check_sim(t_philo *philo);

#endif