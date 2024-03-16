/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:58:27 by fnikzad           #+#    #+#             */
/*   Updated: 2024/03/16 12:19:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	long				start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		p_action;
	pthread_mutex_t		die;
	pthread_mutex_t		l_eat;
	pthread_mutex_t		n_eat;
	int					all_done;
	int					stop;
}	t_data;

typedef struct s_philo
{
	t_data		*p_data;
	pthread_t	p_th;
	int			id;
	int long	last_eat;
	int			right_fork;
	int			left_fork;
	int			num_eat;
	int			done_eating;
}	t_philo;

//helper function
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		valid_args(char **s);
int		is_num(char *s);
void	ft_putnbr_fd(int n, int fd);
long	get_current_time(void);
void	ft_usleep(long int duration);
void	ft_putchar_fd(char c, int fd);

void	init_philos(t_data *data);
void	init_philos2(t_data *data);
void	init_forks(int *fork1, int *fork2, t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	print_ac(char *action, t_philo *philo, long int now);
void	dying(t_data *data);

#endif
