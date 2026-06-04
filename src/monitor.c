/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:09:26 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/04 17:26:23 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*track_life_philo(void *arg)
{
	t_data	*data;
	int		i;
	long	last_eat;

	data = (t_data *)arg;
	while (!is_someone_died(data))
	{
		i = 0;
		while (i < data->num_philos && !is_someone_died(data))
		{
			pthread_mutex_lock(&data->monitor_lock);
			last_eat = data->action[i].last_eat;
			pthread_mutex_unlock(&data->monitor_lock);
			if (get_timestamp(data) - last_eat > data->time_to_die)
			{
				set_someone_died(data);
				print_action(data, data->action[i].id, "died");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	is_someone_died(t_data *data)
{
	int	died;

	pthread_mutex_lock(&data->monitor_lock);
	died = data->someone_died;
	pthread_mutex_unlock(&data->monitor_lock);
	return (died);
}

void	set_someone_died(t_data *data)
{
	pthread_mutex_lock(&data->monitor_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->monitor_lock);
}
