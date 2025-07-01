/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:42:15 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/29 17:20:46 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	input_parse(t_data *data, char **argv)
{
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->start_time = 0;
	data->is_dead = false;
	if (argv[5])
		data->limits_meal = ft_atol(argv[5]);
	else
		data->limits_meal = -1;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	data->forks = protect_malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
		return (1);
	pthread_mutex_init(&data->print_lock, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i +1;
		philo[i].meals = 0;
		philo[i].last_meal = data->start_time;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		philo[i].has_fork = false;
		philo[i].data = data;
		i++;
	}
}

void	create_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, philo_routine, &philo[i]);
		i++;
	}
}
