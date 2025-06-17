/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:13:40 by piyu              #+#    #+#             */
/*   Updated: 2025/06/14 00:43:53 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork))
		return (EXIT_FAILURE);
	if (print_messasge(philo, "has taken a fork"))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->r_fork))
		return (EXIT_FAILURE);
	if (print_messasge(philo, "has taken a fork"))
		return (EXIT_FAILURE);
	if (print_message(philo, "is eating"))
		return (EXIT_FAILURE);
	philo->last_meal = get_time();
	if (sleep_monitor(philo, philo->time_eat))
		return (EXIT_FAILURE);
	philo->meals_eaten++;
	if (pthread_mutex_unlock(philo->l_fork))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->r_fork))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(philo->print_lock);
	if (sleep_monitor(philo, philo->time_sleep))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	thinking(t_philo *philo, int t)
{
	pthread_mutex_lock(philo->print_lock);
	print_message(philo, "is thinking");
	pthread_mutex_unlock(philo->print_lock);
	if (sleep_monitor(philo, t))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
	{
		if (thinking(philo, philo->time_eat))
			return (NULL);
	}
	while (*philo->stop_flag == 0)
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo, t))
			return (NULL);
	}
}
