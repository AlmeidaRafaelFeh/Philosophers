/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 06:28:39 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/02 11:38:28 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
	{
		printf("Error: usage:./philo <philos> <die> <eat> <sleep> [time_eat]\n");
		return (1);
	}
	if (ac >= 5)
	{
		if (!starting_data(ac, av, &data))
		{
			printf("Error: initialization falid\n");
			return (1);
		}
		if (!create_threads(&data))
		{
			printf("Error: failed to create thread\n");
			free(data.forks);
			free(data.action);
			return (1);
		}
	}
	free(data.forks);
	free(data.action);
	return (0);
}
