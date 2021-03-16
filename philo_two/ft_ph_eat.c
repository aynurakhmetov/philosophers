/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ph_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:13:00 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/16 21:37:52 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static long	ft_philo_try_takes_forks(t_philosoph *one_phil)
{
	struct timeval	tv;
	long			tm;

	ft_sem_waiter(0);
	sem_wait(one_phil->sem);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_sem_print(0);
	if (g_all.i != 0)
		printf("%ld %d has taken a fork\n",
			tm - one_phil->tm_start, one_phil->num);
	ft_sem_print(1);
	sem_wait(one_phil->sem);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_sem_print(0);
	if (g_all.i != 0)
		printf("%ld %d has taken a fork\n",
			tm - one_phil->tm_start, one_phil->num);
	ft_sem_print(1);
	return (tm);
}

static void	ft_philo_takes_forks(t_philosoph *one_phil)
{
	long			tm;

	tm = ft_philo_try_takes_forks(one_phil);
	one_phil->eat_start = tm;
}

int			ft_philo_eat(t_philosoph *one_phil)
{
	struct timeval	tv;
	long			tm;

	ft_philo_takes_forks(one_phil);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_sem_print(0);
	if (g_all.i != 0)
		printf("%ld %d is eating\n", tm - one_phil->tm_start, one_phil->num);
	ft_sem_print(1);
	gettimeofday(&tv, NULL);
	if (g_all.each_ph_eat + 1 != one_phil->philo.num_of_phil)
		ft_time(tv.tv_sec * 1000 + tv.tv_usec / 1000
			+ one_phil->philo.time_eat);
	sem_post(one_phil->sem);
	sem_post(one_phil->sem);
	ft_sem_waiter(1);
	return (1);
}
