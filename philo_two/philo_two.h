/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <gmarva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:48:58 by gmarva            #+#    #+#             */
/*   Updated: 2021/03/16 20:08:22 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

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
	int				num;
	long			tm_start;
	long			eat_start;
	sem_t			*sem;
}				t_philosoph;
typedef struct	s_global
{
	pthread_t		ms_die;
	sem_t			*sem_life;
	sem_t			*sem_print;
	int				check_sprint;
	sem_t			*sem_waiter;
	int				check_swaiter;
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
void			ft_close_sem();
void			ft_sem_print(int num);
void			ft_sem_waiter(int num);

#endif
