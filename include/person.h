#include <stdbool.h>

typedef struct {
  const char *name;
  int age;
  bool isStudent;
} Person_t;

Person_t *parse_person(char *buffer);

void print_person(Person_t *person);

void free_person(Person_t *p);
