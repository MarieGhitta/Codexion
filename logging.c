/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 18:04:15 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"
#include <string.h>

void	log_status(t_simulation *sim, t_coder *coder, char *message)
{
	pthread_mutex_lock(&sim->writing);
	if (get_stop(sim)
		&& strcmp(message, "burned out") != 0)
	{
		pthread_mutex_unlock(&sim->writing);
		return ;
	}
	printf("%ld %d %s\n", get_simulation_time(sim), coder->ID, message);
	pthread_mutex_unlock(&sim->writing);
}
