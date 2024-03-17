/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:10:04 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/17 12:40:36 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying_2(t_data *data)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (j < data->n_philo)
	{
		while (j < data->n_philo)
		{
			pthread_mutex_lock(&data->n_eat);
			if (data->philos[j].num_eat == data->must_eat)
				count++;
			pthread_mutex_unlock(&data->n_eat);
			j++;
		}
	}
	if (count == data->n_philo)
	{
		pthread_mutex_lock(&data->die);
		data->stop = 1;
		pthread_mutex_unlock(&data->die);
	}
}

void	dying_1(t_data *data)
{
	int	i;

	i = 0;
	while (data->stop == 0)
	{
		pthread_mutex_lock(&data->n_eat);
		if ((data->must_eat > 0 && (data->philos[i].num_eat
					< data->must_eat)) || data->must_eat == 0)
		{
			if (get_current_time() - data->philos[i].last_eat
				> data->time_to_die)
			{
				print_ac("died", &data->philos[i], get_current_time());
				data->stop = 1;
				pthread_mutex_unlock(&data->n_eat);
				return ;
			}
		}
		pthread_mutex_unlock(&data->n_eat);
		if (i == data->n_philo - 1)
			i = 0;
		i++;
		dying_2(data);
		usleep(250);
	}
}

void	dying(t_data *data)
{
	dying_1(data);
}
