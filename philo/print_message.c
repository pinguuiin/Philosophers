/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:59:00 by piyu              #+#    #+#             */
/*   Updated: 2025/06/12 00:35:23 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *s)
{
	if (pthread_mutex_lock(philo->print_lock))
		return (EXIT_FAILURE);
	philo_putnbr(philo->start_time - get_time());
	write(STDOUT_FILENO, " ", 1);
	philo_putnbr(philo->id);
	write(STDOUT_FILENO, " ", 1);
	ft_putendl_fd(s, STDOUT_FILENO);
	if (pthread_mutex_unlock(philo->print_lock))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
