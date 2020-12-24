/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:32:30 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 18:20:25 by kjubybot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->sim->write_m);
	ft_putnbr(get_time() - philo->sim->start_time);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(&philo->sim->write_m);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->lfork]);
	display_message(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->sim->forks[philo->rfork]);
	display_message(philo, " has taken a fork\n");
	display_message(philo, " is eating\n");
	philo->time_of_death = get_time() + philo->sim->time_to_die;
	philo->times_eaten++;
	if (philo->times_eaten == philo->sim->times_eat)
		philo->sim->philos_full++;
	philo->state = STATE_EATING;
	usleep(philo->sim->time_to_eat * 1000);
}

void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->rfork]);
	philo->state = STATE_SLEEPING;
	display_message(philo, " is sleeping\n");
	usleep(philo->sim->time_to_sleep * 1000);
	philo->state = STATE_THINKING;
	display_message(philo, " is thinking\n");
}