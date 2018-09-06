#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

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

/* Implementation based on popen documentation (kanged from dev-harsh1998/Transfer) */
bool can_run_command(const char *cmd)
{
  if (strchr(cmd, '/'))
  {
    // if cmd includes a slash, no path search must be performed,
    // go straight to checking if it's executable

    /* ************************************** */
    // For current linux based systems this check is useless
    // but would rather be used when implementing this for windows
    // powershell.
    /* ************************************** */

    return access(cmd, X_OK) == 0;
  }
  const char *path = getenv("PATH");
  if (!path)
    return false; // something is horribly wrong...
  // we are sure we won't need a buffer any longer
  char *buf = malloc(strlen(path) + strlen(cmd) + 3);
  if (!buf)
    return false; // actually useless, see comment
  // loop as long as we have stuff to examine in path
  for (; *path; ++path)
  {
    // start from the beginning of the buffer
    char *p = buf;
    // copy in buf the current path element
    for (; *path && *path != ':'; ++path, ++p)
    {
      *p = *path;
    }
    // empty path entries are treated like "."
    if (p == buf)
      *p++ = '.';
    // slash and command name
    if (p[-1] != '/')
      *p++ = '/';
    strcpy(p, cmd);
    // check if we can execute it
    if (access(buf, X_OK) == 0)
    {
      free(buf);
      return true;
    }
    // quit at last cycle
    if (!*path)
      break;
  }
  // not found
  free(buf);
  return false;
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
  const char curl[5] = "curl";
  bool x;
  x = can_run_command(curl);

  if (x)
  {
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

  else
  {
    printf("ERROR: CURL IS SOLE DEPENDENCY THIS BINARY WON'T RUN WITHOUT IT\n");
    printf("If this message is on your screen, then your curl binary is either corrupt or not installed!");
    return -ENAVAIL;
  }

  return SUCCESS;
}