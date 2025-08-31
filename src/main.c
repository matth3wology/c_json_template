#include "person.h"
#include "reader.h"

int main(int argc, char *argv[]) {

  const char *filename = "data.json";
  if (argc > 1) {
    filename = argv[1];
  }

  char *buffer = read_file(filename);

  Person_t *person = parse_person(buffer);

  print_person(person);

  free_person(person);

  return 0;
}
