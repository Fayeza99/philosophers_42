/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/17 12:49:50 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_all(char **s, t_data *data)
{
	data->n_philo = ft_atoi(s[1]);
	if (data->n_philo > 200)
		return (1);
	data->time_to_die = ft_atoi(s[2]);
	data->time_to_eat = ft_atoi(s[3]);
	data->time_to_sleep = ft_atoi(s[4]);
	if (s[5])
		data->must_eat = ft_atoi(s[5]);
	else
		data->must_eat = 0;
	return (0);
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
	free (data->philos);
	free (data->forks);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (valid_args(argv) == 0 || (argc != 5 && argc != 6))
		return (ft_putendl_fd("Error\n", 2), 1);
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (ft_putendl_fd("Error\n", 2), 1);
	if (ft_atoi_all(argv, &data) == 1)
		return (ft_putendl_fd("Error\n", 2), 1);
	i = -1;
	init_philos(&data);
	while (++i < data.n_philo)
	{
		if (pthread_create(&data.philos[i].p_th,
				NULL, &philo_function, (void*) &data.philos[i]) != 0)
			return (ft_putendl_fd("Error\n", 2), 1);
	}
	ft_usleep(data.time_to_die + 1);
	dying (&data);
	join_and_destroy(&data);
	return (0);
}
