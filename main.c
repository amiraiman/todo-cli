#include <stdio.h>
#include <stdlib.h>

/**
 * Reads a string from standard input until a specified stop character or EOF is
 * encountered. Dynamically allocates memory for the string, resizing to the
 * exact size needed. The stop character is excluded from the returned string.
 * On allocation or input failure, returns NULL. The caller is responsible for
 * freeing the returned string.
 *
 * @param until The character that signals the end of input (excluded from
 * output).
 * @return A null-terminated string containing the input, or NULL on allocation
 * or input failure
 */
char *read_stdin(char until) {
  size_t buffer_size = 32;
  size_t parsed_length = 0;

  char *input = malloc(buffer_size);
  if (input == NULL) {
    return NULL;
  }

  while (1) {
    if ((parsed_length + 1) > buffer_size) {
      buffer_size *= 2;
      char *temp = realloc(input, buffer_size);
      if (temp == NULL) {
        free(input);
        return NULL;
      }

      input = temp;
    }

    int c = getchar();
    if (ferror(stdin)) {
      free(input);
      return NULL;
    }

    if (c == until || c == EOF) {
      input[parsed_length] = '\0';
      break;
    }

    input[parsed_length] = c;
    parsed_length++;
  }

  char *temp = realloc(input, parsed_length + 1);
  if (temp == NULL) {
    return input;
  }

  return temp;
}

int main() {
  printf("Hi there! What's your name?\n");
  char *name = read_stdin('\n');
  printf("Hello %s\n", name);
  free(name);

  return 0;
}
