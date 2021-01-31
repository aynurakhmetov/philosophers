
#include "philo_one.h" 

void    *ft_exit()
{
    int i;

    i = -1;
    pthread_mutex_lock(&g_all.mutex_life);
    while (++i < g_all.super_phil[0].philo.num_of_phil)
	{
        pthread_mutex_destroy(&g_all.super_phil[i].mutex_left);
    }
    if (g_all.super_phil)
       free(g_all.super_phil);
    exit(0);
}