/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:07:20 by subpark           #+#    #+#             */
/*   Updated: 2024/02/14 16:31:37 by subpark          ###   ########.fr       */
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

# define S_EAT = 1
# define S_SLEEP = 2
# define S_THINK = 3
# define S_DEAD = 0

typedef struct s_arg
{
	pthread_mutex_t food;
	pthread_mutex_t	print;
	int				num_of_philo;
	long long		time_to_eat;
	long long		time_to_die;
	int				num_to_eat;
} t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*r_chopstic;
	pthread_mutex_t	*l_chopstic;
	int				index;
	long long		start_time;
	long long		last_time_eat;
	int				state;
	t_arg			*arg;
} t_philo;

int	ft_atoi(const char *nptr);
int	init_arg(int argc, char **argv, t_arg *arg);

#endif