
#include "philosophers.h"

long	ft_atol(const char *str)
{
	long long	result = 0;
	int			sign = 1;

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
			|| (sign == -1 && -result < LONG_MIN))
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (long)(result * sign);
}


void    input_parse(t_data *data, char **argv)
{
    data->nb_philo = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]) * 1000;
    data->time_to_eat = ft_atol(argv[3]) * 1000;
    data->time_to_sleep = ft_atol(argv[4]) * 1000;
    if (argv[5])
        data->limits_meal = ft_atol(argv[5]);
    else 
        data->limits_meal = 0;
}