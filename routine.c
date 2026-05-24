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

void take_dongle(t_coder *coder)
{
    t_dongle *premier;
    t_dongle *second;

    if (coder->ID % 2 != 0)
    {
        premier = coder->left_dongle;
        second = coder->right_dongle;
    }
    else
    {
        premier = coder->right_dongle;
        second = coder->left_dongle;
    }
    pthread_mutex_lock(&premier->lock_dongle);
    log_status(coder->sim, coder, "has taken a dongle");
    pthread_mutex_lock(&second->lock_dongle);
    log_status(coder->sim, coder, "has taken a dongle");
}

void release_dongle(t_coder *coder)
{
    pthread_mutex_unlock(&coder->right_dongle->lock_dongle);
    pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
}

void *coder_routine(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder*)arg;
    while (!get_stop(coder->sim))
    {
        take_dongle(coder);
        set_start(coder);
        log_status(coder->sim, coder, "is compiling");
        usleep(coder->sim->time_to_compile * 1000);
        release_dongle(coder);
        log_status(coder->sim, coder, "is debugging");
        usleep(coder->sim->time_to_debug * 1000);
        log_status(coder->sim, coder, "is refactoring");
        usleep(coder->sim->time_to_refactor * 1000);
    }
    return NULL;
}