/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:19:08 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/17 12:42:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * (data->n_philo));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->philos || !data->forks)
		return ;
	data->all_done = 0;
	data->stop = 0;
	data->start_time = get_current_time();
	pthread_mutex_init(&data->p_action, NULL);
	pthread_mutex_init(&data->die, NULL);
	pthread_mutex_init(&data->l_eat, NULL);
	pthread_mutex_init(&data->n_eat, NULL);
	init_philos2(data);
}

void	init_philos2(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].right_fork = (i + 1) % data->n_philo;
		data->philos[i].left_fork = i;
		data->philos[i].last_eat = 0;
		data->philos[i].num_eat = 0;
		data->philos[i].p_data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_forks(int *fork1, int *fork2, t_philo *philo)
{
	if (philo->right_fork > philo->left_fork)
	{
		*fork1 = philo->left_fork;
		*fork2 = philo->right_fork;
	}
	else
	{
		*fork1 = philo->right_fork;
		*fork2 = philo->left_fork;
	}
}
