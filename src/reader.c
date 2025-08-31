#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  // Open file
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("Failed to open file");
    exit(1);
  }

  // Determine file size
  if (fseek(file, 0, SEEK_END) != 0) {
    perror("fseek failed");
    fclose(file);
    exit(1);
  }
  long filesize = ftell(file);
  if (filesize < 0) {
    perror("ftell failed");
    fclose(file);
    exit(1);
  }
  rewind(file);

  // Allocate buffer
  char *buffer = malloc(filesize + 1);
  if (buffer == NULL) {
    perror("Failed to allocate memory");
    fclose(file);
    exit(1);
  }

  // Read file into buffer
  size_t read_size = fread(buffer, 1, filesize, file);
  if (read_size != (size_t)filesize) {
    perror("Failed to read entire file");
    free(buffer);
    fclose(file);
    exit(1);
  }
  buffer[read_size] = '\0'; // null-terminate

  fclose(file);
  return buffer; // caller must free()
}
