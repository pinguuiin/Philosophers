/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:07:13 by piyu              #+#    #+#             */
/*   Updated: 2025/08/12 21:05:00 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->is_dead == true)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (false);
}

void	wake_up_all(t_data *data)
{
	int		i;
	time_t	t;

	t = get_time();
	i = 0;
	while (i < data->num)
		pthread_mutex_lock(&data->philo[i++].philo_lock);
	i = 0;
	while (i < data->num)
	{
		data->philo[i].start_time = t;
		data->philo[i].last_meal = t;
		data->philo[i++].start_flag = true;
	}
	i = 0;
	while (i < data->num)
		pthread_mutex_unlock(&data->philo[i++].philo_lock);
}

void	*kill_all(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_lock(&data->philo[i++].philo_lock);
	i = 0;
	while (i < n)
		data->philo[i++].is_dead = true;
	i = 0;
	while (i < n)
		pthread_mutex_unlock(&data->philo[i++].philo_lock);
	return (NULL);
}

void	*watching(void *param)
{
	int		i;
	int		philos_full;
	t_data	*data;

	data = (t_data *)param;
	while (1)
	{
		if (dead_check(&data->philo[0]) == true)
			return (NULL);
		pthread_mutex_lock(&data->philo[0].philo_lock);
		if (data->philo[0].start_flag == true)
			break ;
		pthread_mutex_unlock(&data->philo[0].philo_lock);
		usleep(500);
	}
	pthread_mutex_unlock(&data->philo[0].philo_lock);
	while (1)
	{
		i = 0;
		philos_full = 0;
		while (i < data->num)
		{
			pthread_mutex_lock(&data->philo[i].philo_lock);
			if (get_time() - data->philo[i].last_meal > data->philo[i].time_die)
			{
				pthread_mutex_unlock(&data->philo[i].philo_lock);
				starve_to_die(data, &data->philo[i]);
				return (NULL);
			}
			if (data->philo[i].meals_eaten == data->philo[i].meals_full)
				philos_full++;
			pthread_mutex_unlock(&data->philo[i].philo_lock);
			i++;
		}
		if (philos_full == data->num)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
