
#include "philo_one.h"

static int	ft_nb_test(long long nb, int k, int m, int i)
{
	if (i == m)
		return (-1);
	nb = nb * (k);
	if (((i - m) > 10 && k == 1) || nb > 2147483647)
		return (2147483647);
	if (((i - m) > 10 && k < 0) || nb < -2147483648)
		return (-2147483648);
	return (nb);
}

int			ft_atoi(const char *str)
{
	int			i;
	long long	nb;
	int			k;
	int			m;

	i = 0;
	nb = 0;
	k = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	m = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (ft_nb_test(nb, k, m, i));
}

size_t	ft_strlen(const char *str)
{
	size_t counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}
