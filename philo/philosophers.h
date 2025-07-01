/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:42:15 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/29 17:20:46 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	bool			has_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			limits_meal;
	bool			is_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
}	t_data;

void	input_parse(t_data *data, char **argv);
void	*philo_routine(void *arg);
long	ft_atol(const char *str);
void	*protect_malloc(size_t size);
void	print_status(t_philo *philo, char *msg);
void	ft_putstr_fd(char *s, int fd);
long	get_time(void);
void	init_philo(t_data *data, t_philo *philo);
int		init_mutex(t_data *data);
void	create_philo(t_data *data, t_philo *philo);
void	wait_for_philo(t_data *data, t_philo *philo);
void	*monitoring(void *arg);
void	ft_usleep(long milliseconds);

#endif
