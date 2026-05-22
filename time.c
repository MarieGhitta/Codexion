/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:37 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>

static long get_current_time_ms()
{
    struct timeval debut;
    long    timestamp;

    gettimeofday(&debut, NULL);
    timestamp = (debut.tv_sec * 1000) + (debut.tv_usec / 1000);
    return timestamp;
}

long get_simulation_time(t_simulation *sim)
{
    long    current_time;
    long    simulation_time;

    current_time = get_current_time_ms();
    simulation_time = current_time - sim->time_start_simulation;
    return simulation_time;
}