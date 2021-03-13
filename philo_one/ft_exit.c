/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:28:29 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/13 20:15:26 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_exit(void)
{
	int i;

	i = -1;
	pthread_mutex_lock(&g_all.mutex_life);
	while (++i < g_all.super_phil[0].philo.num_of_phil)
		pthread_mutex_destroy(&g_all.super_phil[i].mutex_left);
	pthread_mutex_destroy(&g_all.mutex_life);
	pthread_mutex_destroy(&g_all.mutex_print);
	i = -1;
	while (++i < g_all.super_phil[0].philo.num_of_phil)
	{
		pthread_join(g_all.super_phil[i].die, NULL);
		pthread_join(g_all.super_phil[i].ph, NULL);
	}
	if (g_all.super_phil)
		free(g_all.super_phil);
	pthread_join(g_all.ms_die, NULL);
	exit(0);
	return (0);
}

void	ft_exit2(void)
{
	int i;

	i = -1;
	while (++i < g_all.super_phil[0].philo.num_of_phil)
		pthread_mutex_destroy(&g_all.super_phil[i].mutex_left);
	pthread_mutex_destroy(&g_all.mutex_life);
	pthread_mutex_destroy(&g_all.mutex_print);
	i = -1;
	while (++i < g_all.super_phil[0].philo.num_of_phil)
	{
		pthread_join(g_all.super_phil[i].die, NULL);
		pthread_join(g_all.super_phil[i].ph, NULL);
	}
	if (g_all.super_phil)
		free(g_all.super_phil);
	pthread_join(g_all.ms_die, NULL);
	exit(0);
}

void	ft_check_life(void)
{
	while (1)
	{
		if (g_all.i == 0)
		{
			pthread_mutex_unlock(&g_all.mutex_life);
			break ;
		}
	}
}
