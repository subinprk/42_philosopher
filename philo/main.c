/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:18:03 by subpark           #+#    #+#             */
/*   Updated: 2024/02/14 23:15:49 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_philo *philo;
    t_arg   arg;

    if (argc != 5 || argc != 6)
        return (1);
    if (!init_arg(argc, argv, &arg))
        return (1);
    if (!generate_philo(&philo, arg))
        return (1);
    return (0);
}