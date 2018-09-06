#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 50
#define SUCCESS 0

/* do not let smartpeople with very short password show much brain */
int smartpeople(char s[])
{
  if (strlen(s) < 2)
  {
    printf("Isn't your password way too short!?\n");
    return -1;
  }
  return SUCCESS;
}

int main(int argc, char *argv[])
{
  int afh = SUCCESS;
  int bkb = SUCCESS;
  int index;
  int c;
  char cmdbuf[256];
  char uname[MAX_LEN];
  char *password;

  opterr = 0;

  /* Check if we are passing proper no. of commandline arguments */
  if (argc != 3)
  {
    printf("ERROR: This binary expects atleast and only 2 command "
           "line argument\n");
    /* bail out */
    return -ENAVAIL;
  }

  /* Derpy implementation of getopt () */
  while ((c = getopt(argc, argv, "ab")) != -1)
    switch (c)
    {
    case 'a':
      afh = 1;
      break;
    case 'b':
      bkb = 1;
      break;
    case '?':
      if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      return -ENAVAIL;
    default:
      abort();
    }

  if (afh)
  {
    printf("Uploading file to androidfilehost keep your username and password handy\n");
    printf("Input your androidfilehost username: ");
    scanf("%s", uname);
    password = getpass("Input your androidfilehost password: ");
    if (smartpeople(password) == -1)
    {
      exit(1);
    }
    else
    {
      sprintf(cmdbuf, "curl -T %s ftp://uploads.androidfilehost.com --user %s:%s", argv[2], uname, password);
      system(cmdbuf);
    }
  }

  else if (bkb)
  {
    printf("Uploading file to basketbuild keep your password handy\n");
    printf("Input your basketbuild username: ");
    scanf("%s", uname);
    password = getpass("Input your basketbuild password: ");
    if (smartpeople(password) == -1)
    {
      exit(1);
    }
    else
    {
      sprintf(cmdbuf, "curl -T %s ftp://basketbuild.com --user %s:%s", argv[2], uname, password);
      system(cmdbuf);
    }
  }

  else
  {
    /* For some extra smart people */
    for (index = optind; index < argc; index++)
    {
      printf("No valid argument supplied %s\n", argv[index]);
      break;
      return -ENODATA;
    }
  }

  return SUCCESS;
}