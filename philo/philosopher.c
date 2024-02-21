/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:23:45 by siun              #+#    #+#             */
/*   Updated: 2024/02/21 14:22:55 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_print(t_philo *philo, t_arg arg, char *str)
{
	pthread_mutex_lock(&(arg.print_mu));
	printf("%d %d %s", get_current_time() - philo->start_time
		, philo->index, str);
	pthread_mutex_unlock(&(arg.print_mu));
}

int	philo_think(t_philo *philo_i, t_arg arg)
{
	action_print(philo_i, arg, "is thinking");
	if (get_current_time() - philo_i->last_time_eat > arg.time_to_die)
		return (0);
	return (1);
}

int	philo_sleep(t_philo *philo_i, t_arg arg)
{
	action_print(philo_i, arg, "is sleeping");
	if (get_current_time() - philo_i->last_time_eat > arg.time_to_die)
		return (0);
	usleep(arg.time_to_sleep * 1000);
	//in case sth detached/should be joined in case sth is sleeping,
	//also have to think about it
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
	return (1);
}

int philosopher(t_philo **philo)
{
	int	i;
	t_arg *arg;

	i = 0;
	*arg = *(philo[0]->arg);
	// while (i < arg->num_of_philo)
	// {
		while (1)
		{
			philo_eat(philo[i], *arg);
			philo_sleep(philo[i], *arg);
			if (philo[i]->num_of_eat == arg->num_to_eat)
			{
				philo_dead(philo, *arg);
				return (1);
			}//make thread merged
			if (!philo_think(philo[i], *arg))
			{
				one_philo_free(philo[i]);
				return (0);//make thread mdetach | merged?
			}
		}
		philo_error_freeing(philo, *arg);
	// 	return (-1);
	// }
	return (1);
}