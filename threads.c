/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:29 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

int create_threads(t_simulation *sim)
{
    int         i;

    i = 0;
    while(i < sim->number_of_coders)
    {
        pthread_create(&sim->coders[i].coder_thread, NULL, coder_routine, &sim->coders[i]);
        i++;
    }
    return 0;
}

int join_threads(t_simulation *sim)
{
    int         i;

    i = 0;
    while(i < sim->number_of_coders)
    {
        pthread_join(sim->coders[i].coder_thread, NULL);
        i++;
    }
    return 0;
}