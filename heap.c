/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:29 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

static void heap_push(t_heap *heap, t_request *request, t_simulation *sim)
{
    heap->requests[heap->size] = *request;
    heap->size += 1;
    heapify_up(heap, sim);
}

static t_request heap_pop(t_heap *heap, t_request *request, t_simulation *sim)
{
    t_request pop_request;

    pop_request = heap->requests[0];
    heap->request[0] = heap->request[heap->size - 1]
    heap->size -= 1;
}

static int compare_request(t_request *request_a, t_request *request_b, t_simulation *sim)
{
    if (strcmp(sim->scheduler, "fifo") == 0)
    {
        if (request_a->arrival_order > request_b->arrival_order)
            return (1);
    }
    if (strcmp(sim->scheduler, "edf") == 0)
    {
        if (request_a->deadline > request_b->deadline)
            return (1);
    }
    return (0);
}

static void heapify_up(t_heap *heap, t_simulation *sim)
{
    int i;
    int parent;
    t_request   temp_request;

    i = heap->size - 1;
    while ((i != 0))
    {
        parent = (i - 1) / 2;
        if (compare_request(heap->requests[parent], heap->requests[i], sim) == 1)
        {       
            temp_request = heap->requests[i];
            heap->requests[i] =heap->requests[parent];
            heap->requests[parent] = temp_request;
            i = parent;
        }
        else
            break ;
    }
}

static void heapify_down(t_heap *heap, t_simulation *sim)
{
    int i;
    int left_child;
    int right_child;
    t_request   temp_request;
    int  priority_child;

    i = 0;
    while ((i != heap->size - 1))
    {
        left_child = 2 * i + 1;
        right_child = 2 * i + 2;
        if ((left_child < heap->size) && (right_child < heap->size) && (compare_request(heap->requests[left_child], heap->requests[right_child], sim) == 1))
            priority_child = left_child;
        else 
            priority_child = right_child;
        if ((compare_request(heap->requests[priority_child], heap->requests[i], sim) == 1))
        {       
            temp_request = heap->requests[priority_child];
            heap->requests[priority_child] =heap->requests[i];
            heap->requests[i] = temp_request;
            i = priority_child;
        }
        else
            break ;
    }
}