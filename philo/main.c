/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:55:24 by siun              #+#    #+#             */
/*   Updated: 2023/11/11 17:00:17 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_checker(t_philo *first_philo)
{
	t_philo	*curr;
	int		i;

	ft_usleep(2, *first_philo->args);
	curr = first_philo;
	i = 0;
//			printf("hi\n");
//	printf("num of philo : %zu\n", first_philo->args->num_of_philo);
	while (1)
	{
//				printf("hi %d\n", i);
		if (curr->dead)
			return (1);
		if ((i + 1) % first_philo->args->num_of_philo == 0)
		{
			curr = curr - i;
			i = 0;
		}
		else
		{
			curr = curr + 1;
			i ++;
		}
	}
	return (0);
}

int	eating_checker(t_philo *first_philo)
{
	t_philo	*curr;
	int		i;

	if (first_philo->args->eating_goal < 0)
		return (0);
	curr = first_philo;
	i = 0;
	while (i < first_philo->args->num_of_philo)
	{
		if (first_philo->args->eating_goal != 0)
			return (0);
		curr = (curr + sizeof(t_philo));//not sure point. maybe have to do it as a linkedlist
	}
	return (1);
}

void	*philosopher(void *philo)
{
	printf("thread %d generated\n", ((t_philo *)philo)->index);
	if (((t_philo *)philo)->index % 2)
		ft_usleep(1, *((t_philo *)philo)->args);
	//printf("hey\n");
	while (!((t_philo *)philo)->dead)
	{
	//	printf("here\n");
		if (get_current_time() - ((t_philo *)philo)->last_moment_eat >= ((t_philo *)philo)->args->time_to_die)
			((t_philo *)philo)->dead = 1;
		philo_eats(((t_philo *)philo));
		if (((t_philo *)philo)->num_of_meal == ((t_philo *)philo)->args->eating_goal)
			break ;
		philo_sleep(((t_philo *)philo));
		philo_think(((t_philo *)philo));
	}
	return (NULL);//idk
}

int	main(int argc, char **argv)
{
	t_args					args;
	t_philo					*philo;
	pthread_mutex_t			*chopstick;

	if (!put_arguments(&args, argv))
		return (errno);
	if (!generate_philo(&philo, &args))
		return (errno);
	//printf("philo->args->time to sleep : %zu\n", philo->args->time_to_sleep);
	if (!generate_chopstick(&chopstick, &philo, args))
		return (errno);
	if (!generate_threads(&philo, args))
		return (errno);
	if (dead_checker(philo) || eating_checker(philo))
		joining_threads(&philo, args);
	return (0);
}