Anwendungskonfiguration mit libconfig
=======================================

Homepage: http://www.hyperrealm.com/libconfig/

Einfaches Beispiel aus Quellcode von libconfig kopiert:

```c
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

int main(int argc, char **argv)
{
  config_t cfg;
  config_setting_t *setting;
  const char *str;

  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "example.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  
  /* Get the store name. */
  if(config_lookup_string(&cfg, "name", &str))
    printf("Store name: %s\n\n", str);
  else
    fprintf(stderr, "No 'name' setting in configuration file.\n");

  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}
```
