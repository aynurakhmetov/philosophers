#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

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
	int				num;
    long            tm_start;
    long            tm_die;
}               t_philosoph;

typedef struct  s_global
{
    pthread_t       ms_die;
    pthread_mutex_t mutex_life;
    t_philosoph     *super_phil;
    long            die_count;
}               t_global;


t_global        g_all;
int             ft_atoi(const char *str);
size_t          ft_strlen(const char *str);
void            *ft_philo_life(void *philosoph);
void            *ft_exit();