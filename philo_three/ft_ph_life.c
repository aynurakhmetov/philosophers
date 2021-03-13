/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ph_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:05:41 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/12 19:12:35 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_time(long time_end)
{
	struct timeval	tv;
	long			tm;

	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (tm < time_end)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}

void	ft_philo_sleep_think(t_philosoph *one_phil)
{
	struct timeval	tv;
	long			tm_sl;
	long			tm_th;

	gettimeofday(&tv, NULL);
	tm_sl = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	sem_wait(g_all.sem_print);
	printf("%ld %d is sleeping\n",
			tm_sl - one_phil->tm_start, one_phil->num);
	sem_post(g_all.sem_print);
	gettimeofday(&tv, NULL);
	ft_time(tv.tv_sec * 1000 + tv.tv_usec / 1000
			+ one_phil->philo.time_sleep);
	gettimeofday(&tv, NULL);
	tm_th = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	sem_wait(g_all.sem_print);
	printf("%ld %d is thinking\n",
			tm_th - one_phil->tm_start, one_phil->num);
	sem_post(g_all.sem_print);
}

void	*ft_philo_life(void *philosoph)
{
	t_philosoph		*one_phil;
	int				res_eat;

	res_eat = 0;
	one_phil = (t_philosoph *)philosoph;
	pthread_create(&one_phil->die, NULL, ft_philo_die, one_phil);
	g_all.i = 1;
	while (g_all.i == 1)
	{
		res_eat += ft_philo_eat(one_phil);
		if (res_eat == one_phil->philo.num_of_time)
			exit(0);
		ft_philo_sleep_think(one_phil);
	}
	pthread_join(one_phil->die, NULL);
	return (0);
}
