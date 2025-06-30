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
	t_data data;
	
	if (argc == 5 ||argc == 6)
		input_parse(&data, argv);
	else
		printf("error wrong input\n");
	return 0;
}
