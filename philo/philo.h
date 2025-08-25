/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:23:27 by piyu              #+#    #+#             */
/*   Updated: 2025/08/15 00:33:44 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals_full;

	int				meals_eaten;
	time_t			last_meal;
	time_t			start_time;
	bool			start_flag;
	bool			is_dead;

	pthread_mutex_t	philo_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;

}	t_philo;

typedef struct s_data
{
	int				num;
	t_philo			*philo;
	pthread_t		monitor;

	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	print_lock;

}	t_data;

int		conditional_clean_up(t_data *data, int p);
int		init_data(t_data *data, int *arr);

void	wake_up_all(t_data *data);
void	*kill_all(t_data *data, int n);
bool	dead_check(t_philo *philo);
void	*watching(void *param);

void	*routine(void *param);

time_t	get_time(void);
int		time_counter(t_philo *philo, time_t ms);
int		wait_for_ready(t_philo *philo);

int		print_message(t_philo *philo, char *s);
int		philo_atoi(char *s);
int		error_return(char *s);

#endif
