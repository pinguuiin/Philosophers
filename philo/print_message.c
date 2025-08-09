/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:59:00 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 05:08:41 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *s)
{
	if (dead_check(philo) == true)
		return (EXIT_FAILURE);
	if (get_time() - philo->last_meal > philo->time_die)
		return (starve_to_die(philo), EXIT_FAILURE);
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->print_lock);
	return (EXIT_SUCCESS);
}
