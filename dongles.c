/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:37 by mghitta          ###   ########.fr       */
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

int take_dongle(t_coder *coder)
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

void release_dongle(t_coder *coder)
{
    pthread_mutex_unlock(&coder->right_dongle->lock_dongle);
    pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
}