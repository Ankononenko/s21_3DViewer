#ifndef MY_GETLINE_H
#define MY_GETLINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/types.h>

#ifdef _WIN32
//  if typedef doesn't exist (msvc, blah)
typedef intptr_t ssize_t;
#endif  // _WIN32
ssize_t my_getline_allocate(char **line, size_t *allocated_size, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif  // MY_GETLINE_H
