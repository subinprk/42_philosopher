/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chopstick_lock_unlock.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:38:26 by subpark           #+#    #+#             */
/*   Updated: 2024/03/05 18:29:46 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chopstick_lock_first(t_philo *philo_i, t_arg arg)
{
	if (!(philo_i->index % 2) && (pthread_mutex_lock(philo_i->l_chopstick)
			|| !alive_checker(philo_i)
			|| !action_print(philo_i, arg, "has taken a fork")))
	{
		pthread_mutex_unlock(philo_i->l_chopstick);
		return (0);
	}
	if (arg.num_of_philo == 1)
	{
		pthread_mutex_unlock(philo_i->r_chopstick);
		return (0);
	}
	return (1);
}

int	chopstick_lock_second(t_philo *philo_i, t_arg arg)
{
	if (pthread_mutex_lock(philo_i->r_chopstick)
		|| !alive_checker(philo_i)
		|| !action_print(philo_i, arg, "has taken a fork"))
	{
		if (!(philo_i->index % 2))
			pthread_mutex_unlock(philo_i->l_chopstick);
		if (philo_i->l_chopstick)
			pthread_mutex_unlock(philo_i->r_chopstick);
		return (0);
	}
	if ((philo_i->index % 2) && (pthread_mutex_lock(philo_i->l_chopstick)
			|| !alive_checker(philo_i)
			|| !action_print(philo_i, arg, "has taken a fork")))
	{
		pthread_mutex_unlock(philo_i->r_chopstick);
		pthread_mutex_unlock(philo_i->l_chopstick);
		return (0);
	}
	return (1);
}
