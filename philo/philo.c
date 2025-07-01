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

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

    if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        ft_usleep(philo->data->time_to_die); // On attend qu'il meurea
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    } 
	if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat / 2);
	if (philo->data->nb_philo % 2 != 0 && philo->id == philo->data->nb_philo)
    	ft_usleep(philo->data->time_to_eat);	
	while(1)
	{
		
        pthread_mutex_lock(&philo->data->dead_lock);
        if (philo->data->is_dead)
        {
            pthread_mutex_unlock(&philo->data->dead_lock);
            break; // Sortir si la simulation est terminée
        }
        pthread_mutex_unlock(&philo->data->dead_lock);
	 	if (philo->data->is_dead) // vérifier avant de commencer à manger
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            break;
        }
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
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is thinking");
		if (philo->data->limits_meal != -1 && philo->meals >= philo->data->limits_meal)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		usleep(500);

		//lacher fourchette et liberer la memoire 
	}

	return (NULL);
}


void	wait_for_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;

	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}

}

void	detroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(data->forks);
		i++;

	}
	pthread_mutex_destroy(&data->print_lock);

}

void *monitoring(void *arg)
{
    t_data  *data;
    int     i;
    int     all_philos_have_eaten;

    data = (t_data *)arg;
    while (1) // Boucle infinie, on sortira de l'intérieur.
    {
        all_philos_have_eaten = 1; // Supposons que tout le monde a mangé.
        i = -1;
        while (++i < data->nb_philo)
        {
            pthread_mutex_lock(&data->philos[i].last_meal_mutex);
            // Vérification de la mort
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                // Mettre fin à la simulation.
                pthread_mutex_unlock(&data->philos[i].last_meal_mutex); // Libérer avant de prendre le suivant.
                
                pthread_mutex_lock(&data->dead_lock);
                data->is_dead = 1;
                pthread_mutex_unlock(&data->dead_lock);

                print_status(&data->philos[i], "died");
                return (NULL); // Le moniteur a fini son travail.
            }
            // Vérification du nombre de repas (si l'option est active).
            if (data->limits_meal != -1 && data->philos[i].meals < data->limits_meal)
                all_philos_have_eaten = 0; // Au moins un n'a pas fini de manger.
            pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
        }

        // Si l'option des repas est active et que tout le monde a mangé.
        if (data->limits_meal != -1 && all_philos_have_eaten)
        {
            pthread_mutex_lock(&data->dead_lock);
            data->is_dead = 1; // Terminer la simulation.
            pthread_mutex_unlock(&data->dead_lock);
            return (NULL);
        }
        usleep(1000); // Petite pause pour ne pas surcharger le CPU.
    }
    return (NULL);
} 


