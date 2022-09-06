/*
 * Demonstrates the use of the Get_next_op() function that will be used in
 * project 1. The Get_next_op() function randomly generates a character
 * representing the operation to perform ('G' for get, 'D' for delete, and 'I'
 * for insert), the key to perform the operation on, and the data to use for
 * the operation (note that the data is only relevant for insert operations).
 */

#include <stdio.h>
#include <stdlib.h>

/* The following 6 lines should not be changed */
int num_G, num_D, num_I = 0;

long int next = 20;
void Get_next_op (char *random_op, int *random_key, int *random_data,
		  int range);
int rand (void);
void srand (unsigned int seed);
/*define structure to store data for link */
typedef struct data_ops
{
   int key;
   int data;
   struct data_ops *next;
} dataStore;
/* initialize head and tail */
dataStore *head = NULL;
dataStore *tail = NULL;
/* initialize step counter */
unsigned long int stepCount = 0;


/* gets data if key is in dynamic list, return 0 otherwise */
int
get (int key, int data)
{
   dataStore *tempBase;
   tempBase = head;
  /* iterate through repository to compare key */
   while (tempBase != NULL)
   {
      stepCount++;
      if (tempBase->key == key)
      {
         return tempBase->data;
      }
      tempBase = tempBase->next;
      
   }
   return 0;
}

/*If key and data are not in link, add to repository */
int
insert (int keyCheck, int dataCheck)
{
   dataStore *tempBase;
   dataStore *ptrBase;
   tempBase = head;
  /* initialize memory allocation and head if head is NULL */
  
   if (head == NULL)
   {
      /* allocate memory if initial repository is empty */
      ptrBase = (dataStore *) malloc (sizeof (dataStore)); 
      ptrBase->key = keyCheck;
      ptrBase->data = dataCheck;
      ptrBase->next = NULL;
      stepCount++;
      tempBase = ptrBase;
      head = tempBase;
      tail = tempBase;
      stepCount++;
      
      return 1;
   }
 
  /* loop to check for duplicate values. If false, insert key and data into repository*/
  /* for (tempBase = head; tempBase != NULL; tempBase= tempBase->next)
   {
      if (tempBase->key == keyCheck) {
          return 0;
      }
    
      stepCount++;
   } */
 while (tempBase->next != NULL) {
     if (tempBase->key == keyCheck) {
          return 0;
      }
      tempBase = tempBase->next;
      stepCount++;
 }
   ptrBase = (dataStore *) malloc (sizeof (dataStore)); 
      ptrBase->key = keyCheck;
      ptrBase->data = dataCheck;
      ptrBase->next = NULL;
    tempBase->next = ptrBase;
    tempBase = tempBase->next;
   stepCount++;
   return 1;
}
/* iterate through link. If key and data match input, delete pointer from repository. Else return 0 */
int
delete (int keyCheck, int dataCheck)
{
   dataStore *tempBase;
   dataStore *ptrBase;
  /* if there is no data in repository, return 0 */
   if (head == NULL)
   {
      return 0;
   }
   tempBase = head;
  /* if key needed is in first position, delete from repository and point to next */
   if (tempBase != NULL && tempBase->key == keyCheck) {
      ptrBase = tempBase->next;
      stepCount++;
      head = ptrBase;
     
      /*free memory */
      free(tempBase);
      return 1;
   }
  /* iterate through repository to compare key and data. If match, delete key */
   while (tempBase != NULL)
   {
      if (tempBase->key != keyCheck)
      {
         ptrBase = tempBase;
         tempBase = tempBase->next;
         stepCount++;
      }
      else if (tempBase->key == keyCheck) {
         ptrBase->next = tempBase->next;
         stepCount++;
         free (tempBase);
         return 1;
      }
   }
    /*return 0 if no key matched */
   if (tempBase == NULL) {
      return 0;
   }
}
/* print every interval: current repository, steps, repository size */
void
print_data ()
{
   dataStore *tester;
   tester = head;
   int size = 0;
   while (tester->next != NULL)
   {
     // printf ("\t%d, \t%d\n", tester->key, tester->data);
      tester = tester->next;
      size++;
   }
   printf("Size: %d, Steps: %llu\n", size, stepCount );
}
/* call method depending on random operation generated 
* if 'G' call get method
* if 'I' call insert method
* if 'D' call delete method
*/
void
useOP (char r_op, int r_key, int r_data)
{
   if (r_op == 'G')
   {
      get (r_key, r_data);
   }
   else if (r_op == 'I')
   {
      insert (r_key, r_data);
   }
   else if (r_op == 'D')
   {
      delete (r_key, r_data);
   }

}

int
main ()
{
   unsigned int s;
   unsigned int counter;
   int opCase;
   int num_op, r_key, r_data, i;
   int range;
   int interval;
   int upper;
   double randomNum, randNum1;
   char r_op;


   printf ("Generating random operations\n");
   printf ("Please enter the number of operations requested: ");
   scanf ("%d", &num_op);
   printf ("Please enter a range: ");
   scanf ("%d", &range);
   printf ("Please enter a starting seed: ");
   scanf ("%d", &s);
   printf ("Please enter an interval: ");
   scanf ("%d", &interval);
   printf ("\nGenerating %d operations with range %d and random seed %d \n",
      num_op, range, s);
   printf
      ("----------------------------------------------------------------------\n");

   srand (s);


   printf ("\nOperation\t     Key\t    Data\n\n");
   for (i = 1; i <= num_op; i++)
   {
      Get_next_op (&r_op, &r_key, &r_data, range);
      useOP (r_op, r_key, r_data);
      if (i % interval == 0)
      {
      //printf ("%9c\t%8d\t%8d\n", r_op, r_key, r_data);
         print_data ();
      }
   
   }
  

   printf ("Num_G %d, Num_D %d, Num_I %d\n", num_G, num_D, num_I);
}


/* The following 47 lines should not be changed */
void
Get_next_op (char *random_op, int *random_key, int *random_data, int range)
{
   int random_number;
   int limit;

  /* Get random operation ('G' for Get, 'D' for Delete, 'I' for Insert) */
   random_number = rand () % 4;

   switch (random_number)
   {
      case 0:
      case 1:
         *random_op = 'G';
         num_G++;
         break;
      case 2:
         *random_op = 'D';
         num_D++;
         break;
      case 3:
         *random_op = 'I';
         num_I++;
   }

  /* Get random key between 1 and range */
   limit = (32768 / range) * range;
   while ((random_number = rand ()) >= limit);

   *random_key = random_number % range + 1;

  /* Get random data between 1 and range */
   while ((random_number = rand ()) >= limit);

   *random_data = random_number % range + 1;
}

/* Pseudo random generator on 0..32767 */
int
rand (void)
{
   next = next * 1103515245 + 12345;
   return (unsigned int) (next / 65536) % 32768;
}

void
srand (unsigned int seed)
{
   next = seed;
}
