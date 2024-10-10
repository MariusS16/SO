// SPDX-License-Identifier: BSD-3-Clause

#include "os_threadpool.h"
#include "log/log.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Create a task that would be executed by a thread. */
os_task_t *create_task(void (*action)(void *), void *arg, void (*destroy_arg)(void *))
{
	os_task_t *t;

	t = malloc(sizeof(*t));
	DIE(t == NULL, "malloc");

	t->action = action;
	t->argument = arg;
	t->destroy_arg = destroy_arg;

	return t;
}

/* Destroy task. */
void destroy_task(os_task_t *t)
{
	if (t->destroy_arg != NULL)
		t->destroy_arg(t->argument);
	free(t);
}

/* Put a new task to threadpool task queue. */
void enqueue_task(os_threadpool_t *tp, os_task_t *t)
{
	assert(tp != NULL);
	assert(t != NULL);

	/* TODO: Enqueue task to the shared task queue. Use synchronization. */
	// lock si unlock la mutex
	// adaug in lista si incrementez numarul de taskuri
	// dau broadcast la cond
	pthread_mutex_lock(&tp->work_mutex);
	list_add_tail(&tp->head, &t->list);
	tp->num_tasks++;
	pthread_mutex_unlock(&tp->work_mutex);
	pthread_cond_broadcast(&tp->work_cond);
}

/*
 * Check if queue is empty.
 * This function should be called in a synchronized manner.
 */
static int queue_is_empty(os_threadpool_t *tp)
{
	return list_empty(&tp->head);
}

/*
 * Get a task from threadpool task queue.
 * Block if no task is available.
 * Return NULL if work is complete, i.e. no task will become available,
 * i.e. all threads are going to block.
 */

os_task_t *dequeue_task(os_threadpool_t *tp)
{
	os_task_t *t = NULL;

	/* TODO: Dequeue task from the shared task queue. Use synchronization. */
	// lock si unlock (la final) la mutex
	// daca nu e coada goala sau s-a dat shutdown atunci ies din while
	// daca nu s-a dat shutdown atunci scad numarul de taskuri si iau primul task din coada
	pthread_mutex_lock(&tp->work_mutex);
	while (1) {
		if (!queue_is_empty(tp) || tp->shutdown)
			break;
		pthread_cond_wait(&tp->work_cond, &tp->work_mutex);// astept
	}

	if (!tp->shutdown) {
		tp->num_tasks_running++;
		t = list_entry(tp->head.next, os_task_t, list);
		list_del(tp->head.next);
		tp->num_tasks--;
	}

	pthread_mutex_unlock(&tp->work_mutex);
	return t;
}

/* Loop function for threads */
static void *thread_loop_function(void *arg)
{
	os_threadpool_t *tp = (os_threadpool_t *)arg;

	while (1) {
		os_task_t *t;

		t = dequeue_task(tp);
		if (t == NULL)
			break;
		t->action(t->argument);
		destroy_task(t);
		pthread_mutex_lock(&tp->work_mutex);
		tp->num_tasks_running--;
		// daca nu mai am taskuri atunci dau broadcast la cond
		if (tp->num_tasks_running == 0 && tp->num_tasks == 0)
			pthread_cond_broadcast(&tp->work_cond);
		pthread_mutex_unlock(&tp->work_mutex);
	}

	return NULL;
}

/* Wait completion of all threads. This is to be called by the main thread. */
void wait_for_completion(os_threadpool_t *tp)
{
	/* TODO: Wait for all worker threads. Use synchronization. */
	// lock la mutex
	// daca coada e goala si nu mai am taskuri atunci ies din while
	// dau broadcast la cond
	// dau unlock la mutex
	pthread_mutex_lock(&tp->work_mutex);
	while (1) {
		if (queue_is_empty(tp) && tp->num_tasks_running == 0)
			break;
		pthread_cond_wait(&tp->work_cond, &tp->work_mutex);
	}
	tp->shutdown = 1;
	pthread_cond_broadcast(&tp->work_cond);
	pthread_mutex_unlock(&tp->work_mutex);
	/* Join all worker threads. */
	for (unsigned int i = 0; i < tp->num_threads; i++)
		pthread_join(tp->threads[i], NULL);
}

/* Create a new threadpool. */
os_threadpool_t *create_threadpool(unsigned int num_threads)
{
	os_threadpool_t *tp = NULL;
	int rc;

	tp = malloc(sizeof(*tp));
	DIE(tp == NULL, "malloc");

	list_init(&tp->head);

	/* TODO: Initialize synchronization data. */
	// initializez mutex si cond
	// initializez threadurile ,create
	pthread_mutex_init(&tp->work_mutex, NULL);
	pthread_cond_init(&tp->work_cond, NULL);
	tp->num_tasks = 0;
	tp->num_tasks_running = 0;
	tp->shutdown = 0;
	tp->num_threads = num_threads;
	tp->threads = malloc(num_threads * sizeof(*tp->threads));
	DIE(tp->threads == NULL, "malloc");
	for (unsigned int i = 0; i < num_threads; ++i) {
		rc = pthread_create(&tp->threads[i], NULL, &thread_loop_function, (void *)tp);
		DIE(rc < 0, "pthread_create");
	}

	return tp;
}

/* Destroy a threadpool. Assume all threads have been joined. */
void destroy_threadpool(os_threadpool_t *tp)
{
	os_list_node_t *n, *p;

	/* TODO: Cleanup synchronization data. */
	// distruge cond si mutextul
	// distruge taskurile
	pthread_mutex_destroy(&tp->work_mutex);
	pthread_cond_destroy(&tp->work_cond);

	list_for_each_safe(n, p, &tp->head) {
		list_del(n);
		destroy_task(list_entry(n, os_task_t, list));
	}

	free(tp->threads);
	free(tp);
}
