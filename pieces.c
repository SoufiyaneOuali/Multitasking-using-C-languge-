#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t sem1, sem2;
int the_end;
int trait1 = 1;
int trait2 = 5;
int nb_p_table = 0;

void *thread1_process (void * arg)
{  
  while (!the_end) {
    sem_wait (&sem2);
    printf ("Robot 1 traite une piece !  \n");
  sleep (trait1);
     
    printf ("Robot 1 depose 1 piece sur la table! nb piece sur table %d\n",++nb_p_table);
    sem_post (&sem1);
    
  }

   pthread_exit (0);
}


void *thread2_process (void * arg)
{  
  while (!the_end) {
    sem_wait (&sem1);  
    sleep (trait2);
    printf ("Robot 2  a pris une piece           nb piece sur table %d !\n",--nb_p_table); 
    sem_post (&sem2);
    printf ("Robot 2  fini 1 piece \n");
    
    
  }

   pthread_exit (0);
}


main (int ac, char **av)
{
  pthread_t th1, th2;
  void *ret;

  sem_init (&sem1, 0, 0);
  sem_init (&sem2, 0, 4);
  if (pthread_create (&th1, NULL, thread1_process, NULL) < 0) {
    fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
  }

  if (pthread_create (&th2, NULL, thread2_process, NULL) < 0) {
    fprintf (stderr, "pthread_create error for thread 2\n");
    exit (1);
  }

  (void)pthread_join (th1, &ret);
  (void)pthread_join (th2, &ret);
}
