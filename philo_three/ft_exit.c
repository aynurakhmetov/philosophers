/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:28:29 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/12 16:34:22 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_close_sem(void)
{
	sem_close(g_all.super_phil[0].sem);
	sem_close(g_all.sem_life);
	sem_close(g_all.sem_print);
	sem_close(g_all.sem_waiter);
	sem_unlink("/semaphore");
	sem_unlink("/sema_life");
	sem_unlink("/sema_print");
	sem_unlink("/sema_waiter");
}

void	*ft_exit(void)
{
	int i;

	i = -1;
	sem_wait(g_all.sem_life);
	ft_close_sem();
	i = -1;
	while (++i < g_all.super_phil[0].philo.num_of_phil)
	{
		pthread_join(g_all.super_phil[i].die, NULL);
		kill(g_all.super_phil[i].pid, SIGTERM);
	}
	if (g_all.super_phil)
		free(g_all.super_phil);
	pthread_join(g_all.ms_die, NULL);
	exit(0);
}

void	ft_fork(t_philosoph *philosoph, long tm_start)
{
	int i;

	i = -1;
	while (++i < philosoph[0].philo.num_of_phil)
	{
		philosoph[i].tm_start = tm_start;
		philosoph[i].pid = fork();
		if (philosoph[i].pid == 0)
		{
			ft_philo_life(&philosoph[i]);
			exit(0);
		}
	}
}
