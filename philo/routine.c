/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:13:40 by piyu              #+#    #+#             */
/*   Updated: 2025/08/25 21:17:54 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	unlock_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static inline int	eating(t_philo *philo)
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

static inline int	sleeping_and_thinking(t_philo *philo)
{
	if (print_message(philo, "is sleeping"))
		return (EXIT_FAILURE);
	if (time_counter(philo, philo->time_sleep))
		return (EXIT_FAILURE);
	if (print_message(philo, "is thinking"))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->philo_lock);
	if (get_time() - philo->last_meal + philo->time_eat < philo->time_die
		&& philo->time_eat >= philo->time_sleep)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		if (time_counter(philo, philo->time_eat - philo->time_sleep + 1))
			return (EXIT_FAILURE);
		pthread_mutex_lock(&philo->philo_lock);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (EXIT_SUCCESS);
}

static inline void	*run_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork), NULL);
	usleep(philo->time_die * 1000);
	return (pthread_mutex_unlock(philo->l_fork), NULL);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (wait_for_ready(philo))
		return (NULL);
	if (philo->l_fork == philo->r_fork)
		return (run_one_philo(philo));
	if (philo->id % 2 != 0)
	{
		if (print_message(philo, "is thinking"))
			return (NULL);
		if (time_counter(philo, 3))
			return (NULL);
	}
	while (1)
	{
		if (eating(philo))
			break ;
		if (sleeping_and_thinking(philo))
			break ;
	}
	return (NULL);
}
