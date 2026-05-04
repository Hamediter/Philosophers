/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:16:25 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/30 18:16:26 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->has_fork = true;
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		philo->has_fork = true;
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

static int	philo_eat_sleep_think(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is thinking");
	if (philo->data->limits_meal != -1
		&& philo->meals >= philo->data->limits_meal)
		return (1);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	usleep(500);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	if (philo->data->nb_philo % 2 != 0 && philo->id == philo->data->nb_philo)
		ft_usleep(philo->data->time_to_eat);
	while (!check_death_flag(philo))
	{
		take_forks(philo);
		if (philo_eat_sleep_think(philo))
			break ;
	}
	return (NULL);
}
