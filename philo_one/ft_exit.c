
#include "philo_one.h" 

void    ft_exit(t_philosoph *philosoph)
{
    int i;

    i = -1;
    while (++i < philosoph[0].philo.num_of_phil)
	{
        pthread_mutex_destroy(&philosoph[i].mutex_left);
    }
    if (philosoph)
        free(philosoph);
}