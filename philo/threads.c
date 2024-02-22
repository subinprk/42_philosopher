/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by subpark           #+#    #+#             */
/*   Updated: 2024/02/22 16:47:55 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_checker(t_philo *philo, t_arg arg)
{
	int			i;
	int			bool_all_done;
	int			bool_one_death;

	bool_all_done = 1;
	bool_one_death = 0;
	while (1)
	{
		i = 0;
		while (i < arg.num_of_philo)
		{
			bool_all_done = bool_all_done * (philo[i].state == S_DONE);
			bool_one_death = bool_one_death + (philo[i].last_time_eat
						- get_current_time() > arg.time_to_die);
			i ++;
		}
		if (bool_all_done || bool_one_death)
			break;
		usleep(1);
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