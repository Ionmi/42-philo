/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:49:25 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/27 10:56:32 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hola(t_data *data)
{
	get_fork(data);
	sem_wait(data->print);
	ft_usleep(data->die_t);
	printf("%s%d%s %d died\n",
		BLUE, get_time_diff(&data->born_t), WHITE, data->id);
	data->meal_n = 0;
	exit (0);
}

void	routine(t_data *data, int id)
{
	pthread_t	tracker;

	data->id = id;
	gettimeofday(&data->last_meal, NULL);
	gettimeofday(&data->born_t, NULL);
	if (pthread_create(&tracker, NULL, still_alive, data))
		exit(1);
	if (data->id % 2 != 1)
		ft_usleep(data->eat_t - 10);
	while ((data->philo_n == 1 && hola(data)) || data->meal_n--)
	{
		get_fork(data);
		get_fork(data);
		eat_sleep_think(data);
	}
	exit(0);
}

void	init_sems(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("prints");
	sem_unlink("died");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->philo_n);
	data->print = sem_open("prints", O_CREAT | O_EXCL, 0644, 1);
	data->died = sem_open("died", O_CREAT | O_EXCL, 0644, 1);
}

int	philosophers(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	init_sems(data);
	while (i < data->philo_n)
	{
		data->pid[i] = fork();
		if (data->pid[i++] == 0)
			routine(data, i);
	}
	i = 0;
	while (i++ < data->philo_n)
		waitpid (-1, &status, -1);
	wait (NULL);
	i = 0;
	if (!status)
		while (i < data->philo_n)
			kill(data->pid[i++], SIGKILL);
	else
		ft_usleep(1000);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->died);
	return (0);
}
