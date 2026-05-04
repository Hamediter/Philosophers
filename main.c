/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:59:35 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/29 17:01:35 by ahmed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philo_state(t_data *data, int i, int *all_philos_have_eaten)
{
	pthread_mutex_lock(&data->philos[i].last_meal_mutex);
	if (get_time() - data->philos[i].last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		pthread_mutex_lock(&data->dead_lock);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		print_status(&data->philos[i], "died");
		return (1);
	}
	if (data->limits_meal != -1 && data->philos[i].meals < data->limits_meal)
		*all_philos_have_eaten = 0;
	pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	int		all_philos_have_eaten;

	data = (t_data *)arg;
	while (1)
	{
		all_philos_have_eaten = 1;
		i = -1;
		while (++i < data->nb_philo)
		{
			if (check_philo_state(data, i, &all_philos_have_eaten))
				return (NULL);
		}
		if (data->limits_meal != -1 && all_philos_have_eaten)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_data *data, t_philo *philo, pthread_t *monitor_thread)
{
	init_philo(data, philo);
	if (create_philo(data, philo) != 0)
		return (free(philo), 1);
	if (pthread_create(monitor_thread, NULL, monitoring, data) != 0)
		return (destroy_mutex(data), free(philo), 1);
	wait_for_philo(data, philo);
	if (pthread_join(*monitor_thread, NULL) != 0)
		return (destroy_mutex(data), free(philo), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	monitor_thread;

	if (argc != 5 && argc != 6)
		return (printf("error wrong input\n"));
	if (!input_parse(&data, argv))
		return (1);
	philo = protect_malloc(sizeof(t_philo) * data.nb_philo);
	if (!philo)
		return (1);
	data.philos = philo;
	if (init_mutex(&data) != 0)
		return (free(philo), 1);
	data.start_time = get_time();
	if (start_simulation(&data, philo, &monitor_thread) != 0)
		return (1);
	destroy_mutex(&data);
	free(philo);
	return (0);
}
