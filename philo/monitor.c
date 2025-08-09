/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:07:13 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 02:50:08 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->is_dead == true)
	{
		pthread_mutex_unlock(&philo->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->dead_lock);
	return (false);
}

void	*kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num)
		pthread_mutex_lock(&data->philo[i++].dead_lock);
	i = 0;
	while (i < data->num)
		data->philo[i++].is_dead = true;
	i = 0;
	while (i < data->num)
		pthread_mutex_unlock(&data->philo[i++].dead_lock);
	return (NULL);
}

void	*watching(void *param)
{
	int		i;
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		i = 0;
		while (i < data->num)
		{
			if (dead_check(&data->philo[i]) == true)
				return (kill_all(data));
			i++;
		}
		usleep(200);
	}
	return (NULL);
}
