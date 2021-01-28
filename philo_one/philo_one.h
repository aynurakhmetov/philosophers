#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct  s_philo
{
    int num_of_phil;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_of_time;
}               t_philo;

typedef struct  s_philosoph
{
    t_philo         philo;
    pthread_t       ph;
    pthread_mutex_t mutex_left;
    pthread_mutex_t *mutex_right;
}               t_philosoph;

int     ft_atoi(const char *str);
size_t  ft_strlen(const char *str);