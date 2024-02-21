/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by subpark           #+#    #+#             */
/*   Updated: 2024/02/21 18:20:42 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_checker(t_philo *philo, t_arg arg)
{
	int			i;
	int			bool_done;
	int			bool_death;

	bool_done = 1;
	bool_death = 0;
	while (1)
	{
		i = 0;
		while (i < arg.num_of_philo)
		{
			bool_done = bool_done * (philo[i].state == S_DONE);
			bool_death = bool_death + (philo[i].state == S_DEAD);
			i ++;
		}
		if (bool_done || bool_death)
			break;
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