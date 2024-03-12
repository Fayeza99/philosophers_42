/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:33:51 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/12 17:02:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd('0' + (n % 10), fd);
}

void	print_ac(char *action, t_philo *philo, long int now)
{

	pthread_mutex_lock(&philo->p_data->p_action);
	ft_putnbr_fd(now - philo->p_data->start_time, 1);
	// ft_putendl_fd(" Philo ", 1);
	write (1, " ", 1);
	
	ft_putnbr_fd(philo->id, 1);
	write (1, " ", 1);
	ft_putendl_fd(action, 1);
	write (1, "\n", 1);
	pthread_mutex_unlock(&philo->p_data->p_action);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long int duration)
{
	long int	i;

	i = get_current_time();
	while ((get_current_time() - i) < duration)
		usleep(duration / 10);
}

int	dying(t_philo *philo)
{
	int i;
	while (1)
	{
		i = 0;
		while (i < philo->p_data->n_philo)
		{
			if (philo->p_data->all_done == philo->p_data->n_philo)
			{
				// printf("kdnkwjejawef\n");
				return (1);
			}
			if (get_current_time() - philo->p_data->philos[i].last_eat > philo->p_data->time_to_die)
			{
				
				print_ac("died", &philo->p_data->philos[i], get_current_time());
				philo->p_data->signal_for_stop = 1;
				
				return (1);
			}
			
			i++;
		}
	}
	return (0);
}
