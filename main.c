/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/16 12:20:13 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_atoi_all(char **s, t_data *data)
{
	data->n_philo = ft_atoi(s[1]);
	data->time_to_die = ft_atoi(s[2]);
	data->time_to_eat = ft_atoi(s[3]);
	data->time_to_sleep = ft_atoi(s[4]);
	if (s[5])
		data->must_eat = ft_atoi(s[5]);
	else
		data->must_eat = 0;
}

void	*philo_function(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->p_data->time_to_eat);
	if (philo->p_data->n_philo == 1)
	{
		ft_eat(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->p_data->die);
		if (philo->p_data->stop == 1 || (philo->p_data->must_eat > 0
				&& philo->num_eat == philo->p_data->must_eat))
		{
			pthread_mutex_unlock(&philo->p_data->die);
			break ;
		}
		pthread_mutex_unlock(&philo->p_data->die);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	join_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philos[i].p_th, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->p_action);
	pthread_mutex_destroy(&data->die);
	pthread_mutex_destroy(&data->n_eat);
	pthread_mutex_destroy(&data->l_eat);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (valid_args(argv) == 0 || (argc != 5 && argc != 6))
	{
		ft_putendl_fd("Wrong Number of Args\n", 2);
		return (1);
	}
	ft_atoi_all(argv, &data);
	i = -1;
	init_philos(&data);
	while (++i < data.n_philo)
	{
		if (pthread_create(&data.philos[i].p_th,
				NULL, &philo_function, (void*) &data.philos[i]) != 0)
		{
			ft_putendl_fd("Error\n", 2);
			return (1);
		}
	}
	ft_usleep(data.time_to_die + 1);
	dying (&data);
	join_and_destroy(&data);
	return (0);
}
