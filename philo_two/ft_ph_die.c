/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ph_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:27:11 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/11 14:17:58 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			sem_wait(&g_all.sem_print);
			printf("%ld %d died\n", tm - one_phil->tm_start, one_phil->num);
			sem_post(&g_all.sem_life);
			break ;
			sem_post(&g_all.sem_print);
		}
	}
	return (0);
}
