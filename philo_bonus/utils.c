/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:27:43 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/23 15:39:25 by ioromero         ###   ########.fr       */
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

int	ft_usleep(int milliseconds)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	while (get_time_diff(&t1) < milliseconds)
		usleep(100);
	return (1);
}

int	print(t_data *data, char *str)
{
	sem_wait(data->print);
	printf("%s%d%s %d %s\n",
		BLUE, get_time_diff(&data->born_t), WHITE, data->id, str);
	sem_post(data->print);
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
