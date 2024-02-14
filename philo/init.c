/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:29 by subpark           #+#    #+#             */
/*   Updated: 2024/02/14 16:36:03 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arg(int argc, char **argv, t_arg *arg)
{
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_eat = ft_atoi(argv[2]);
	arg->time_to_die = ft_atoi(argv[3]);
	if (argc == 6)
		arg->num_to_eat = ft_atoi(argv[4]);
	pthread_mutex_init(&(arg->food), NULL);
	if (!(*arg).food)
		return (0);
	pthread_mutex_init(&(arg->print), NULL);
	if (!(arg->food))
		return (0);
}