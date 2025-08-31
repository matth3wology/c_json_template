#include "person.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person_t *parse_person(char *buffer) {

  Person_t *newPerson = malloc(sizeof(Person_t));

  // Parse JSON
  cJSON *root = cJSON_Parse(buffer);
  free(buffer); // free buffer after parsing

  if (root == NULL) {
    printf("Error parsing JSON!\n");
    exit(1);
  }

  // Extract values
  cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
  cJSON *age = cJSON_GetObjectItemCaseSensitive(root, "age");
  cJSON *is_student = cJSON_GetObjectItemCaseSensitive(root, "is_student");

  if (cJSON_IsString(name) && (name->valuestring != NULL)) {
    newPerson->name = _strdup(name->valuestring);
  }

  if (cJSON_IsNumber(age)) {
    newPerson->age = age->valueint;
  }

  if (cJSON_IsBool(is_student)) {
    newPerson->isStudent = cJSON_IsTrue(is_student);
  }

  // Free memory
  cJSON_Delete(root);

  return newPerson;
}

void print_person(Person_t *person) {
  printf("Name: %s\n", person->name);
  printf("Age: %d\n", person->age);
  if (person->isStudent == true) {
    printf("Student: true\n");
  } else {
    printf("Student: false\n");
  }
}

void free_person(Person_t *p) {
  if (p) {
    free((void *)p->name);
    free(p);
  }
}
