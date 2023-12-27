/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:57:10 by siun              #+#    #+#             */
/*   Updated: 2023/11/11 17:04:41 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i ++;
	return (i);
}


int		put_arguments(t_args *args, char **input)
{
	if (input[1] && input[2] && input[3] && input[4])
	{
		args->num_of_philo = ft_atoi(input[1]);
		args->time_to_die = ft_atoi(input[2]);
		args->time_to_eat = ft_atoi(input[3]);
		args->time_to_sleep = ft_atoi(input[4]);
	}
	
	else
		return (0);
	if (input[5])
		args->eating_goal = ft_atoi(input[5]);
	else
		args->eating_goal = -1;
	args->start_time = get_current_time();
	if (pthread_mutex_init(&(args->meal), NULL))
		return (0);
	return (1);
}

size_t	get_current_time()
{
	struct timeval	current_time;

	if(!gettimeofday(&current_time, NULL))
		return (0);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_args args)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds
			&& (get_current_time() - start < args.time_to_die))
		usleep(5);
	return (0);
}
