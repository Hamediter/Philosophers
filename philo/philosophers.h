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


typedef struct s_data
{
    long    nb_philo;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    limits_meal;
    bool    is_dead;
    pthread_mutex_t *forks;  
}   t_data;

typedef struct s_philo
{
    int     id;
    long    meals;
    long    last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t       thread_id;
    
}   t_philo;

void    input_parse(t_data *data, char **argv);


#endif
