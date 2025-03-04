#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PROCESSES 5
#define TIME_QUANTUM 3  // Time slice for Round Robin
#define MEMORY_SIZE 1024 // Total memory size in KB
#define PAGE_SIZE 256    // Each page size in KB

// Process structure
typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int memory_required;
} Process;

Process processes[MAX_PROCESSES];
int memory[MEMORY_SIZE / PAGE_SIZE] = {0}; // Paging system
sem_t scheduler_lock;

void *process_execution(void *arg) {
    Process *p = (Process *)arg;
    while (p->remaining_time > 0) {
        sem_wait(&scheduler_lock);
        int exec_time = (p->remaining_time < TIME_QUANTUM) ? p->remaining_time : TIME_QUANTUM;
        printf("Process %d is running for %d seconds...\n", p->pid, exec_time);
        sleep(exec_time);
        p->remaining_time -= exec_time;
        sem_post(&scheduler_lock);
        sleep(1);
    }
    printf("Process %d has completed.\n", p->pid);
    return NULL;
}

void schedule_processes() {
    pthread_t threads[MAX_PROCESSES];
    sem_init(&scheduler_lock, 0, 1);
    
    for (int i = 0; i < MAX_PROCESSES; i++) {
        pthread_create(&threads[i], NULL, process_execution, (void *)&processes[i]);
    }
    
    for (int i = 0; i < MAX_PROCESSES; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&scheduler_lock);
}

int allocate_memory(int pid, int size) {
    int required_pages = size / PAGE_SIZE;
    int allocated_pages = 0;
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        if (memory[i] == 0) {
            memory[i] = pid;
            allocated_pages++;
            if (allocated_pages == required_pages) return 1;
        }
    }
    return 0;
}

void initialize_processes() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].pid = i + 1;
        processes[i].burst_time = (rand() % 10) + 5;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].memory_required = (rand() % 512) + 256; // Between 256KB to 768KB
        if (!allocate_memory(processes[i].pid, processes[i].memory_required)) {
            printf("Memory allocation failed for process %d.\n", processes[i].pid);
        }
    }
}

void print_process_info() {
    printf("PID\tBurst Time\tMemory Required\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d\t%d sec\t%d KB\n", processes[i].pid, processes[i].burst_time, processes[i].memory_required);
    }
}

int main() {
    srand(time(NULL));
    initialize_processes();
    print_process_info();
    schedule_processes();
    return 0;
}
