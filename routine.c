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
#include <unistd.h>

void *coder_routine(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder*)arg;
    while (1)
    {
        log_status(coder->sim, coder, "is compiling");
        sleep(1);
        log_status(coder->sim, coder, "is debugging");
        sleep(2);
    }
    return NULL;
}