/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 16:46:12 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	release_dongle(t_coder *coder)
{
	long	now;

	now = get_simulation_time(coder->sim);
	pthread_mutex_lock(&coder->left_dongle->lock_dongle);
	coder->left_dongle->is_taken = 0;
	coder->left_dongle->last_release_time = now;
	pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
	pthread_mutex_lock(&coder->right_dongle->lock_dongle);
	coder->right_dongle->is_taken = 0;
	coder->right_dongle->last_release_time = now;
	pthread_mutex_unlock(&coder->right_dongle->lock_dongle);
}
