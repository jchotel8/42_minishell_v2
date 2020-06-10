#	ifndef HEADER_H
#	define HEADER_H

#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 1
#	endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int			get_next_line(int fd, char **line);
size_t		ft_strlen(char *s, int type);
char		*ft_strdup(char *src, char *dst);
void		*ft_calloc(size_t count, size_t size);
char		*ft_clear(char *s, int type);
void		ft_before(char **save, char **line);

#	endif