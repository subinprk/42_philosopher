/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:23:15 by siun              #+#    #+#             */
/*   Updated: 2024/02/16 15:37:36 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error_freeing(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.num_of_philo)
	{
		free(philo[i]->r_chopstick);
		free(philo[i]);
		i ++;
	}
}

void	one_philo_free(t_philo *philo_i)
{
	free(philo_i->r_chopstick);
	free(philo_i);
}

void	philo_dead(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while (i <arg.num_of_philo)
	{
//thread detach? merge?
		one_philo_free(philo[i]);
		i ++;
	}
}

void	philo_end(t_philo **philo, t_arg arg)
{
	int	i;

	i = 0;
	while(i < arg.num_of_philo)
	{
//thread detach? merge?
		one_philo_free(philo[i]);
		i ++;
	}
}
