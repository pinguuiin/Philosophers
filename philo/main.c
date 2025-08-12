/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:50:30 by piyu              #+#    #+#             */
/*   Updated: 2025/08/12 04:18:18 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_and_clean_up(t_data *data, int n)
{
	int	i;

	conditional_clean_up(data, data->num);
	if (n == -1)
		return (EXIT_FAILURE);
	kill_all(data, n);
	while (i < n)
		pthread_join(data->philo[i++].thread, NULL);
	pthread_join(data->monitor, NULL);
	return (EXIT_FAILURE);
}

static int	create_thread(t_data *data)
{
	int		i;
	time_t	t;

	i = 0;
	if (pthread_create(&data->monitor, NULL, watching, (void *)data))
		return (join_and_clean_up(data, -1));
	while (i < data->num)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
		(void *)&data->philo[i]))
			return (join_and_clean_up(data, i));
		i++;
	}
	wake_up_all(data);
	return (EXIT_SUCCESS);
}

static int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL))
		return (conditional_clean_up(data, data->num));
	while (i < data->num)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (conditional_clean_up(data, data->num));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	run_philo(t_data *data)
{
	if (create_thread(data))
		return (EXIT_FAILURE);
	if (join_thread(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int				i;
	int				arr[5];
	t_data			data;

	i = 0;
	if (argc != 5 && argc != 6)
		return (error_return("Invalid input. Insert 4 or 5 arguments"));
	if (argc == 5)
		arr[4] = -1;
	while (i < argc - 1)
	{
		arr[i] = philo_atoi(argv[i + 1]);
		if (arr[i] <= 0)
			return (error_return("Invalid input. Positive numbers required"));
		i++;
	}
	if (init_data(&data, arr))
		return (error_return("Initialization error"));
	return (run_philo(&data));
}
