/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 04:58:51 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	starve_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->dead_lock);
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %d %s\n", get_time() - philo->start_time,
	philo->id, "died");
	usleep(500);
	pthread_mutex_unlock(philo->print_lock);
}

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
		if (now - philo->last_meal > philo->time_die)
			return (starve_to_die(philo), EXIT_FAILURE);
		usleep(1000);
		now += 1;
	}
	return (EXIT_SUCCESS);
}
