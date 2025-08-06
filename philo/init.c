/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:58:20 by piyu              #+#    #+#             */
/*   Updated: 2025/08/06 17:33:29 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	conditional_clean_up(t_data *data, int p)
{
	int	i;

	i = 0;
	free(data->philo);
	if (p == -3)
		return (EXIT_FAILURE);
	free(data->fork_lock);
	if (p == -2)
		return (EXIT_FAILURE);
	pthread_mutex_destroy(&data->stop_flag_lock);
	if (p == -1)
		return (EXIT_FAILURE);
	pthread_mutex_destroy(&data->print_lock);
	while (i < p)
		pthread_mutex_destroy(&data->fork_lock[i++]);
	return (EXIT_FAILURE);
}

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

void	init_philo(t_data *data, int *arr, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].time_die = arr[1];
	data->philo[i].time_eat = arr[2];
	data->philo[i].time_sleep = arr[3];
	data->philo[i].meals_full = arr[4];
	data->philo[i].meals_eaten = 0;
	data->philo[i].is_dead = false;
	data->philo[i].start_flag = &data->start_flag;
	data->philo[i].stop_flag = &data->stop_flag;
	data->philo[i].print_lock = &data->print_lock;
}

int	init_data(t_data *data, int *arr)
{
	int	i;

	i = 0;
	data->num = arr[0];
	data->stop_flag = 0;
	data->start_flag = 0;
	data->philo = malloc(data->num * sizeof(t_philo));
	if (!data->philo)
		return (EXIT_FAILURE);
	data->fork_lock = malloc(data->num * sizeof(pthread_mutex_t));
	if (!data->fork_lock)
		return (conditional_clean_up(data, -3));
	if (pthread_mutex_init(&data->stop_flag_lock, NULL))
		return (conditional_clean_up(data, -2));
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (conditional_clean_up(data, -1));
	while (i < data->num)
	{
		init_philo(data, arr, i);
		if (pthread_mutex_init(&data->fork_lock[i], NULL))
			return (conditional_clean_up(data, i));
		i++;
	}
	allocate_fork(data);
	return (EXIT_SUCCESS);
}
