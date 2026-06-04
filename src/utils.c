/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 07:00:18 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/04 17:25:37 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi_verified(const char *str)
{
	size_t		i;
	long		result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX / 10 || (result == INT_MAX / 10
				&& (str[i] - '0') > INT_MAX % 10))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	print_action(t_data *data, int id, char *action)
{
	if (is_someone_died(data) && action[0] != 'd')
		return ;
	pthread_mutex_lock(&data->output_lock);
	printf("%ld %d %s\n", get_timestamp(data), id, action);
	pthread_mutex_unlock(&data->output_lock);
}

long	get_timestamp(t_data *data)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start_time);
}

int	all_ate_enough(t_data *data)
{
	int	i;

	if (data->num_times_eat <= 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->action[i].times_eaten < data->num_times_eat)
			return (0);
		i++;
	}
	return (1);
}

void	single_philosopher(t_data *data, t_action *action)
{
	pthread_mutex_lock(action->left_fork);
	print_action(data, action->id, "has taken a fork");
	usleep(data->time_to_die * 1000);
	pthread_mutex_unlock(action->left_fork);
}
