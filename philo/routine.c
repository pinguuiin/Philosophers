/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:13:40 by piyu              #+#    #+#             */
/*   Updated: 2025/08/14 00:50:14 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_ready(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == true)
			return (EXIT_FAILURE);
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->start_flag == true)
			break ;
		pthread_mutex_unlock(&philo->philo_lock);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (EXIT_SUCCESS);
}

static void	unlock_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork), EXIT_FAILURE);
	pthread_mutex_lock(philo->r_fork);
	if (print_message(philo, "has taken a fork"))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	if (print_message(philo, "is eating"))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
	if (time_counter(philo, philo->time_eat))
		return (unlock_two_forks(philo), EXIT_FAILURE);
	unlock_two_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->meals_full)
		return (pthread_mutex_unlock(&philo->philo_lock), EXIT_FAILURE);
	return (pthread_mutex_unlock(&philo->philo_lock), EXIT_SUCCESS);
}

static int	sleeping_and_thinking(t_philo *philo)
{
	if (print_message(philo, "is sleeping"))
		return (EXIT_FAILURE);
	if (time_counter(philo, philo->time_sleep))
		return (EXIT_FAILURE);
	if (print_message(philo, "is thinking"))
		return (EXIT_FAILURE);
	// pthread_mutex_lock(&philo->philo_lock);
	// if (get_time() - philo->last_meal + philo.)
	// usleep(100);
	// pthread_mutex_unlock(&philo->philo_lock);
	return (EXIT_SUCCESS);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (wait_for_ready(philo))
		return (NULL);
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		if (print_message(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->l_fork), NULL);
		usleep(philo->time_die * 1000);
		return (pthread_mutex_unlock(philo->l_fork), NULL);
	}
	if (philo->id % 2 == 0 && sleeping_and_thinking(philo))
		return (NULL);
	while (1)
	{
		if (eating(philo))
			break ;
		if (sleeping_and_thinking(philo))
			break ;
	}
	return (NULL);
}
