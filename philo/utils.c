/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:27:43 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/23 16:03:04 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_e(char *str)
{
	printf("%s%serror:%s%s %s%s%s", RED, BOLD,
		NORMAL, WHITE, BOLD, str, NORMAL);
	return (1);
}

int	get_time_diff(struct timeval *t1)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec * 1000 + t2.tv_usec / 1000)
		- (t1->tv_sec * 1000 + t1->tv_usec / 1000));
}

int	ft_usleep(int milliseconds, t_philo *philo)
{
	struct timeval	t1;
	int				i;

	if (!still_alive(philo))
		return (0);
	pthread_mutex_unlock(&philo->data->died);
	i = 0;
	gettimeofday(&t1, NULL);
	while (get_time_diff(&t1) < milliseconds)
	{
		usleep(100);
		if (i++ == 10)
		{
			if (!still_alive(philo))
				return (0);
			pthread_mutex_unlock(&philo->data->died);
			i = 0;
		}
	}
	return (1);
}

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (!still_alive(philo))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (0);
	}
	printf("%s%d%s %d %s\n",
		BLUE, get_time_diff(&philo->born_t), WHITE, philo->id, str);
	pthread_mutex_unlock(&philo->data->died);
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long	n;
	unsigned long long	i;
	int					sign;

	n = 0;
	i = 922337203685775807;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
		n = n * 10 + (*str++ - '0');
	if (n > i)
	{
		n = -1;
		if (sign == -1 && n != i + 1)
			n = 0;
	}
	return (sign * n);
}
