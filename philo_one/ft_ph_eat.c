/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ph_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:13:00 by gmarva            #+#    #+#             */
/*   Updated: 2021/02/24 19:26:46 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static long	ft_philo_try_takes_forks(pthread_mutex_t *fork_one,
	pthread_mutex_t *fork_two, t_philosoph *one_phil)
{
	struct timeval	tv;
	long			tm;

	pthread_mutex_lock(fork_one);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld %d has taken a fork\n",
			tm - one_phil->tm_start, one_phil->num);
	pthread_mutex_lock(fork_two);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld %d has taken a fork\n",
			tm - one_phil->tm_start, one_phil->num);
	return (tm);
}

static void	ft_philo_takes_forks(t_philosoph *one_phil)
{
	long			tm;

	if (one_phil->num != one_phil->philo.num_of_phil)
		tm = ft_philo_try_takes_forks(&one_phil->mutex_left,
		one_phil->mutex_right, one_phil);
	else
		tm = ft_philo_try_takes_forks(one_phil->mutex_right,
		&one_phil->mutex_left, one_phil);
	one_phil->eat_start = tm + one_phil->philo.time_eat;
}

int			ft_philo_eat(t_philosoph *one_phil)
{
	struct timeval	tv;
	long			tm;

	ft_philo_takes_forks(one_phil);
	gettimeofday(&tv, NULL);
	ft_time(tv.tv_sec * 1000 + tv.tv_usec / 1000
			+ one_phil->philo.time_eat);
	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	one_phil->eat_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld %d is eating\n", tm - one_phil->tm_start, one_phil->num);
	if (one_phil->num != one_phil->philo.num_of_phil)
	{
		pthread_mutex_unlock(one_phil->mutex_right);
		pthread_mutex_unlock(&one_phil->mutex_left);
	}
	else
	{
		pthread_mutex_unlock(&one_phil->mutex_left);
		pthread_mutex_unlock(one_phil->mutex_right);
	}
	return (1);
}
