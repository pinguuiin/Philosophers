/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:07:13 by piyu              #+#    #+#             */
/*   Updated: 2025/06/14 02:41:48 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_monitor(t_philo *philo, time_t t_ms)
{
	time_t	now;
	time_t	end;

	now = get_time();
	end = now + t_ms;
	while (now < end)
	{
		if (*philo->stop_flag = 1)
			return (EXIT_FAILURE);
		if (now - philo->last_meal > philo->time_die)
		{
			philo->is_dead = true;
			if (print_message(philo, "is dead"))
				return (EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		if (usleep(1000))
			return (EXIT_FAILURE);
		now += 1;
	}
	return (EXIT_SUCCESS);
}

void	*watching(void *param)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)param;
	if (data->stop_flag == 1)
		return (NULL);
	while (i < data->num)
	{
		if (data->philo[i].is_dead == true)
		{
			if (pthread_mutex_lock(&data->stop_flag_lock))
				return (NULL);
			data->stop_flag = 1;
			if (pthread_mutex_unlock(&data->stop_flag_lock))
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
