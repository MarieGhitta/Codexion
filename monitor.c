/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:37 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>
#include <stdio.h>

static int burnout_check(t_simulation *sim, t_coder *coder)
{
    long    time_since_last_compile;
    
    time_since_last_compile = get_simulation_time(sim) - get_start(coder);
    if (time_since_last_compile >= sim->time_to_burnout)
    {
        log_status(sim, coder, "burned out");
        set_stop(sim);
        return (1);
    }
    return (0);
}

static int compile_check(t_simulation *sim, t_coder *coder, int *count_coder_finished_compile)
{
    if (get_compile_nbr(coder) >= sim->number_of_compiles_required)
        *count_coder_finished_compile += 1;
    if (*count_coder_finished_compile >= sim->number_of_coders)
    {
        set_stop(sim);
        return (1);
    }
    return (0);
}

void *monitor(void *arg)
{
    int i;
    t_simulation *sim;
    int count_coder_finished_compile;
    
    sim = (t_simulation*)arg;
    while (get_stop(sim) == 0)
    {
        i = 0;
        count_coder_finished_compile = 0;
        while (i < sim->number_of_coders)
        {
            if (burnout_check(sim, &sim->coders[i]) == 1)
                break ;
            if (compile_check(sim, &sim->coders[i], &count_coder_finished_compile) == 1)
                break ;
            i++;
        }
        usleep(150);
    }
    return (NULL);
}