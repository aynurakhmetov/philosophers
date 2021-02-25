/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:57:16 by gmarva            #+#    #+#             */
/*   Updated: 2021/02/25 19:28:04 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		ft_start_procces(t_philosoph *philosoph)
{
	int				i;
	struct timeval	tv;
	long			tm_start;

	i = -1;
	g_all.each_ph_eat = 0;
	pthread_mutex_init(&g_all.mutex_life, NULL);
	pthread_mutex_init(&g_all.mutex_print, NULL);
	pthread_mutex_lock(&g_all.mutex_life);
	g_all.super_phil = philosoph;
	gettimeofday(&tv, NULL);
	tm_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_create(&g_all.ms_die, NULL, ft_exit, NULL);
	printf("NUM %d\n", philosoph[0].philo.num_of_phil);
	while (++i < philosoph[0].philo.num_of_phil)
	{
		philosoph[i].tm_start = tm_start;
		pthread_create(&philosoph[i].ph, NULL, ft_philo_life, &philosoph[i]);
	}
	i = -1;
	while (++i < philosoph[0].philo.num_of_phil)
		pthread_join(philosoph[i].ph, NULL);
	pthread_join(g_all.ms_die, NULL);
	ft_exit();
}

t_philosoph		*ft_philo_create(t_philo philo)
{
	t_philosoph		*philosoph;
	int				i;

	i = -1;
	philosoph = (t_philosoph *)malloc(sizeof(t_philosoph)
			* (philo.num_of_phil + 1));
	while (++i < philo.num_of_phil)
	{
		philosoph[i].philo = philo;
		philosoph[i].num = i + 1;
		pthread_mutex_init(&philosoph[i].mutex_left, NULL);
		if (i == philo.num_of_phil - 1)
			philosoph[i].mutex_right = &philosoph[0].mutex_left;
		else
			philosoph[i].mutex_right = &philosoph[i + 1].mutex_left;
	}
	return (philosoph);
}

static void		ft_philo_start(int argc, char *argv[])
{
	t_philo		philo;
	t_philosoph	*philosoph;

	philo.num_of_phil = ft_atoi(argv[1]);
	if (philo.num_of_phil <= 1)
	{
		printf("Error: %d philosophers\n", philo.num_of_phil);
		exit(0);
	}
	philo.time_die = ft_atoi(argv[2]);
	philo.time_eat = ft_atoi(argv[3]);
	philo.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo.num_of_time = ft_atoi(argv[5]);
		if (philo.num_of_time == 0 || philo.num_of_time == -1)
		{
			printf("Error: 5th argument must be more than 0\n");
			exit(0);
		}
	}
	else
		philo.num_of_time = -1;
	philosoph = ft_philo_create(philo);
	ft_start_procces(philosoph);
}

static int		ft_check_arguments(int argc, char *argv[])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Problems with numbers of arguments\n");
		exit(0);
	}
	while (++i < argc)
	{
		j = -1;
		while (++j < (int)ft_strlen(argv[i]))
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Invalid argument number %d: %s\n", i, argv[i]);
				k++;
			}
		}
	}
	return (k);
}

int				main(int argc, char *argv[])
{
	int	k;
	int i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '\0')
		{
			printf("Invalid argument number %d\n", i);
			exit(0);
		}
	}
	k = ft_check_arguments(argc, argv);
	if (k > 0)
	{
		printf("Enter a correct number\n");
		return (0);
	}
	else if (argv[1] == 0)
		printf("Number of philosophers = 0\n");
	else
		ft_philo_start(argc, argv);
	return (0);
}
