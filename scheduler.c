/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:29 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>
#include <stdio.h>

static int dongle_available(t_simulation *sim, t_dongle *dongle)
{
    long time_since_release;
    int available;

    pthread_mutex_lock(&dongle->lock_dongle);

    time_since_release =
        get_simulation_time(sim) - dongle->last_release_time;

    available = (!dongle->is_taken
        && time_since_release >= sim->dongle_cooldown);

    pthread_mutex_unlock(&dongle->lock_dongle);

    return (available);
}

void *scheduler_routine(void *arg)
{
    t_simulation    *sim;
    t_request   request;

    sim = (t_simulation*)arg;
    while(get_stop(sim) == 0)
    {
        pthread_mutex_lock(&sim->heap_mutex);
        if (sim->request_heap->size)
        {
            request = heap_pop(sim->request_heap, sim);
            pthread_mutex_unlock(&sim->heap_mutex);
            if (dongle_available(sim, request.coder->left_dongle)
                && dongle_available(sim, request.coder->right_dongle))
            {           
                pthread_mutex_lock(&request.coder->mut_wait);
                request.coder->left_dongle->is_taken = 1;
                request.coder->right_dongle->is_taken = 1;
                request.coder->can_compile = 1;
                pthread_cond_signal(&request.coder->wait);
                pthread_mutex_unlock(&request.coder->mut_wait);
            }
            else
            {
                pthread_mutex_lock(&sim->heap_mutex);
                heap_push(sim->request_heap, request, sim);
                pthread_mutex_unlock(&sim->heap_mutex);

                usleep(50);

                continue;
            }
        }
        else
            pthread_mutex_unlock(&sim->heap_mutex);
        usleep(150);
    }
    return (NULL);
}