/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:13:31 by piyu              #+#    #+#             */
/*   Updated: 2025/08/15 00:29:27 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->print_lock);
	if (dead_check(philo) == true)
		return (pthread_mutex_unlock(philo->print_lock), EXIT_FAILURE);
	printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, s);
	return (pthread_mutex_unlock(philo->print_lock), EXIT_SUCCESS);
}

int	philo_atoi(char *s)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	if (!s || !s[i])
		return (-1);
	while (s[i] == ' ')
		i++;
	if (s[i] == '-')
		return (-1);
	if (s[i] == '+')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (n * 10 + s[i] - '0' > INT_MAX)
			return (-1);
		n = n * 10 + s[i] - '0';
		i++;
	}
	return ((int)n);
}

int	error_return(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(STDERR_FILENO, &s[i++], 1);
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
