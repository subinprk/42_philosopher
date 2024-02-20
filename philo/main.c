/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:18:03 by subpark           #+#    #+#             */
/*   Updated: 2024/02/16 16:42:35 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_philo	*philo;
	t_arg	arg;
	int		philosopher_result;

	if (argc != 5 && argc != 6)
		return (1);
	if (!init_arg(argc, argv, &arg))
		return (1);
	if (!generate_philo(&philo, arg))
		return (1);
	if (!generate_chopstick(&philo, arg));
		return (1);
	philosopher_result = philosopher(&philo, arg);
	if (philosopher_result == -1)
		return (1);
	else if	(philosopher_result == 0)
		philo_dead(&philo, arg);
	else
		philo_end(&philo, arg);
	return (0);
}