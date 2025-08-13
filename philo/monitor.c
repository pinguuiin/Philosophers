/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:07:13 by piyu              #+#    #+#             */
/*   Updated: 2025/08/13 04:39:31 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	hunger_level_check(t_data *data, t_philo *philo, int *philos_full)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (get_time() - philo->last_meal > philo->time_die)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		kill_all(data, data->num);
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d %s\n", get_time() - philo->start_time,
		philo->id, "died");
		usleep(1000);
		pthread_mutex_unlock(philo->print_lock);
		return (EXIT_FAILURE);
	}
	if (philo->meals_eaten == philo->meals_full)
		(*philos_full)++;
	pthread_mutex_unlock(&philo->philo_lock);
	return (EXIT_SUCCESS);
}

void	*watching(void *param)
{
	int		i;
	int		philos_full;
	t_data	*data;

	data = (t_data *)param;
	if (wait_for_ready(&data->philo[0]))
		return (NULL);
	while (1)
	{
		i = 0;
		philos_full = 0;
		while (i < data->num)
		{
			if (hunger_level_check(data, &data->philo[i], &philos_full))
				return (NULL);
			i++;
		}
		if (philos_full == data->num)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
