/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:02:31 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int get_stop(t_simulation *sim)
{
    int value_stop;

    pthread_mutex_lock(&sim->stop_sim_mutex);
    value_stop = sim->stop_sim;
    pthread_mutex_unlock(&sim->stop_sim_mutex);
    return value_stop;
}

void set_stop(t_simulation *sim)
{
    int i;
    
    pthread_mutex_lock(&sim->stop_sim_mutex);
    sim->stop_sim = 1;
    i = 0;
    while (i < sim->number_of_coders)
    {
        pthread_mutex_lock(&sim->coders[i].mut_wait);
        sim->coders[i].can_compile = 1;
        pthread_cond_signal(&sim->coders[i].wait);
        pthread_mutex_unlock(&sim->coders[i].mut_wait);
        i++;
    }
    pthread_mutex_unlock(&sim->stop_sim_mutex);
}

long get_start(t_coder *coder)
{
    int value_start;

    pthread_mutex_lock(&coder->safe_start_of_last_compile);
    value_start = coder->start_of_last_compile;
    pthread_mutex_unlock(&coder->safe_start_of_last_compile);
    return value_start;
}

void set_start(t_coder *coder)
{
    pthread_mutex_lock(&coder->safe_start_of_last_compile);
    coder->start_of_last_compile = get_simulation_time(coder->sim);
    pthread_mutex_unlock(&coder->safe_start_of_last_compile);
}