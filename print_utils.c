/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:33:51 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/17 12:33:10 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->p_data->die);
	if (philo->p_data->stop == 1)
	{
		pthread_mutex_unlock(&philo->p_data->die);
		return ;
	}
	pthread_mutex_lock(&philo->p_data->p_action);
	ft_putnbr_fd(now - philo->p_data->start_time, 1);
	write (1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	write (1, " ", 1);
	ft_putendl_fd(action, 1);
	write (1, "\n", 1);
	pthread_mutex_unlock(&philo->p_data->p_action);
	pthread_mutex_unlock(&philo->p_data->die);
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
		usleep(200);
}
