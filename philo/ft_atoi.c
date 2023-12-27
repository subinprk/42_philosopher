/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:04:45 by siun              #+#    #+#             */
/*   Updated: 2023/11/10 12:19:47 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				index;

	str1 = s1;
	str2 = s2;
	index = 0;
	while (index < n)
	{
		if (*(str1 + index) == *(str2 + index))
			index ++;
		else
			return (str1[index] - str2[index]);
	}
	return (0);
}

int	spc(char c)
{
	if (c == '\t' || c == '\n' || c == ' ' || c == '\r' || c == '\v'
		||c == '\f')
		return (1);
	else
		return (0);
}

void	signs(const char *nptr, int *index, int *sign)
{
	if (nptr[*index] == '-')
		*sign = -1;
	if (nptr[*index] == '+' || nptr[*index] == '-')
		(*index)++;
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	index;
	int	sign;

	sign = 1;
	num = 0;
	index = 0;
	while ((nptr[index] != 0 && spc(nptr[index]) == 1))
		index ++;
	if (!ft_memcmp(&nptr[index], "-2147483648", 11))
		return (-2147483648);
	signs(nptr, &index, &sign);
	while (nptr[index] != 0)
	{
		if (nptr[index] < '0' || nptr[index] > '9')
			return (sign * num);
		else if (10 * num + (nptr[index] - '0') < num)
			return (0);
		else
			num = 10 * num + (nptr[index] - '0');
		index ++;
	}
	return (sign * num);
}