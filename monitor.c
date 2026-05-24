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

void monitor(t_simulation *sim)
{
    int i;
    long    time_since_last_compile;
    
    while (get_stop(sim) == 0)
    {
            i = 0;
        while (i < sim->number_of_coders)
        {
            time_since_last_compile = get_simulation_time(sim) - get_start(&sim->coders[i]);
            if (time_since_last_compile >= sim->time_to_burnout)
            {
                log_status(sim, &sim->coders[i], "burned out");
                set_stop(sim);
                break;
            }
            i++;
        }
        usleep(1000);
    }
}