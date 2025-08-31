#include "person.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// portable strdup
static char *portable_strdup(const char *src) {
  size_t len = strlen(src) + 1;
  char *dst = malloc(len);
  if (dst)
    memcpy(dst, src, len);
  return dst;
}

Person_t *parse_person(char *buffer) {
  if (!buffer)
    return NULL;

  Person_t *newPerson = malloc(sizeof(Person_t));
  if (!newPerson) {
    perror("malloc failed");
    exit(1);
  }
  memset(newPerson, 0, sizeof(Person_t));

  cJSON *root = cJSON_Parse(buffer);
  free(buffer); // free after parse

  if (root == NULL) {
    printf("Error parsing JSON!\n");
    free(newPerson);
    exit(1);
  }

  cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
  cJSON *age = cJSON_GetObjectItemCaseSensitive(root, "age");
  cJSON *is_student = cJSON_GetObjectItemCaseSensitive(root, "is_student");

  if (cJSON_IsString(name) && name->valuestring) {
    newPerson->name = portable_strdup(name->valuestring);
  }
  if (cJSON_IsNumber(age)) {
    newPerson->age = age->valueint;
  }
  if (cJSON_IsBool(is_student)) {
    newPerson->isStudent = cJSON_IsTrue(is_student);
  }

  cJSON_Delete(root);
  return newPerson;
}

void print_person(const Person_t *person) {
  if (!person)
    return;
  printf("Name: %s\n", person->name ? person->name : "(null)");
  printf("Age: %d\n", person->age);
  printf("Student: %s\n", person->isStudent ? "true" : "false");
}

void free_person(Person_t *p) {
  if (p) {
    free((void *)p->name);
    free(p);
  }
}
