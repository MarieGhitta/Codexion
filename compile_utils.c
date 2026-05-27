/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:29 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

int get_compile_nbr(t_coder *coder)
{
    int nbr_compile;

    pthread_mutex_lock(&coder->safe_number_of_compiles_done);
    nbr_compile = coder->number_of_compiles_done;
    pthread_mutex_unlock(&coder->safe_number_of_compiles_done);
    return nbr_compile;
}

void increment_compile_nbr(t_coder *coder)
{
    pthread_mutex_lock(&coder->safe_number_of_compiles_done);
    coder->number_of_compiles_done += 1;
    pthread_mutex_unlock(&coder->safe_number_of_compiles_done);
}