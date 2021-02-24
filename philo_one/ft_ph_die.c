/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ph_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:27:11 by gmarva            #+#    #+#             */
/*   Updated: 2021/02/24 19:28:01 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_philo_die(void *philosoph)
{
	struct timeval	tv;
	t_philosoph		*one_phil;
	long			tm;

	one_phil = (t_philosoph *)philosoph;
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	one_phil->eat_start = tm;
	while (g_all.i == 1)
	{
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (tm - one_phil->eat_start > one_phil->philo.time_die)
		{
			g_all.i = 0;
			printf("%ld %d died\n", tm - one_phil->tm_start, one_phil->num);
			pthread_mutex_unlock(&g_all.mutex_life);
			break ;
		}
	}
	return (0);
}
