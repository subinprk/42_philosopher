/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:23:45 by siun              #+#    #+#             */
/*   Updated: 2024/02/28 16:31:28 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive_checker(t_philo *philo_i)
{
	if (!pthread_mutex_lock(philo_i->state_mu) && philo_i->state != S_DEAD
		&& !pthread_mutex_unlock(philo_i->state_mu))
		return (1);
	else
	{
		pthread_mutex_unlock(philo_i->state_mu);
		return (0);
	}
}

void	action_print(t_philo *philo, t_arg arg, char *str)
{
	pthread_mutex_lock(arg.print_mu);
	printf("%llu %d %s\n", get_current_time() - philo->start_time,
		philo->index + 1, str);
	pthread_mutex_unlock(arg.print_mu);
}

int	philo_sleep(t_philo *philo_i, t_arg arg)
{
	action_print(philo_i, arg, "is sleeping");
	while (!pthread_mutex_lock(philo_i->state_mu) && philo_i->state != S_DEAD
		&& !pthread_mutex_unlock(philo_i->state_mu))
	{
		usleep(1000);
		if ((long long)(get_current_time() - philo_i->last_time_eat)
			>= arg.time_to_sleep)
		{
			action_print(philo_i, arg, "is thinking");
			return (1);
		}
	}
	pthread_mutex_unlock(philo_i->state_mu);
	return (0);
}

int	philo_eat(t_philo *philo_i, t_arg arg)
{
	if (alive_checker(philo_i) && philo_i->index % 2
		&& pthread_mutex_lock(philo_i->l_chopstick))
		return (0);
	action_print(philo_i, arg, "has taken a fork");
	if (alive_checker(philo_i) && pthread_mutex_lock(philo_i->r_chopstick))
		return (0);
	if (alive_checker(philo_i) && !(philo_i->index % 2)
		&& pthread_mutex_lock(philo_i->l_chopstick))
		return (0);
	action_print(philo_i, arg, "has taken a fork");
	action_print(philo_i, arg, "is eating");
	philo_i->last_time_eat = get_current_time();
	while ((long long)get_current_time()
			- philo_i->last_time_eat < arg.time_to_eat)
		usleep(1000);
	pthread_mutex_unlock(philo_i->r_chopstick);
	pthread_mutex_unlock(philo_i->l_chopstick);
	philo_i->last_time_eat = get_current_time();
	philo_i->num_of_eat = philo_i->num_of_eat + 1;
	return (1);
}

void	*philosopher(void *tmp_philo)
{
	int		i;
	t_philo	*philo_i;
	t_arg	*arg;

	philo_i = tmp_philo;
	i = 0;
	arg = philo_i->arg;
	if (philo_i->index % 2 == 0)
		usleep(1000);
	while (alive_checker(philo_i))
	{
		if (philo_eat(philo_i, *arg))
		{
			return (NULL);
		}
		if (philo_sleep(philo_i, *arg))
			return (NULL);
	}
	printf("\tphilo %d is dead\n", philo_i->index);
	return (NULL);
}
