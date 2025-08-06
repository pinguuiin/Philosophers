/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:50:30 by piyu              #+#    #+#             */
/*   Updated: 2025/08/06 17:54:56 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_up(t_data *data)
{
	int	i;

	i = 0;
	conditional_clean_up(data, data->num);
	while (i < data->num)
	{
		if (data->philo->has_thread)
	}
}

static int	create_thread(t_data *data)
{
	int		i;
	size_t	t;

	i = 0;
	t = get_time();
	if (pthread_create(&data->monitor, NULL, watching, (void *)data))
		return (clean_up(data));
	while (i < data->num)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine, (void *)&data->philo[i]))
			return (clean_up(data));
		data->philo[i].start_time = t;
		data->philo[i].last_meal = t;
		i++;
	}
	data->start_flag = 1;
	return (EXIT_SUCCESS);
}

static int	join_thread(t_data *data, int n)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL))
		return (clean_up(data));
	while (i < n)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (clean_up(data));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	run_philo(t_data *data)
{
	if (create_thread(data))
		return (EXIT_FAILURE);
	if (join_thread(data, data->num))
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
