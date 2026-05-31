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
            usleep(150);
        pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
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