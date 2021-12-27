/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:03:14 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/23 16:33:15 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*still_alive(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	while (1)
	{
		if (get_time_diff(&data->last_meal) >= data->die_t)
		{
			sem_wait(data->died);
			sem_wait(data->print);
			printf("%s%d%s %d died\n",
				BLUE, get_time_diff(&data->born_t), WHITE, data->id);
			exit (1);
		}
		usleep(100);
	}
}

void	get_fork(t_data *data)
{
	sem_wait(data->forks);
	print(data, "has taken a fork");
}

void	eat_sleep_think(t_data *data)
{	
	print(data, "is eating");
	ft_usleep(data->eat_t);
	sem_post(data->forks);
	sem_post(data->forks);
	gettimeofday(&data->last_meal, NULL);
	if (!data->meal_n)
		exit (0);
	print(data, "is sleeping");
	ft_usleep(data->sleep_t);
	print(data, "is thinking");
}
