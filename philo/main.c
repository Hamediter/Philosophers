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

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = NULL;
	if (argc == 5 || argc == 6)
	{
		input_parse(&data, argv);
		philo = protect_malloc(sizeof(t_philo) * data.nb_philo);
		if (!philo)
			return (1);
		data.philos = philo;
		if (init_mutex(&data) != 0)
			return (1);
		data.start_time = get_time();
		init_philo(&data, philo);
		create_philo(&data, philo);
		pthread_create(&monitor_thread, NULL, monitoring, &data);
		wait_for_philo(&data, philo);
		pthread_join(monitor_thread, NULL);
	}
	else
		printf("error wrong input\n");
	return (0);
}
