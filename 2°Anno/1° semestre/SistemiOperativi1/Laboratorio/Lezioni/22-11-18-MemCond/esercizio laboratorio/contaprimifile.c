#include "xerrori.h"

// programma per il conteggio del numero dei primi 
// tra gli interi contenuti in un file 

// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  int i;
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)
      return true;
    else
      return false;
  }
  for (i=3; i*i<=n; i += 2) {
      if(n%i==0) {
          return false;
      }
  }
  return true;
}


// conta quanti sono i primi in argv[1] usando argv[2] processi helper
int main(int argc, char *argv[]) {
  if(argc!=3) {
    printf("Uso:\n\t%s nomefile p\n",argv[0]);
    exit(1);
  }
  int p = atoi(argv[2]);
  assert(p>0);
  // creo una pipe di comunicazione tra padre e figli
  int up[2]; // la chiamo up perche' la uso da figli a padre
  int down[2]; // la chiamo down perche' la uso dal padre a figli
  xpipe(up,__FILE__,__LINE__);
  xpipe(down,__FILE__,__LINE__);

  for(int i=0;i<p;i++) {
    pid_t pid = xfork(__FILE__,__LINE__);
    if(pid==0) {// figlio
      close(up[0]);
      close(down[1]);
      int tot=0;
      while(true) {
        int x;
        ssize_t e = read(down[0],&x,sizeof(int));
        if(e==0) break;
        if(primo(x)) tot++;
      } 
      printf("Figlio %d, trovati %d \n",i,tot);
      ssize_t e = write(up[1],&tot,sizeof(int));
      if(e!=sizeof(int)) die("Errore scrittura pipe");
      close(up[1]);
      exit(0);
    }  
  }
  close(up[1]);
  close(down[0]);
  // i padre inizia a leggere gli interi dal file
  FILE *f = xfopen(argv[1],"rt",__FILE__,__LINE__);
  while(true) {
    int x;
    int e = fscanf(f,"%d",&x);
    if(e==0|| e==EOF) break;
    ssize_t ex = write(down[1],&x,sizeof(int));
    if(ex!=sizeof(int)) die("Errore scrittura pipe (padre)");
  }
  fclose(f);
  close(down[1]);
  printf("Fine lettura interi da file. Attendo i risultati dai figli\n");
  int tot=0;
  while(true) {
    int x;
    ssize_t e = read(up[0],&x,sizeof(int));
    if(e==0) break;
    tot += x;
  }
  close(up[0]);
  printf("Numero primi p letti dal file: %d\n",tot);
  return 0;
}
