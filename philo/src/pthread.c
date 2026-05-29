/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 06:28:58 by rafreire          #+#    #+#             */
/*   Updated: 2026/05/29 14:51:05 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void starting_mutex(t_data *data);
static int  create_action(t_data *data);
static void destruction_mutex(t_data *data);
static void cleanup_threads(t_data *data, int created_count);

int create_threads(t_data *data)
{
    int i;
    pthread_t   monitor_thread;

    starting_mutex(data);
    if (!create_action(data))
    {
        destruction_mutex(data);
        return (0);
    }
    usleep(100);
    if (pthread_create(&monitor_thread, NULL, track_life_philo, data) != 0)
    {
        cleanup_threads(data, data->num_philos);
        return (0);
    }
    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->action[i].thread, NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
	destruction_mutex(data);
    return (1);
}

static void    starting_mutex(t_data *data)
{
    int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->output_lock, NULL);
}

static int  create_action(t_data *data)
{
    int i;

    i = 0;
	while (i < data->num_philos)
	{
        if (pthread_create(&data->action[i].thread, NULL,
                philosopher_routine, &data->action[i]) != 0)
        {
            printf("Error: failed to create thread %d\n", i);
            cleanup_threads(data, i);
            return (0);
        }
        i++;
	}
    return (1);
}

static void    destruction_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->output_lock);
}

static void	cleanup_threads(t_data *data, int created_count)
{
    int	i;

    i = 0;
    while (i < created_count)
    {
        pthread_cancel(data->action[i].thread);
        i++;
    }
    destruction_mutex(data);
}
