/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:23:45 by siun              #+#    #+#             */
/*   Updated: 2024/02/27 16:42:34 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
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
	while (philo_i->state != S_DEAD)
	{
		usleep(1000);
		if ((long long)(get_current_time() - philo_i->last_time_eat)
			>= arg.time_to_sleep)
		{
			action_print(philo_i, arg, "is thinking");
			return (1);
		}
	}
	return (0);
}

int	philo_eat(t_philo *philo_i, t_arg arg)
{
	if (philo_i->index % 2 && pthread_mutex_lock(philo_i->l_chopstick))
		return (0);
	action_print(philo_i, arg, "has taken a fork");
	if (pthread_mutex_lock(philo_i->r_chopstick))
		return (0);
	if (!(philo_i->index % 2) && pthread_mutex_lock(philo_i->l_chopstick))
		return (0);
	action_print(philo_i, arg, "has taken a fork");
	action_print(philo_i, arg, "is eating");
	philo_i->last_time_eat = get_current_time();
	while (philo_i->state != S_DEAD && (long long)get_current_time()
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
		usleep(10000);
	while (!pthread_mutex_lock(philo_i->state_mu) && philo_i->state != S_DEAD
		&& !pthread_mutex_unlock(philo_i->state_mu))
	{
		if (!philo_eat(philo_i, *arg))
		{
			usleep(1000);
			continue ;
		}
		if (!philo_sleep(philo_i, *arg))
			break ;
	}
	//printf("\tphilo %d is dead\n", philo_i->index);
	return (NULL);
}
