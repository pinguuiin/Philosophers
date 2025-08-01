/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:50:30 by piyu              #+#    #+#             */
/*   Updated: 2025/08/01 20:27:31 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_process(t_data *data)
{
	int		i;
	size_t	t;

	i = 0;
	t = get_time();
	while (i < data->num)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine, (void *)&data->philo[i]))
			return (EXIT_FAILURE);
		data->philo[i].start_time = t;
		data->philo[i].last_meal = t;
		i++;
	}
	if (pthread_create(&data->monitor, NULL, watching, (void *)data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	run_philo(t_data *data)
{
	if (start_process(data))
		return (EXIT_FAILURE);
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
