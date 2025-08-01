/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:58:20 by piyu              #+#    #+#             */
/*   Updated: 2025/08/01 22:41:28 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocate_fork(t_data *data)
{
	int				i;
	pthread_mutex_t	*temp;

	i = 0;
	while (i < data->num - 1)
	{
		data->philo[i].l_fork = &data->fork_lock[i];
		data->philo[i].r_fork = &data->fork_lock[i + 1];
		i++;
	}
	data->philo[i].l_fork = &data->fork_lock[i];
	data->philo[i].r_fork = &data->fork_lock[0];
	i = 0;
	while (i < data->num)
	{
		if (data->philo[i].id % 2 == 0)
		{
			temp = data->philo[i].l_fork;
			data->philo[i].l_fork = data->philo[i].r_fork;
			data->philo[i].r_fork = temp;
		}
		i++;
	}
}

int	init_data(t_data *data, int *arr)
{
	int	i;

	i = 0;
	data->num = arr[0];
	data->stop_flag = 0;
	data->philo = malloc(data->num * sizeof(t_philo));
	if (!data->philo)
		return (EXIT_FAILURE);
	data->fork_lock = malloc(data->num * sizeof(pthread_mutex_t));
	if (!data->fork_lock)
	{
		free(data->philo);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->stop_flag_lock, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (EXIT_FAILURE);
	while (i < data->num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].time_die = arr[1];
		data->philo[i].time_eat = arr[2];
		data->philo[i].time_sleep = arr[3];
		data->philo[i].meals_full = arr[4];
		data->philo[i].meals_eaten = 0;
		data->philo[i].is_dead = false;
		data->philo[i].stop_flag = &data->stop_flag;
		data->philo[i].print_lock = &data->print_lock;
		if (pthread_mutex_init(&data->fork_lock[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	allocate_fork(data);
	return (EXIT_SUCCESS);
}
