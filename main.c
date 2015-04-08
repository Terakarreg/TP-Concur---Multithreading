
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#define MIN_SIZE 10

static pthread_mutex_t mutexFile;
static pthread_mutex_t mutexScreen;
static FILE* file;

int is_prime(uint64_t nb)
{
    uint64_t cpt;
    uint64_t square=nb*nb;
    uint16_t pas=2;
    if((nb%2==0 || nb%3==0) && nb!=2 && nb!=3)
    {
        return 0;
    }


    for(cpt=5 ; cpt*cpt<square  ; cpt+=pas, pas=6-pas)
    {

        if(nb%cpt==0)
        {
            return 0;
        }
    }

    return 1;
}


uint64_t* print_prime_factors(uint64_t n)
{
    uint64_t restant=n;
    uint64_t cpt=2;
    uint16_t pas=2;
    uint64_t *result= malloc(sizeof(uint64_t)*MIN_SIZE);
    int indice=1;
    int taille=MIN_SIZE;

    if(is_prime(n))
    {
         result[0]=1;
         result[1]=n;
         return result;
    }
    while(restant !=1)
    {
        if(restant%cpt==0)
        {
            if(indice>=taille)
            {
                int i=0;
                uint64_t *result_tmp= malloc(sizeof(uint64_t)*(taille+MIN_SIZE));
                for(i=1;i<taille;i++)
                {
                   result_tmp[i]=result[i];
                }
                result=result_tmp;

                taille+=MIN_SIZE;
            }
            result[indice]=cpt;
            indice++;
            restant/=cpt;

            cpt=2;

        }
        else
        {
			if(cpt>=5) {cpt += pas; pas=6-pas;}
			else if(cpt==3) cpt = 5;
			else cpt++;
			
        }
        if(cpt*cpt >= restant) {
			cpt = restant;
		}
    }
	result[0]=indice-1;

	return result;
}


void * lancementThread(void * arg)
{
	uint64_t nb = 64;
	uint64_t * results = NULL;
	int retScanf;
	
	do 
	{
		// Lecture du fichier
		pthread_mutex_lock (&mutexFile);
		retScanf = fscanf(file, "%llu",&nb);
	    pthread_mutex_unlock (&mutexFile);
	    
	    if(retScanf != EOF) {
			// Lancement de la fonction
			results = print_prime_factors(nb);

			// Affichage du resultat
			int i=0;
			pthread_mutex_lock (&mutexScreen);
			printf("%llu : ",nb);
			for(i=1;i<results[0]+1;i++)
			{
				printf(" %llu",results[i]);
			}
			printf("\n");
			pthread_mutex_unlock (&mutexScreen);
			
		}
	} while(retScanf != EOF);
	
	free(results);
    pthread_exit(NULL);
}


int main()
{
	pthread_t  thread1;
    pthread_t  thread2;
    void * null;
	pthread_mutex_init(&mutexFile, NULL);
	pthread_mutex_init(&mutexScreen, NULL);
	
	file = fopen("nombres.txt","r");
	
	pthread_create(&thread1,NULL,lancementThread,NULL);
	pthread_create(&thread2,NULL,lancementThread,NULL);
    
	pthread_join(thread1,&null);
	pthread_join(thread2,&null);
	
	pthread_mutex_destroy(&mutexFile);
	pthread_mutex_destroy(&mutexScreen);
	
	fclose(file);
	
	return 0;
}
