/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:09:26 by rafreire          #+#    #+#             */
/*   Updated: 2026/05/29 14:32:43 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *track_life_philo(void   *arg)
{
    t_data  *data;
    int     i;
    
    data = (t_data *)arg;
    while (!data->someone_died)
    {
        i = 0;
        while (i < data->num_philos && !data->someone_died)
        {
            if(get_timestamp(data) - data->action[i].last_eat > data->time_to_die)
            {
                data->someone_died = 1;
                print_action(data, data->action[i].id, "died");
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}
