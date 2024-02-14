/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:32:58 by siun              #+#    #+#             */
/*   Updated: 2024/02/14 22:34:15 by siun             ###   ########.fr       */
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


size_t	get_current_time()
{
	struct timeval	current_time;

	if(!gettimeofday(&current_time, NULL))
		return (0);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}