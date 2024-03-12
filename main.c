/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/12 17:05:44 by fnikzad          ###   ########.fr       */
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

void	init_philos(t_data *data)
{
	int i = 0;

	data->philos = (t_philo *) malloc(sizeof(t_philo) * (data->n_philo));
	data->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->philos || !data->forks)
		return ;
	data->signal_for_stop = 0;
	data->all_done = 0;
	
	data->start_time = get_current_time();
	pthread_mutex_init(&data->p_action, NULL);
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].right_fork = (i + 1) % data->n_philo;
		data->philos[i].left_fork = i;
		data->philos[i].last_eat = 0;
		data->philos[i].num_eat = 0;
		data->philos[i].p_data = data;
		data->philos[i].done_eating = 0;
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

void	ft_eat(t_philo *philo)
{
	int	fork1;
	int	fork2;

	init_forks(&fork1, &fork2, philo);
	
	if (philo->p_data->signal_for_stop == 0)
	{
		pthread_mutex_lock(&philo->p_data->forks[fork1]);
		print_ac("has taken a fork", philo, get_current_time());
		pthread_mutex_lock(&philo->p_data->forks[fork2]);
		print_ac("has taken a fork", philo, get_current_time());
		print_ac("is eating", philo, get_current_time());
		philo->last_eat = get_current_time();
		ft_usleep(philo->p_data->time_to_eat);
		philo->num_eat++;
		pthread_mutex_unlock(&philo->p_data->forks[fork2]);
		pthread_mutex_unlock(&philo->p_data->forks[fork1]);
	}

	
}

void	ft_sleep(t_philo *philo)
{
	if (philo->p_data->signal_for_stop == 0)
	{
		print_ac("is sleeping", philo, get_current_time());
		ft_usleep(philo->p_data->time_to_sleep);
	}
}

void	ft_think(t_philo *philo)
{
	if (philo->p_data->signal_for_stop == 0)
	{
		print_ac("is thinking", philo, get_current_time());
	}
}

void	*philo_function(void *data)
{
	t_philo	*philo;
	philo = (t_philo*) data;
	if (philo->id % 2 == 0)
	{
		ft_usleep(philo->p_data->time_to_eat);
	}
	while (1)
	{
		if (philo->p_data->must_eat > 0 && philo->num_eat == philo->p_data->must_eat)
		{
			// philo->p_data->signal_for_stop = 1;
			// philo->done_eating = 1;
			philo->p_data->all_done++;
			// break;
		}
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		// dying(philo);
	}
	return(NULL);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (valid_args(argv) == 0 || (argc != 5 && argc != 6))
	{
		ft_putendl_fd("Wrong Number of Args\n", 2);
		return (1);
	}
	ft_atoi_all(argv, &data);
	int i = 0;
	init_philos(&data);
	while (i < data.n_philo)
	{
		if (pthread_create(&data.philos[i].p_th, NULL, &philo_function, (void*) &data.philos[i]) != 0)
		{
			ft_putendl_fd("Error\n", 2);
			return (1);
		}
		i++;
	}
	ft_usleep(data.time_to_die + 1);
	if (dying (data.philos) == 1)
	{
		// printf("----%d\n", data.philos->num_eat);
		return (1);
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(data.philos[i].p_th, NULL);
		i++;
	}
	printf("%d\n", data.philos->num_eat);
	return (0);
}
