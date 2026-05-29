/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:22:09 by rafreire          #+#    #+#             */
/*   Updated: 2026/05/29 15:34:57 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void valid_time_eat(int ac, char **av, t_data *data);

int    starting_data(int ac, char **av, t_data *data)
{
    struct timeval  tv;

    args_handling(av, data);
    valid_time_eat(ac, av, data);
    data->someone_died = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (0);
    data->action = malloc(sizeof(t_action) * data->num_philos);
    if (!data->action)
    {
        free(data->forks);
        return (0);
    }
    gettimeofday(&tv, NULL);
    data->start_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    starting_tools(data);
    return (1);
}

void    starting_tools(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        data->action[i].id = i + 1;
        data->action[i].left_fork = &data->forks[i];
        data->action[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->action[i].data = data;
        data->action[i].times_eaten = 0;
        data->action[i].last_eat = get_timestamp(data);
        i++;
    }
}

static void valid_time_eat(int ac, char **av, t_data *data)
{
    if (ac == 6)
    {
        if (!is_valid_nums(av[5]) || ft_atoi_verified(av[5]) <= 0)
        {
            printf("Error: times_must_eat must be positive\n");
            exit(1);
        }
        data->num_times_eat = ft_atoi_verified(av[5]);
    }
    else
        data->num_times_eat = -1;
}
