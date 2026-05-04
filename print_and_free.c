/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:45:23 by aboutale          #+#    #+#             */
/*   Updated: 2025/07/03 17:45:24 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *msg)
{
	long	time;
	int		is_dead_flag;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	is_dead_flag = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (is_dead_flag && ft_strcmp(msg, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	time = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	free_all(t_data *data)
{
	int	i;

	if (data->forks)
		destroy_mutex(data);
	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philo)
			pthread_mutex_destroy(&data->philos[i++].last_meal_mutex);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->dead_lock);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks);
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
