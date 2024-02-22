/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:23:35 by siun              #+#    #+#             */
/*   Updated: 2024/02/22 16:07:29 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	generate_chopstick(t_philo **philo, t_arg arg)
{
	int				i;
	pthread_mutex_t	*chopstick;

	i = 0;
	while (i < arg.num_of_philo)
	{
		(*philo)[i].r_chopstick = malloc(sizeof(pthread_mutex_t));
		if (!(*philo)[i].r_chopstick)
			return (0);
		pthread_mutex_init((*philo)[i].r_chopstick, NULL);
		i ++;
	}
	i = 0;
	while (i < arg.num_of_philo)
	{
		(*philo)[i].l_chopstick = ((*philo)[(i + 1)
				% arg.num_of_philo]).r_chopstick;
		i ++;
	}
	return (1);
}

int	generate_philo(t_philo **philo, t_arg arg)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * arg.num_of_philo);
	if (!*philo)
		return (1);
	i = 0;
	while (i < arg.num_of_philo)
	{
		(*philo)[i] = (t_philo){0};
		(*philo)[i].arg = &arg;
		(*philo)[i].state = S_GEN;
		(*philo)[i].start_time = get_current_time();
		(*philo)[i].last_time_eat = 0;
		(*philo)[i].index = i;
		i ++;
	}
	return (1);
}

int	generate_print_mu(pthread_mutex_t **print_mu)
{
	(*print_mu) = malloc(sizeof(pthread_mutex_t));
	if (!(*print_mu))
		return (0);
	if (pthread_mutex_init((*print_mu), NULL))
		return (0);
	return (1);
}

int	init_arg(int argc, char **argv, t_arg *arg)
{
	arg->print_mu = NULL;
	arg->num_of_philo = atoi(argv[1]);
	arg->time_to_die = atoi(argv[2]);
	arg->time_to_eat = atoi(argv[3]);
	arg->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		arg->num_to_eat = atoi(argv[5]);
	if (!generate_print_mu(&(arg->print_mu)))
		return (0);
	return (1);
}
