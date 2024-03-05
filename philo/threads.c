/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by subpark           #+#    #+#             */
/*   Updated: 2024/03/05 18:02:50 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_goal_checker(t_philo *philo, t_arg arg)
{
	int	i;

	i = 0;
	if (arg.num_to_eat == 0)
		return (0);
	while (i < arg.num_of_philo)
	{
		pthread_mutex_lock(philo->state_mu);
		if (philo[i].num_of_eat < arg.num_to_eat)
		{
			pthread_mutex_unlock(philo->state_mu);
			return (0);
		}
		i ++;
		pthread_mutex_unlock(philo->state_mu);
	}
	return (1);
}

int	dead_checker(t_philo philo_i, t_arg arg)
{
	long long	hungry_time;

	hungry_time = (long long)(get_current_time() - philo_i.last_time_eat);
	if (hungry_time >= arg.time_to_die)
	{
		philo_i.state = S_DEAD;
		action_print(&philo_i, arg, "is died");
		return (1);
	}
	return (0);
}

void	dead_marking_thread_join(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_mutex_lock((*philo)[i].state_mu);
		(*philo)[i].state = S_DEAD;
		pthread_mutex_unlock((*philo)[i].state_mu);
		i ++;
	}
	usleep(1000);
	i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i ++;
	}
}

void	finish_checker(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (1)
	{
		i = i % arg.num_of_philo;
		usleep(1000);
		pthread_mutex_lock((*philo)[i].state_mu);
		if (dead_checker((*philo)[i], arg))
		{
			pthread_mutex_unlock((*philo)[i].state_mu);
			break ;
		}
		pthread_mutex_unlock((*philo)[i].state_mu);
		if (eat_goal_checker((*philo), arg))
			break ;
		i ++;
	}
	dead_marking_thread_join(philo, arg);
	return ;
}

int	thread_working(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.num_of_philo)
	{
		if (pthread_create(&(*philo)[i].thread,
			NULL, &philosopher, &(*philo)[i]))
			return (0);
		i ++;
	}
	finish_checker(philo, arg);
	return (1);
}
