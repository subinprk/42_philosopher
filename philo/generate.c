/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:34:14 by siun              #+#    #+#             */
/*   Updated: 2023/11/11 14:40:21 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	generate_philo(t_philo **philo, t_args *args)
{
	int	i;

	(*philo) = (t_philo *)malloc(sizeof(t_philo) * (args->num_of_philo));
	if (!(*philo))
		return (0);
	i = 0;
	while (i < args->num_of_philo)
	{
		memset(&((*philo)[i]), 0, sizeof(t_philo));
		(*philo)[i].args = args;
		i ++;
	}
	return (1);
}

int generate_chopstick(pthread_mutex_t **chopstick, t_philo **philo, t_args args)
{
	int	i;

	*chopstick = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
				* args.num_of_philo);
	if (!chopstick)
	{
		free_philo(philo, args);
		return (0);
	}
	i = 0;
	while (i < args.num_of_philo)
		if (pthread_mutex_init(&(*chopstick)[i ++], NULL))
			return (0);
	i = 0;
	while (i < args.num_of_philo)
	{
		(*philo)[i].r_chopstick = chopstick[i];
		(*philo)[i].l_chopstick = chopstick[(i + 1) % args.num_of_philo];
	//	printf("pointer of l chopstick address %p\n", chopstick[i]);
	//	printf("pointer of copied r chopstick address %p\n", (*philo)[i].r_chopstick);
		i ++;
	}
	return (1);
}

int	generate_threads(t_philo **philo, t_args args)
{
	int	i;
	int	buf;

	i = 0;
	while(i < args.num_of_philo)
	{
		(*philo)[i].index = i;
		buf = pthread_create(&(*philo)[i].thread, 0, philosopher, &(*philo)[i]);
		//philo[i]->args;
		if (buf != 0)
		{
			detach_threads(&(*philo)[i].thread, i);
			free_philo(philo, args);
			return (0);
		}
		i ++;
	}
	return (1);
}