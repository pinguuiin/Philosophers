/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:07:13 by piyu              #+#    #+#             */
/*   Updated: 2025/08/06 01:02:56 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (data->philo[i].is_dead == true)
			{
				pthread_mutex_lock(&data->stop_flag_lock);
				data->stop_flag = 1;
				pthread_mutex_unlock(&data->stop_flag_lock);
				break ;
			}
			i++;
		}
		break ;
	}
	return (NULL);
}
