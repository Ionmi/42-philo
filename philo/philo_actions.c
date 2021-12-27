/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:03:14 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/24 15:58:24 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died);
	if (!philo->data->alive)
	{
		pthread_mutex_unlock(&philo->data->died);
		return (0);
	}
	if (get_time_diff(&philo->last_meal) >= philo->data->die_t)
	{
		philo->data->alive = 0;
		pthread_mutex_lock(&philo->data->print);
		printf("%s%d%s %d died\n",
			BLUE, get_time_diff(&philo->born_t), WHITE, philo->id);
		usleep(200);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->died);
		return (0);
	}
	return (1);
}

int	get_fork(t_data *data, t_philo *philo, int fork)
{
	pthread_mutex_lock(&data->forks[fork]);
	if (!still_alive(philo))
	{
		pthread_mutex_unlock (&data->forks[fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->died);
	print(philo, "has taken a fork");
	return (1);
}

int	eat_sleep_think(t_data *data, t_philo *philo)
{	
	print(philo, "is eating");
	if (!ft_usleep(data->eat_t, philo))
	{
		pthread_mutex_unlock (&data->forks[philo->r_fork]);
		pthread_mutex_unlock (&data->forks[philo->l_fork]);
		return (0);
	}
	if (!still_alive(philo))
	{
		pthread_mutex_unlock (&data->forks[philo->r_fork]);
		pthread_mutex_unlock (&data->forks[philo->l_fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->died);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock (&data->forks[philo->r_fork]);
	pthread_mutex_unlock (&data->forks[philo->l_fork]);
	if (!philo->meals)
		return (0);
	if (!print(philo, "is sleeping") || !ft_usleep(data->sleep_t, philo))
		return (0);
	if (!print(philo, "is thinking"))
		return (0);
	return (1);
}
