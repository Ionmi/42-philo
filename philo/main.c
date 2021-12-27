/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:38:53 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/17 19:20:37 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	f_mem(pthread_mutex_t *forks, pthread_t *philos)
{
	if (forks)
		free(forks);
	if (philos)
		free(philos);
	return (1);
}

int	error(t_data *data)
{
	if (data->philo_n < 1 || data->die_t < 60 || data->eat_t < 60
		|| data->sleep_t < 60)
		return (1);
	data->alive = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (str_e("argument\n"));
	data = (t_data){.philo_n = ft_atoi(argv[1]), .die_t = ft_atoi(argv[2]),
		.eat_t = ft_atoi(argv[3]), .sleep_t = ft_atoi(argv[4]), .meal_n = -1};
	if (argv[5])
	{
		data.meal_n = ft_atoi(argv[5]);
		if (data.meal_n < 1)
			return (str_e("wrong argument parmeters"));
	}
	if (error(&data))
		return (str_e("wrong argument parmeters"));
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_n);
	data.philos = malloc(sizeof(pthread_t) * data.philo_n);
	if (!data.forks || !data.philos)
		return (f_mem(data.forks, data.philos)
			&& str_e("memory allocation failed"));
	if (philosophers(&data, data.philos))
		return (f_mem(data.forks, data.philos)
			&& str_e("thread creation failed"));
	f_mem(data.forks, data.philos);
	return (0);
}
