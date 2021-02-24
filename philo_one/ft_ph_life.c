
#include "philo_one.h"

void	ft_time(long time_end)
{
	struct	timeval	tv;
	long	tm;

	gettimeofday(&tv, NULL);
	tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	while (tm < time_end)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}

int		ft_philo_eat(t_philosoph *one_phil)
{
	struct	timeval	tv;
	long	tm;

	//printf("2Hello %s %ld\n", one_phil->entry_point->__opaque, one_phil->entry_point->__sig);
	//pthread_mutex_lock(one_phil->entry_point);
	//printf("3Hello %s %ld\n", one_phil->entry_point->__opaque, one_phil->entry_point->__sig);
	if (one_phil->num != one_phil->philo.num_of_phil)
	{
		pthread_mutex_lock(&one_phil->mutex_left);
		gettimeofday(&tv, NULL);
		g_all.eat_start = tm = tv.tv_sec * 1000 + tv.tv_usec / 1000 + one_phil->philo.time_eat;
		printf("%ld %d has taken a fork\n", tm - one_phil->tm_start, one_phil->num);

		pthread_mutex_lock(one_phil->mutex_right);
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		printf("%ld %d has taken a fork\n", tm - one_phil->tm_start, one_phil->num);
	}
	else
	{
		pthread_mutex_lock(one_phil->mutex_right);
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		printf("%ld %d has taken a fork\n", tm - one_phil->tm_start, one_phil->num);

		pthread_mutex_lock(&one_phil->mutex_left);
		gettimeofday(&tv, NULL);
		g_all.eat_start = tm = tv.tv_sec * 1000 + tv.tv_usec / 1000 + one_phil->philo.time_eat;
		printf("%ld %d has taken a fork\n", tm - one_phil->tm_start, one_phil->num);
		
	}
	
	//pthread_mutex_unlock(one_phil->entry_point);
	gettimeofday(&tv, NULL);
	ft_time(tv.tv_sec * 1000 + tv.tv_usec / 1000 + one_phil->philo.time_eat);
	//usleep(one_phil->philo.time_eat * 1000);
	gettimeofday(&tv, NULL);
	g_all.eat_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
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

void	*ft_philo_die(void *philosoph)
{
	struct		timeval	tv;
	t_philosoph	*one_phil;
	long			tm;

	one_phil = (t_philosoph *)philosoph;
	gettimeofday(&tv, NULL);
	g_all.eat_start = tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&tv, NULL);
		tm = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (tm - g_all.eat_start > one_phil->tm_die)
		{
			printf("%ld %d  died\n", tm - one_phil->tm_start, one_phil->num);
			pthread_mutex_unlock(&g_all.mutex_life);
		}
	}	
}

void    *ft_philo_life(void *philosoph)
{
	t_philosoph	*one_phil;
	int			k;
	int			res_eat;
	struct		timeval tv;
	long		tm_sl;
	long		tm_th;
	pthread_t	die;
	
	k = 0;
	res_eat = 0;
	one_phil = (t_philosoph *)philosoph;
	//printf("%ld\n", one_phil->tm_start);
	pthread_create(&die, NULL, ft_philo_die, &philosoph);
	while (1)
	{
		k = ft_philo_eat(one_phil);
		res_eat += k;
		if (res_eat == one_phil->philo.num_of_time)
			break ;
		//usleep(one_phil->philo.time_sleep * 1000);
		gettimeofday(&tv, NULL);
		ft_time(tv.tv_sec * 1000 + tv.tv_usec / 1000 + one_phil->philo.time_sleep);
		gettimeofday(&tv, NULL);
		tm_sl = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		printf("%ld %d is sleeping\n", tm_sl - one_phil->tm_start, one_phil->num);
		gettimeofday(&tv, NULL);
		tm_th = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		printf("%ld %d is thinking\n", tm_th - one_phil->tm_start, one_phil->num);
	}
	pthread_join(die, NULL);
	return (0);
}
