/* ************************************************************************** */
/*                                                                            */
/*                                                       d :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:57:25 by siun              #+#    #+#             */
/*   Updated: 2023/11/06 22:57:25 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <semaphore.h>
# include <errno.h>

typedef struct s_args
{
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				eating_goal;
	pthread_mutex_t	meal;
}				t_args;

typedef struct s_philo
{
	int					index;
	int					state;
	int					dead;
	int					num_of_meal;
	int					last_moment_eat;
	pthread_t			thread;
	pthread_mutex_t		*r_chopstick;
	pthread_mutex_t		*l_chopstick;
	t_args				*args;
}				t_philo;

int		ft_atoi(const char *nptr);
int		put_arguments(t_args *arg, char **input);
int		generate_threads(t_philo **philo, t_args args);
int		generate_chopstick(pthread_mutex_t **chopstick,
							t_philo **philo, t_args arg);
int		generate_philo(t_philo **philo, t_args *args);
int		dead_checker(t_philo *first_philo);
int		eating_checker(t_philo *first_philo);
int		generate_threads(t_philo **philo, t_args args);
void	*philosopher(void *philo);
void	free_philo(t_philo **philo, t_args args);
void	free_philo_with_c(t_philo **philo, t_args args);
void	joining_threads(t_philo **philo, t_args args);
void	detach_threads(pthread_t *threads, int how_many);
size_t	get_current_time();
int		ft_usleep(size_t milliseconds, t_args args);
int		ft_strlen(char *str);
char	*ft_itoa(int n);
void	action_print(t_philo *philo, char *str);
void	philo_eats(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif