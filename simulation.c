/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 17:50:09 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

static int	fill_coders_and_dongles(t_simulation *sim)
{
	sim->coders = malloc(sim->number_of_coders * sizeof(t_coder));
	if (!sim->coders)
		return (1);
	sim->dongles = malloc(sim->number_of_coders * sizeof(t_dongle));
	if (!sim->dongles)
	{
		free(sim->coders);
		return (1);
	}
	return (0);
}

static int	init_dongles(t_simulation *sim)
{
	int	i;
	int	lock_dongle_init;

	i = 0;
	while (i < sim->number_of_coders)
	{
		lock_dongle_init
			= pthread_mutex_init(&sim->dongles[i].lock_dongle, NULL);
		if (lock_dongle_init != 0)
			return (1);
		sim->dongles[i].is_taken = 0;
		sim->dongles[i].last_release_time = -sim->dongle_cooldown;
		sim->count_mutex += 1;
		i++;
	}
	return (0);
}

static int	init_coder_mutexes(t_coder *coder)
{
	if (pthread_mutex_init(&coder->safe_start_of_last_compile,
			NULL) != 0)
		return (1);
	if (pthread_mutex_init(
			&coder->safe_number_of_compiles_done, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&coder->mut_wait, NULL) != 0)
		return (1);
	if (pthread_cond_init(&coder->wait, NULL) != 0)
		return (1);
	return (0);
}

static int	init_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		sim->coders[i].ID = i + 1;
		sim->coders[i].number_of_compiles_done = 0;
		sim->coders[i].start_of_last_compile = 0;
		sim->coders[i].left_dongle = &sim->dongles[i % sim->number_of_coders];
		sim->coders[i].right_dongle
			= &sim->dongles[(i + 1) % sim->number_of_coders];
		sim->coders[i].sim = sim;
		if (init_coder_mutexes(&sim->coders[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_simulation(t_simulation *sim)
{
	if (fill_coders_and_dongles(sim) == 1)
		return (1);
	if (init_dongles(sim) == 1)
		return (1);
	if (init_coders(sim) == 1)
		return (1);
	if (pthread_mutex_init(&sim->writing, NULL) != 0)
		return (1);
	sim->is_mut_writing = 1;
	if (pthread_mutex_init(&sim->stop_sim_mutex, NULL) != 0)
		return (1);
	sim->is_mut_stop_sim = 1;
	if (pthread_mutex_init(&sim->finished_mutex, NULL) != 0)
		return (1);
	sim->is_mut_finished = 1;
	if (pthread_mutex_init(&sim->heap_mutex, NULL) != 0)
		return (1);
	sim->is_mut_heap = 1;
	return (0);
}
