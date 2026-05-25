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

static void set_dongles_order(t_coder *coder, t_dongle **premier, t_dongle **second)
{
    if (coder->ID % 2 != 0)
    {
        *premier = coder->left_dongle;
        *second = coder->right_dongle;
    }
    else
    {
        *premier = coder->right_dongle;
        *second = coder->left_dongle;
    }
}

static int take_dongle(t_coder *coder)
{    
    t_dongle *premier;
    t_dongle *second;

    set_dongles_order(coder, &premier, &second);

    pthread_mutex_lock(&premier->lock_dongle);
    if (get_stop(coder->sim))
    {
        pthread_mutex_unlock(&premier->lock_dongle);
        return (1);
    }
    log_status(coder->sim, coder, "has taken a dongle");
    pthread_mutex_lock(&second->lock_dongle);
    if (get_stop(coder->sim))
    {
        pthread_mutex_unlock(&second->lock_dongle);
        pthread_mutex_unlock(&premier->lock_dongle);
        return (1);
    }
    log_status(coder->sim, coder, "has taken a dongle");
    return (0);
}

static void release_dongle(t_coder *coder)
{
    pthread_mutex_unlock(&coder->right_dongle->lock_dongle);
    pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
}

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
    if (take_dongle(coder) == 1)
        return (1);
    set_start(coder);
    if (get_stop(coder->sim))
    {
        release_dongle(coder);
        return (1);
    }
    log_status(coder->sim, coder, "is compiling");
    smart_sleep(coder->sim, coder->sim->time_to_compile);
    release_dongle(coder);
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