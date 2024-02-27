/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:18:03 by subpark           #+#    #+#             */
/*   Updated: 2024/02/27 11:48:10 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeing_arg(t_philo *philo, t_arg arg)
{
	int	i;

	i = 0;
	free(arg.print_mu);
	while (i < arg.num_of_philo)
	{
		free(philo[i].l_chopstick);
		
		i ++;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (1);
	if (!init_arg(argc, argv, &arg))
		return (1);
	if (!generate_philo(&philo, arg))
		return (1);
	if (!generate_chopstick(&philo, arg))
		return (1);
	if (!thread_working(&philo, arg))
		return (1);
	freeing_arg(philo, arg);
	return (0);
}
