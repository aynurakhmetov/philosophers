/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:48:58 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/13 21:13:38 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int num_of_phil;
	int time_die; 
	int time_eat;
	int time_sleep;
	int num_of_time;
}				t_philo;
typedef struct	s_philosoph
{
	t_philo			philo;
	pthread_t		ph;
	pthread_t		die;
	pthread_mutex_t	mutex_left;
	pthread_mutex_t	*mutex_right;
	int				num;
	long			tm_start;
	long			eat_start;
}				t_philosoph;
typedef struct	s_global
{
	pthread_t		ms_die;
	pthread_mutex_t mutex_life;
	pthread_mutex_t mutex_print;
	int				i;
	int				each_ph_eat;
	t_philosoph		*super_phil;
}				t_global;
t_global		g_all;
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			*ft_philo_life(void *philosoph);
int				ft_philo_eat(t_philosoph *one_phil);
void			*ft_philo_die(void *philosoph);
void			ft_time(long time_end);
void			*ft_exit();
void			ft_exit2();
void			ft_check_life();

#endif
