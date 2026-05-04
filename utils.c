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

void	is_sign(const char **str, int *sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

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
	is_sign(&str, &sign);
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

int	ft_strcmp(char *s1, char *s2)

{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
