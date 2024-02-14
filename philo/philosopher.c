/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:23:45 by siun              #+#    #+#             */
/*   Updated: 2024/02/14 23:49:42 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_print(t_philo *philo, t_arg arg, char *str)
{
	pthread_mutex_lock(&(arg.print_mu));
	printf("timestamp %d %s", philo->index, str); //have to add timestamp
	pthread_mutex_unlock(&(arg.print_mu));
}

int philo_think(t_philo *philo_i, t_arg arg)
{
	action_print(philo_i, arg, "is thinking");
	if (get_current_time() - philo_i->last_time_eat > arg.time_to_die)
		return(0);
	return (1);
}

int philo_sleep(t_philo *philo_i, t_arg arg)
{
	action_print(philo_i, arg, "is sleeping");
	if (get_current_time() - philo_i->last_time_eat > arg.time_to_die)
		return(0);
	usleep(arg.time_to_sleep);
	return (1);
}

int philo_eat(t_philo *philo_i, t_arg arg)
{
	pthread_mutex_lock(philo_i->l_chopstick);
	action_print(philo_i, arg, "has taken a fork");
	pthread_mutex_lock(philo_i->r_chopstick);
	action_print(philo_i, arg, "has taken a fork");
	action_print(philo_i, arg, "is eating");
	pthread_mutex_unlock(philo_i->l_chopstick);
	pthread_mutex_unlock(philo_i->r_chopstick);
	philo_i->last_time_eat = philo_i->last_time_eat + arg.time_to_eat;
}

int philosopher(t_philo *philo_i, t_arg arg)
{
	while (1)
	{
		philo_eat(philo_i, arg);
		philo_sleep(philo_i, arg);
		if (!philo_think(philo_i, arg))
		{
			action_print(philo_i, arg, "is died");
			return (0);//make thread mdetach | merged?
		}
		if (philo_i->num_of_eat == arg.num_to_eat)
			return (1);//make thread merged
	}
	return (-1);
}