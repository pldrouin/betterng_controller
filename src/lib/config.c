#include "config.h"

int config()
{
  gGlobals.fptra=NULL;
  gGlobals.fptri=-1;
  gGlobals.parc=0;

  gGlobals.plength=1;

  gGlobals.oout=1; //stdout==1
  gGlobals.eout=2; //stderr==2

  gGlobals.ht=ht_create();
  config_ht_populate();

  gGlobals.oldstdout=dup(1);
  gGlobals.oldstderr=dup(2);

  int (*cfunct)(void);

  while(gGlobals.plength>0) {

    while((gGlobals.plength=getnextparam(gGlobals.fptra,&gGlobals.fptri,false,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf))>0) {
      cfunct=(int (*)(void))ht_get(gGlobals.ht, gGlobals.pbuf);

      if(cfunct) cfunct();

      else {
	fprintf(stderr,"%s: Error: Unknown parameter: '%s'\n",__func__,gGlobals.pbuf);
	ht_destroy(gGlobals.ht);
	return 1;
      }
    }

    //Assertion: We are ready to perform a task whether a break statement has
    //been reached in the inner loop or plength<=0. Otherwise the value of
    //plength can be assessed and appropriate actions can be taken

    //All the parameters for the current job have been read, the job can now be
    //performed. Do it here

    //If reading argument from the standard input (interactive mode), we
    //indicate that the job is completed through the standard output
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    if(gGlobals.fptri!=-1 && gGlobals.fptra[gGlobals.fptri] == stdin) write(gGlobals.oldstderr,"@DONE\n",6);
    #pragma GCC diagnostic pop
    fflush(stdout);
    fflush(stderr);
    //Continue reading other commands for the next job
  }

  close(gGlobals.oout);
  close(gGlobals.eout);
  dup2(gGlobals.oldstdout,1);
  dup2(gGlobals.oldstderr,2);
  close(gGlobals.oldstdout);
  close(gGlobals.oldstderr);

  free(gGlobals.fptra);
  ht_destroy(gGlobals.ht);
  return 0;
}

void config_ht_populate()
{
  ht_set(gGlobals.ht, "config", config_config);
  ht_set(gGlobals.ht, "olog", config_olog);
  ht_set(gGlobals.ht, "elog", config_elog);
  ht_set(gGlobals.ht, "prompt", config_prompt);
}

int config_config(void)
{
  safegetnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf);

  //If we switch to interactive mode (reading instructions from standard
  //input)
  if(!argsdiffer(gGlobals.pbuf,"-")) {

    if(gGlobals.fptri==-1 || gGlobals.fptra[gGlobals.fptri] != stdin) {
      gGlobals.fptri++;
      gGlobals.fptra=(FILE**)realloc(gGlobals.fptra,(gGlobals.fptri+1)*sizeof(FILE*));
      gGlobals.fptra[gGlobals.fptri]=stdin;
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wunused-result"
      write(gGlobals.oldstderr,"@INTERACTIVE\n",13);
      #pragma GCC diagnostic push
    }

    //Otherwise, if reading from a configuration file
  } else {
    gGlobals.fptri++;
    gGlobals.fptra=(FILE**)realloc(gGlobals.fptra,(gGlobals.fptri+1)*sizeof(FILE*));

    if(!(gGlobals.fptra[gGlobals.fptri]=fopen(gGlobals.pbuf,"r"))) {
      fprintf(stderr,"%s: Error: Cannot open file '%s' in read mode\n",__func__,gGlobals.pbuf);
      ht_destroy(gGlobals.ht);
      return 1;
    }
  }
  return 0;
}

//Output file log, redirecting the standard output
int config_olog(void)
{
  safegetnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf);
  fflush(stdout);
  close(gGlobals.oout);

  if((gGlobals.oout=open(gGlobals.pbuf,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))<0) {
    fprintf(stderr,"%s: Error: Cannot open file '%s' in write mode\n",__func__,gGlobals.pbuf);
    ht_destroy(gGlobals.ht);
    return 1;
  }
  dup2(gGlobals.oout,1);
  return 0;
}

//Output error file log, redirecting the standard error
int config_elog(void)
{
  safegetnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf);
  fflush(stderr);
  close(gGlobals.eout);

  if((gGlobals.eout=open(gGlobals.pbuf,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))<0) {
    fprintf(stderr,"%s: Error: cannot open file '%s' in write mode\n",__func__,gGlobals.pbuf);
    ht_destroy(gGlobals.ht);
    return 1;
  }
  dup2(gGlobals.eout,2);
  return 0;
}

int config_prompt(void)
{
  char* lineptr;
  char* charptr;
  size_t n;
  ssize_t ret;
  int oldnargs=gGlobals.nargs;
  const char** oldargs=gGlobals.args;
  int oldparc=gGlobals.parc;
  gGlobals.nargs=-1;
  gGlobals.parc=-2;
  gGlobals.args=(char const**)&charptr;

  int (*cfunct)(void);

  do {
next_line:
    printf("<bigng> ");
    lineptr=NULL;
    n=0;
    ret=getline(&lineptr, &n, stdin);
    charptr=lineptr;

    if(ret<0) {
      free(lineptr);
      gGlobals.nargs=oldnargs;
      gGlobals.args=oldargs;
      gGlobals.parc=oldparc;
      break;
    }

    do {

      while((gGlobals.plength=getnextparam(gGlobals.fptra,&gGlobals.fptri,false,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf))>0) {
	cfunct=(int (*)(void))ht_get(gGlobals.ht, gGlobals.pbuf);

	if(cfunct) cfunct();

	else {
	  fprintf(stderr,"%s: Error: Unknown parameter: '%s'\n",__func__,gGlobals.pbuf);
	  free(lineptr);
	  goto next_line;
	}
      }

      //Assertion: We are ready to perform a task whether a break statement has
      //been reached in the inner loop or plength<=0. Otherwise the value of
      //plength can be assessed and appropriate actions can be taken

      //All the parameters for the current job have been read, the job can now be
      //performed. Do it here

      //If reading argument from the standard input (interactive mode), we
      //indicate that the job is completed through the standard output
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wunused-result"
      if(gGlobals.fptri!=-1 && gGlobals.fptra[gGlobals.fptri] == stdin) write(gGlobals.oldstderr,"@DONE\n",6);
      #pragma GCC diagnostic pop
      fflush(stdout);
      fflush(stderr);
      //Continue reading other commands for the next job

    } while(gGlobals.plength>0);

  } while(charptr == lineptr+ret);
  printf("\n");
  gGlobals.nargs=oldnargs;
  gGlobals.args=oldargs;
  gGlobals.parc=oldparc;
  return 0;
}
