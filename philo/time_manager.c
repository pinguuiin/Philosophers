/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/08/15 00:12:54 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (error_return("couldn't get time"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	time_counter(t_philo *philo, time_t t_ms)
{
	time_t	now;
	time_t	end;

	now = get_time();
	end = now + t_ms;
	while (now < end)
	{
		if (dead_check(philo) == true)
			return (EXIT_FAILURE);
		usleep(1000);
		now = get_time();
	}
	return (EXIT_SUCCESS);
}

int	wait_for_ready(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == true)
			return (EXIT_FAILURE);
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->start_flag == true)
			break ;
		pthread_mutex_unlock(&philo->philo_lock);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (EXIT_SUCCESS);
}
