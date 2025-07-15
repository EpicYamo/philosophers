/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pt_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:09:04 by aaycan            #+#    #+#             */
/*   Updated: 2025/07/15 23:34:48 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	philo_prep(t_philo *philo, int *thread_creation);
static void	philo_loop(t_philo *philo);
static void	close_semaphores(t_philo *philo);

void	*philo_routine(t_philo *philo, t_philo *philo_arr)
{
	long long	current_ms;
	int			thread_creation;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	current_ms = get_timestamp_in_ms(philo->start_time);
	sem_wait(philo->ipc_sem_two);
	if (get_timestamp_in_ms(philo->start_time) - current_ms >= 50)
		philo->sim_flag = 0;
	philo_prep(philo, &thread_creation);
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	if ((philo->philo_id % 2 == 1) && (philo->num_of_philo != 1))
		smart_sleep((philo->to_eat), philo);
	if ((philo->philo_id % 2 == 1) && (philo->philo_id == philo->num_of_philo)
		&& (philo->num_of_philo > 1))
		smart_sleep((philo->to_eat), philo);
	philo_loop(philo);
	if (thread_creation == 1)
		pthread_join(philo->end_sim_mon, NULL);
	close_semaphores(philo);
	if (philo->dead_flag == 1)
		exit_status = 3;
	free(philo_arr);
	exit(exit_status);
}

static void	philo_prep(t_philo *philo, int *thread_creation)
{
	int	i;

	(*thread_creation) = 1;
	if (pthread_create(&philo->end_sim_mon, NULL, &end_sim_monitor, philo) != 0)
	{
		end_sim_func(philo);
		printf("Thread Creation at Philo: %d Failed Ending the Simulation\n",
			philo->philo_id);
		philo->sim_flag = 0;
		(*thread_creation) = 0;
		usleep(50000);
		sem_post(philo->ipc_sem_two);
	}
	else
		sem_post(philo->ipc_sem_two);
	if (philo->philo_id == philo->num_of_philo)
	{
		i = -1;
		while (++i < philo->num_of_philo)
			sem_post(philo->ipc_sem_one);
	}
	sem_wait(philo->ipc_sem_one);
	smart_sleep(5, philo);
	sem_wait(philo->ipc_sem_three);
	sem_post(philo->ipc_sem_three);
}

static void	philo_loop(t_philo *philo)
{
	if (philo->num_of_philo == 1)
		alone_philosopher(philo);
	else
	{
		while (check_sim(philo))
		{
			eat_philosopher(philo);
			if (philo->done_eating == 1)
				break ;
			print_message(philo, "is sleeping");
			smart_sleep(philo->to_sleep, philo);
			print_message(philo, "is thinking");
			if (philo->num_of_philo % 2 == 1)
				smart_sleep(((philo->to_eat * 2) - philo->to_sleep), philo);
			else
				smart_sleep((philo->to_eat - philo->to_sleep), philo);
			usleep(100);
		}
	}
	if (philo->done_eating == 1)
	{
		smart_sleep((philo->to_eat * 3), philo);
		sem_post(philo->s_death);
	}
}

static void	close_semaphores(t_philo *philo)
{
	sem_close(philo->s_death);
	sem_close(philo->s_fork);
	sem_close(philo->s_print);
	sem_close(philo->ipc_sem_one);
	sem_close(philo->ipc_sem_two);
	sem_close(philo->ipc_sem_three);
}
