/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:57:16 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/27 12:57:17 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// static void	ft_start_procces
// {

// }

t_philosoph	*ft_philo_create(t_philo	philo)
{
	t_philosoph	*philosoph;
	int			i;

	i = -1;
	philosoph = (t_philosoph *)malloc(sizeof(t_philosoph) * (philo.num_of_phil + 1));
	while (++i < philo.num_of_phil)
	{
		philosoph[i].philo = philo;
		if (i == philo.num_of_phil - 1)
			philosoph[i].mutex_right = &philosoph[0].mutex_left;
		else
			philosoph[i].mutex_right = &philosoph[i + 1].mutex_left;
	}
	return (philosoph);
}

static void	ft_philo_start(int argc, char *argv[])
{
	t_philo		philo;
	t_philosoph	*philosoph;
	
	philo.num_of_phil = ft_atoi(argv[1]);
	philo.time_die = ft_atoi(argv[2]);
	philo.time_eat = ft_atoi(argv[3]);
	philo.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.num_of_time = ft_atoi(argv[5]);
	ft_philo_create(philo);
	philosoph = ft_philo_create(philo);
	// ft_start_procces
	
}

static int	ft_check_arguments(int argc, char *argv[])
{
	int	i;
	int	j;
	int k;
	
	i = 0;
	k = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Problems with numbers of arguments\n");
		exit (0);
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

int			main(int argc, char *argv[])
{
	int	k;

	k = ft_check_arguments(argc, argv);
	if (k > 0)
	{
		printf("Enter a non-negative number\n");
		return (0);
	}
	else
		ft_philo_start(argc, argv);
	return (0);
}
