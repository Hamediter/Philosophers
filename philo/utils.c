/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:29:44 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/30 18:29:47 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (!str)
		return (-1);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > LONG_MAX)
			|| (sign == -1 && (-result) < LONG_MIN))
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((long)(result * sign));
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;
	int		is_dead_flag;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	is_dead_flag = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (is_dead_flag && strcmp(msg, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	time = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*protect_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_putstr_fd("Error malloc", 2);
		return (NULL);
	}
	return (ptr);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write (fd, s++, 1);
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}
