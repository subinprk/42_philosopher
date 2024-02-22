/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by subpark           #+#    #+#             */
/*   Updated: 2024/02/22 17:42:20 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eat_goal_checker(t_philo philo_i, t_arg arg)
{
	if (philo_i.num_of_eat == arg.num_to_eat)
		return (1);
	return (0);
}

int		dead_checker(t_philo philo_i, t_arg arg)
{
	if (get_current_time() - philo_i.last_time_eat >= arg.time_to_die)
	{
		action_print(&philo_i, arg, "is died");
		return (1);
	}
	return (0);
}

void	finish_checker(t_philo *philo, t_arg arg)
{
	int			i;
	int			check_eat_goal;
	int			check_dead;

	check_eat_goal = 0;
	check_dead = 0;
	while (1)
	{
		i = 0;
		check_eat_goal = eat_goal_checker(philo[i], arg) + check_eat_goal;
		check_dead = dead_checker(philo[i], arg) + check_dead;
		if (check_eat_goal == arg.num_of_philo)
			break;
		if (check_dead)
			break;
		i ++;
	}
	i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
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
		if (pthread_create(&(*philo)[i].thread, NULL, &philosopher, &(*philo)[i]))
			return (0);
		i ++;
	}
	finish_checker(*philo, arg);
	return (1);
}