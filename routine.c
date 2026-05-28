/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
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

static void one_coder(t_coder *coder)
{
        pthread_mutex_lock(&coder->left_dongle->lock_dongle);
        log_status(coder->sim, coder, "has taken a dongle");
        set_start(coder);
        while (!get_stop(coder->sim))
            usleep(1000);
        pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
}

static int coder_cycle(t_coder *coder)
{
    t_request   request;

    request.coder = coder;
    request.arrival_order = coder->sim->arrival_counter;
    coder->sim->arrival_counter += 1;
    pthread_mutex_lock(&coder->sim->heap_mutex);
    pthread_mutex_lock(&coder->mut_wait);
    coder->can_compile = 0;
    heap_push(coder->sim->request_heap, request, coder->sim);
    pthread_mutex_unlock(&coder->sim->heap_mutex);
    while (coder->can_compile == 0)
    {
        pthread_cond_wait(&coder->wait, &coder->mut_wait);
    }
    pthread_mutex_unlock(&coder->mut_wait);
    pthread_mutex_lock(&coder->left_dongle->lock_dongle);
    log_status(coder->sim, coder, "has taken a dongle");
    pthread_mutex_lock(&coder->right_dongle->lock_dongle);
    log_status(coder->sim, coder, "has taken a dongle");
    set_start(coder);
    if (get_stop(coder->sim))
    {
        release_dongle(coder);
        return (1);
    }
    log_status(coder->sim, coder, "is compiling");
    smart_sleep(coder->sim, coder->sim->time_to_compile);
    release_dongle(coder);
    increment_compile_nbr(coder);
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

void *coder_routine(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder*)arg;
    if (coder->sim->number_of_coders == 1)
        one_coder(coder);
    else
    {
        while (!get_stop(coder->sim))
        {
            if (coder_cycle(coder) == 1)
                break;
        }
    }
    return NULL;
}