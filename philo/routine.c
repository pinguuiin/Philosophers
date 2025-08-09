/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:13:40 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 05:42:04 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_messasge(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	pthread_mutex_lock(philo->r_fork);
	if (print_messasge(philo, "has taken a fork"))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	if (print_message(philo, "is eating"))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	philo->last_meal = get_time();
	if (time_counter(philo, philo->time_eat))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	philo->meals_eaten++;
	unlock_two_forks(philo);
	return (EXIT_SUCCESS);
}

static int	sleeping(t_philo *philo)
{
	if (print_message(philo, "is sleeping"))
		return (EXIT_FAILURE);
	if (time_counter(philo, philo->time_sleep))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	thinking(t_philo *philo)
{
	if (print_message(philo, "is thinking"))
		return (EXIT_FAILURE);
	// if (time_counter(philo, t))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (dead_check(philo) == true)
			return (NULL);
		pthread_mutex_lock(philo->start_lock);
		if (philo->start_flag == true)
			break ;
		pthread_mutex_unlock(philo->start_lock);
		usleep(500);
	}
	pthread_mutex_unlock(philo->start_lock);
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	// if (philo->id % 2 == 0)
	// {
	// 	if (thinking(philo, philo->time_eat))
	// 		return (NULL);
	// }
	while (1)
	{
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
