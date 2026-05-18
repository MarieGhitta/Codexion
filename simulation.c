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
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

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

static int init_coders(t_simulation *sim)
{
    int         i;
    t_dongle    left_dongle;
    t_dongle    right_dongle;
    //long        timestamp;

    i = 0;
    while(i < sim->number_of_coders)
    {
        left_dongle = sim->coders[i].left_dongle[i % sim->number_of_coders];
        right_dongle = sim->coders[i].right_dongle[(i + 1) % sim->number_of_coders];
        sim->coders[i].ID = i;
        sim->coders[i].number_of_compiles_done = 0;
        sim->coders[i].start_of_last_compile = 0;
        sim->coders[i].start_of_last_compile = 0;
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
    init_coders(sim);
    return 0;
}