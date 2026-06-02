/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 07:40:14 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/02 16:04:00 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_data *data, t_action *action);
static void	eat_action(t_data *data, t_action *action);
static void	free_forks(t_action *action);
static void	sleep_action(t_data *data, t_action *action);

void	*philosopher_routine(void *arg)
{
	t_action	*action;
	t_data		*data;

	action = (t_action *)arg;
	data = (t_data *)action->data;
	if (action->id % 2)
		usleep(6000);
	else
		usleep(3000);
	while (!data->someone_died)
	{
		if (data->num_philos % 2 != 0 && action->id == 1)
			usleep(60000);
		take_forks(data, action);
		eat_action(data, action);
		free_forks(action);
		if (data->num_times_eat > 0 && action->times_eaten
			>= data->num_times_eat)
			break ;
		sleep_action(data, action);
		print_action(data, action->id, "is thinking");
	}
	return (NULL);
}

static void	take_forks(t_data *data, t_action *action)
{
	if (action->id % 2 == 0)
	{
		usleep(100);
		pthread_mutex_lock(action->right_fork);
		print_action(data, action->id, "has taken a fork");
		pthread_mutex_lock(action->left_fork);
		print_action(data, action->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(action->left_fork);
		print_action(data, action->id, "has taken a fork");
		pthread_mutex_lock(action->right_fork);
		print_action(data, action->id, "has taken a fork");
	}
}

static void	eat_action(t_data *data, t_action *action)
{
	pthread_mutex_lock(&data->monitor_lock);
	action->last_eat = get_timestamp(data);
	action->times_eaten++;
	pthread_mutex_unlock(&data->monitor_lock);
	print_action(data, action->id, "is eating");
	usleep(data->time_to_eat * 1000);
	if (data->num_times_eat > 0 && all_ate_enough(data))
		data->someone_died = 1;
}

static void	free_forks(t_action *action)
{
	pthread_mutex_unlock(action->left_fork);
	pthread_mutex_unlock(action->right_fork);
}

static void	sleep_action(t_data *data, t_action *action)
{
	print_action(data, action->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}
