/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:32:50 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 18:08:38 by kjubybot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ft_atoi(char *s)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		sign = *s == '-' ? -1 : sign;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (res * sign);
}

void			ft_putnbr(unsigned long n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
	}
	else
		c = n + '0';
	write(1, &c, 1);
}

int				free_and_exit(t_sim *sim, int status, char *message)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->num_philos)
			pthread_mutex_destroy(&sim->forks[i++]);
		free(sim->forks);
	}
	if (sim->philos)
		free(sim->philos);
	write(1, message, ft_strlen(message));
	pthread_mutex_destroy(&sim->write_m);
	return (status);
}

int				ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}