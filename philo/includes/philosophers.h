/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 06:27:31 by rafreire          #+#    #+#             */
/*   Updated: 2026/06/02 11:36:54 by rafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_action
{
	int				id;
	int				times_eaten;
	long			last_eat;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_action;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_eat;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	monitor_lock;
	t_action		*action;
}	t_data;

void	starting_tools(t_data *data);
void	*philosopher_routine(void *arg);
void	print_action(t_data *data, int id, char *action);
void	args_handling(char **av, t_data *data);
void	*track_life_philo(void *arg);
long	get_timestamp(t_data *data);
int		create_threads(t_data *data);
int		starting_data(int ac, char **av, t_data *data);
int		ft_atoi_verified(const char *str);
int		is_valid_nums(char *str);
int		all_ate_enough(t_data *data);

#endif