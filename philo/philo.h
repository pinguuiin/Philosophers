/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:23:27 by piyu              #+#    #+#             */
/*   Updated: 2025/08/09 05:08:30 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_data
{
	int				num;
	pthread_t		monitor;
	t_philo			*philo;
	_Atomic bool	start_flag;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals_full;
	int				meals_eaten;
	time_t			start_time;
	time_t			last_meal;
	_Atomic bool	*start_flag;
	pthread_mutex_t	*start_lock;
	_Atomic bool	is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
}	t_philo;

int		philo_atoi(char *s);
void	ft_putendl_fd(char *s, int fd);
int		error_return(char *s);
time_t	get_time(void);
int		conditional_clean_up(t_data *data, int p);
int		init_data(t_data *data, int *arr);
int		print_message(t_philo *philo, char *s);
void	*routine(void *param);
bool	dead_check(t_philo *philo);
void	*watching(void *param);
void	starve_to_die(t_philo *philo);
int		time_counter(t_philo *philo, time_t ms);
#endif
