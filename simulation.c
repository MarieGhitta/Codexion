/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:02:31 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int fill_coders_and_dongles(t_simulation *sim)
{
    sim->coders = malloc(sim->number_of_coders * sizeof(t_coder));
    if (!sim->coders)
        return 1;
    sim->dongles = malloc(sim->number_of_coders * sizeof(t_dongle));
    if (!sim->dongles)
    {
        free(sim->coders);
        return 1;
    }
    return 0;
}

static int init_dongles(t_simulation *sim)
{
    int i;
    int lock_dongle_init;

    i = 0;
    while (i < sim->number_of_coders)
    {
        lock_dongle_init = pthread_mutex_init(&sim->dongles[i].lock_dongle, NULL);
        if (lock_dongle_init != 0)
        {
            i--;
            while(i >= 0)
            {
                pthread_mutex_destroy(&sim->dongles[i].lock_dongle);
                i--;
            }
            return 1;
        }
        i++;
    }
    return 0;
}

int init_simulation(t_simulation *sim)
{
    if (fill_coders_and_dongles(sim) == 1)
        return 1;
    if (init_dongles(sim) == 1)
        return 1;
    return 0;
}