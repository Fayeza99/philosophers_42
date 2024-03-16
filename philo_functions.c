/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:15:50 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/16 12:10:57 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat2(t_philo *philo, int forks1, int forks2)
{
	pthread_mutex_lock(&philo->p_data->forks[forks2]);
	print_ac("has taken a fork", philo, get_current_time());
	print_ac("is eating", philo, get_current_time());
	pthread_mutex_lock(&philo->p_data->n_eat);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->p_data->n_eat);
	pthread_mutex_lock(&philo->p_data->n_eat);
	philo->num_eat++;
	pthread_mutex_unlock(&philo->p_data->n_eat);
	pthread_mutex_unlock(&philo->p_data->forks[forks2]);
	pthread_mutex_unlock(&philo->p_data->forks[forks1]);
	ft_usleep(philo->p_data->time_to_eat);
}

void	ft_eat(t_philo *philo)
{
	int	forks[2];

	init_forks(&forks[0], &forks[1], philo);
	if (philo->p_data->stop == 0)
	{
		pthread_mutex_lock(&philo->p_data->forks[forks[0]]);
		print_ac("has taken a fork", philo, get_current_time());
		if (philo->p_data->n_philo == 1)
		{
			ft_usleep(philo->p_data->time_to_die + 1);
			pthread_mutex_unlock(&philo->p_data->forks[forks[0]]);
			return ;
		}
		ft_eat2(philo, forks[0], forks[1]);
	}
}

void	ft_sleep(t_philo *philo)
{
	if (philo->p_data->stop == 0)
	{
		print_ac("is sleeping", philo, get_current_time());
		ft_usleep(philo->p_data->time_to_sleep);
	}
}

void	ft_think(t_philo *philo)
{
	if (philo->p_data->stop == 0)
	{
		print_ac("is thinking", philo, get_current_time());
	}
}
