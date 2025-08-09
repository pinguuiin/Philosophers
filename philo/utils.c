/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:13:31 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 01:51:25 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

int	error_return(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (EXIT_FAILURE);
}
