#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "xerrors.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=3)
  {

      printf("Uso\n\t%s limite numprocessi\n", argv[0]);
      exit(1);
  }
  int p = atoi(argv[1]);
  assert(p>0);

  FILE *f= xfopen(argv[2], "rb",__LINE__,__FILE__);
  // crea processi
  int e;
  pid_t pid;
  // crea pipe per la comnicazione dai figli al padre.
  int up[2];
  int down[2];
  xpipe(up,__LINE__,__FILE__);
  xpipe(down,__LINE__,__FILE__);

  // crea i processi assegnandogli intervalli distinti
  int num = 0;
  int cnt=0 ;
  int x = 0;
  while(!feof(f))
  {
      int pe = fread(&num, sizeof(int),1,f); // legge un int da f
      cnt++;

      if (ferror(f)){perror("Errore lettura");exit(1);}
      if(pe == 0) break;

      int pipedown= write(down[1],&num,sizeof(int));
      assert(pipedown==sizeof(int));
  }

  close(down[1]);
  e = fclose(f);
  if (e!=0)
  {
      perror("Errore in chiusura file");
      exit(1);
  }
  printf("Lettura di %d numeri da file\n",cnt-1);

  int b = 0;
  int flag = 0;
  if ((cnt%p!=0)) {b =cnt/p ;flag = 1;}
  else b = cnt/p;
  for (int i = 0 ; i<p;i++)
    {
		pid = xfork(__LINE__,__FILE__);

        if (pid==0)
        {
      // codice dei processi figli
            if ((flag == 1)&&(i+1 == p))
            {
                b += cnt %p;
            }
            for (int z = 0 ; z<b ; z++)
            {
                 int pt= read(down[0],&x,sizeof(int));
                 if (pt == 0 ) break;
                 if(pt!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}

                 int somma=0;
                 somma+=x*x;
                 int pe= write(up[1],&somma,sizeof(int));
                 printf("P%d scrive %d in pipe\n",i+1,somma);
                 assert(pe==sizeof(int));
            }
            close(down[0]);
            exit(0);
        }

    }
  close(up[1]);

  int fine = 0;
  int count = 0;
  while(true) {
    int x;
    int le = read(up[0],&x,sizeof(int));
    if (le == 0 ) break;
    if(le!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
    fine+= x;
    count++;
    if (count==(cnt-1)) break;

  }
  close(up[0]);
  printf("Somma quadrati ricevuti da %d PROCESSI e' %d\n",p,fine);

}
