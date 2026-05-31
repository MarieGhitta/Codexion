/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 18:42:46 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>
#include <unistd.h>

long	get_current_time_ms(void)
{
	struct timeval	debut;
	long			timestamp;

	gettimeofday(&debut, NULL);
	timestamp = (debut.tv_sec * 1000) + (debut.tv_usec / 1000);
	return (timestamp);
}

long	get_simulation_time(t_simulation *sim)
{
	long	current_time;
	long	simulation_time;

	current_time = get_current_time_ms();
	simulation_time = current_time - sim->time_start_simulation;
	return (simulation_time);
}

void	smart_sleep(t_simulation *sim, long time_to_wait)
{
	long	time_start;
	long	current_time;

	time_start = get_simulation_time(sim);
	current_time = time_start;
	while (!get_stop(sim) && (current_time - time_start) <= time_to_wait)
	{
		if (get_stop(sim))
			break ;
		usleep(150);
		current_time = get_simulation_time(sim);
	}
}
