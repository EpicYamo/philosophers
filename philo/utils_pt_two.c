/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_two.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/28 23:47:36 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/28 23:47:36 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

long long get_timestamp_in_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long long		ms;

	gettimeofday(&current_time, NULL);
	ms = (current_time.tv_sec - start_time.tv_sec) * 1000;
	ms += (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}
