/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                          :+:      :+:    :+:   */
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

int set_stop(t_simulation *sim)
{
    pthread_mutex_lock(&sim->stop_sim_mutex);
    sim->stop_sim = 1;
    pthread_mutex_unlock(&sim->stop_sim_mutex);
}