/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:38:53 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/23 14:24:32 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*aux;

	aux = malloc(count * size);
	if (aux)
		memset(aux, 0, count * size);
	return (aux);
}

int	error(t_data *data)
{
	if (data->philo_n < 1 || data->die_t < 60 || data->eat_t < 60
		|| data->sleep_t < 60)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (str_e("argument\n"));
	data = (t_data){.philo_n = ft_atoi(argv[1]), .die_t = ft_atoi(argv[2]),
		.eat_t = ft_atoi(argv[3]), .sleep_t = ft_atoi(argv[4]), .meal_n = -1};
	data.pid = ft_calloc(data.philo_n, sizeof(int));
	if (argv[5])
	{
		data.meal_n = ft_atoi(argv[5]);
		if (data.meal_n < 1)
			return (str_e("wrong argument parmeters"));
	}
	if (error(&data))
		return (str_e("wrong argument parmeters"));
	philosophers(&data);
	free (data.pid);
	return (0);
}
