/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:13:40 by piyu              #+#    #+#             */
/*   Updated: 2025/08/12 22:28:12 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_two_forks(t_philo *philo)
{
	if (philo->l_fork != philo->r_fork)
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
	pthread_mutex_unlock(&philo->philo_lock);
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
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->start_flag == true)
			break ;
		pthread_mutex_unlock(&philo->philo_lock);
		usleep(500);
	}
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	pthread_mutex_unlock(&philo->philo_lock);
	if (thinking(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(philo->time_eat * 1000);
	while (1)
	{
		if (eating(philo))
			break ;
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->meals_eaten == philo->meals_full)
			return (pthread_mutex_unlock(&philo->philo_lock), NULL);
		pthread_mutex_unlock(&philo->philo_lock);
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
