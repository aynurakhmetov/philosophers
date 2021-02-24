/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:28:29 by gmarva            #+#    #+#             */
/*   Updated: 2021/02/24 19:31:40 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_exit(void)
{
	int i;

	i = -1;
	pthread_mutex_lock(&g_all.mutex_life);
	while (++i < g_all.super_phil[0].philo.num_of_phil)
	{
		pthread_mutex_destroy(&g_all.super_phil[i].mutex_left);
	}
	if (g_all.super_phil)
		free(g_all.super_phil);
	exit(0);
	return (0);
}
