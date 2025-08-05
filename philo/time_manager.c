/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/08/05 00:18:55 by piyu             ###   ########.fr       */
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
		if (*philo->stop_flag == 1)
			return (EXIT_FAILURE);
		if (now - philo->last_meal > philo->time_die)
		{
			philo->is_dead = true;
			if (print_message(philo, "is dead"))
				return (EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		usleep(1000);
		now += 1;
	}
	return (EXIT_SUCCESS);
}
