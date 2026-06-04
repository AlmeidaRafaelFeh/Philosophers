/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 06:55:52 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/02 11:42:05 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_nums(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	args_handling(char **av, t_data *data)
{
	if (!is_valid_nums(av[1]) || !is_valid_nums(av[2])
		|| !is_valid_nums(av[3]) || !is_valid_nums(av[4]))
	{
		printf("Error: invalid arguments, only numbers\n");
		exit(1);
	}
	data->num_philos = ft_atoi_verified(av[1]);
	data->time_to_die = ft_atoi_verified(av[2]);
	data->time_to_eat = ft_atoi_verified(av[3]);
	data->time_to_sleep = ft_atoi_verified(av[4]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: all values must be positive and greater than zero\n");
		exit(1);
	}
}
