/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by subpark           #+#    #+#             */
/*   Updated: 2024/02/27 17:19:30 by subpark          ###   ########.fr       */
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
		printf("num of eat: %d\t", philo[i].num_of_eat);
		if (!(philo[i].num_of_eat == arg.num_to_eat))
			return (0);
		i ++;
	}
	return (i);
}

int	dead_checker(t_philo philo_i, t_arg arg)
{
	if ((long long)(get_current_time() - philo_i.last_time_eat)
		>= arg.time_to_die)
	{
		pthread_mutex_lock(philo_i.state_mu);
		philo_i.state = S_DEAD;
		pthread_mutex_unlock(philo_i.state_mu);
		action_print(&philo_i, arg, "is died");
		return (1);
	}
	return (0);
}

void	finish_checker(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (1)
	{
		i = i % arg.num_of_philo;
		usleep(1000);
		if (dead_checker((*philo)[i], arg))
			break ;
		if (eat_goal_checker((*philo), arg))
			break ;
		i ++;
	}
	i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_mutex_lock((*philo)[i].state_mu);
		(*philo)[i].state = S_DEAD;
		pthread_mutex_unlock((*philo)[i ++].state_mu);
	}
	usleep(1000);
	i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i ++;
	}
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
