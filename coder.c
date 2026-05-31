/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 16:44:33 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>
#include <stdio.h>

static void	request_compile(t_coder *coder)
{
	t_request	request;

	request.coder = coder;
	pthread_mutex_lock(&coder->sim->heap_mutex);
	request.arrival_order = coder->sim->arrival_counter;
	coder->sim->arrival_counter += 1;
	heap_push(coder->sim->request_heap, request, coder->sim);
	pthread_mutex_unlock(&coder->sim->heap_mutex);
}

static int	wait_compile_permission(t_coder *coder)
{
	pthread_mutex_lock(&coder->mut_wait);
	coder->can_compile = 0;
	while (coder->can_compile == 0)
		pthread_cond_wait(&coder->wait, &coder->mut_wait);
	pthread_mutex_unlock(&coder->mut_wait);
	return (get_stop(coder->sim));
}

static int	compile_phase(t_coder *coder)
{
	log_status(coder->sim, coder, "has taken a dongle");
	if (get_stop(coder->sim))
		return (1);
	log_status(coder->sim, coder, "has taken a dongle");
	set_start(coder);
	if (get_stop(coder->sim))
	{
		release_dongle(coder);
		return (1);
	}
	log_status(coder->sim, coder, "is compiling");
	smart_sleep(coder->sim, coder->sim->time_to_compile);
	increment_compile_nbr(coder);
	if (get_compile_nbr(coder) == coder->sim->number_of_compiles_required)
		notify_compile_finished(coder);
	release_dongle(coder);
	return (0);
}

static int	post_compile_phase(t_coder *coder)
{
	if (get_stop(coder->sim))
		return (1);
	log_status(coder->sim, coder, "is debugging");
	smart_sleep(coder->sim, coder->sim->time_to_debug);
	if (get_stop(coder->sim))
		return (1);
	log_status(coder->sim, coder, "is refactoring");
	smart_sleep(coder->sim, coder->sim->time_to_refactor);
	return (0);
}

int	coder_cycle(t_coder *coder)
{
	request_compile(coder);
	if (wait_compile_permission(coder))
		return (1);
	if (compile_phase(coder))
		return (1);
	if (post_compile_phase(coder))
		return (1);
	return (0);
}
