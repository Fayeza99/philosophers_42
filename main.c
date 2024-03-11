/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:09 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/11 15:31:35 by fnikzad          ###   ########.fr       */
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
}

void	init_philos(t_data *data)
{
	int i = 0;

	data->philos = (t_philo *) malloc(sizeof(t_philo) * (data->n_philo));
	data->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->philos || !data->forks)
		return ;
	data->signal_for_stop = 0;
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
	if (philo->id % 2 == 0)
	{
		// ft_sleep(philo);
		ft_usleep(philo->p_data->time_to_eat);
	}
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
		
		if (philo->num_eat == philo->p_data->must_eat)
		{
			philo->p_data->signal_for_stop = 1;
		}
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
	while (!(philo->p_data->signal_for_stop))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
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
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(data.philos[i].p_th, NULL);
		i++;
	}
	return (0);
}



// if (get_current_time() - philo->last_eat > philo->p_data->time_to_die)
// 		{
// 			write (1, "got here\n", 9);
// 			philo->p_data->signal_for_stop = 1;
			
// 		}