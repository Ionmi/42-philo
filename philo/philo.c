/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:10:46 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/24 15:58:20 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep2(int milliseconds)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	while (get_time_diff(&t1) < milliseconds)
		usleep(100);
}

int	hola(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->died);
	get_fork(philo->data, philo, philo->r_fork);
	ft_usleep2(philo->data->die_t);
	printf("%s%d%s %d died\n",
		BLUE, get_time_diff(&philo->born_t), WHITE, philo->id);
	usleep(2000);
	philo->meals = 0;
	pthread_mutex_unlock (&philo->data->forks[philo->r_fork]);
	return (0);
}

void	*routine(void *d)
{
	t_data		*data;
	t_philo		philo;

	data = d;
	philo = (t_philo){.id = data->id, .meals = data->meal_n, .data = d,
		.r_fork = data->id - 1, .l_fork = data->id};
	pthread_mutex_unlock(&data->tmp_m);
	if (philo.l_fork == data->philo_n)
		philo.l_fork = 0;
	gettimeofday(&philo.last_meal, NULL);
	gettimeofday(&philo.born_t, NULL);
	if (philo.id % 2 != 1)
		usleep(data->eat_t / 2 * 1000);
	while ((data->philo_n == 1 && hola(&philo)) || philo.meals--)
	{
		if (!get_fork(data, &philo, philo.r_fork))
			break ;
		if (!get_fork(data, &philo, philo.l_fork))
			break ;
		if (!eat_sleep_think(data, &philo))
			break ;
	}
	pthread_mutex_destroy(&philo.data->died);
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init (&data->tmp_m, NULL);
	pthread_mutex_init (&data->died, NULL);
	pthread_mutex_init (&data->print, NULL);
	i = 0;
	while (i < data->philo_n)
		pthread_mutex_init (&data->forks[i++], NULL);
}

int	philosophers(t_data *data, pthread_t *philos)
{
	int	i;

	init_mutex(data);
	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->tmp_m);
		data->id = i + 1;
		if (pthread_create(&philos[i++], NULL, routine, data))
			return (1);
	}
	pthread_mutex_destroy(&data->tmp_m);
	pthread_mutex_destroy(&data->died);
	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->philo_n)
	{
		pthread_join (philos[i], NULL);
		pthread_mutex_destroy(&data->forks[i++]);
	}
	return (0);
}
