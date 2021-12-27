/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:11:12 by ioromero          #+#    #+#             */
/*   Updated: 2021/12/23 16:23:08 by ioromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* colors */
# define BLUE "\e[1;34m"
# define RED "\033[0;31m"
# define WHITE "\033[0;37m"
# define BOLD "\033[1m"
# define NORMAL "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

/* structs */
typedef struct s_data
{
	int				philo_n;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				meal_n;
	int				*pid;
	int				id;
	sem_t			*died;
	sem_t			*print;
	sem_t			*forks;
	struct timeval	born_t;
	struct timeval	last_meal;
}	t_data;

/* philo */
int		philosophers(t_data *data);

/* philo actions */
void	*still_alive(void *d);
void	get_fork(t_data *data);
void	eat_sleep_think(t_data *data);

/* utils */
int		str_e(char *str);
int		ft_atoi(const char *str);
int		print(t_data *data, char *str);
int		get_time_diff(struct timeval *t1);
int		ft_usleep(int milliseconds);

#endif

/* ./philo 200 310 200 100  */