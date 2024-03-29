#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *file_to_string(char *const filename, size_t *string_size);
char *fd_to_string(int fd, size_t *string_size);

char *file_to_string(char *const filename, size_t *string_size)
{
        char *string = NULL;
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
                *string_size = 0;
                return NULL;
        }
        string = fd_to_string(fd, string_size);
        close(fd);
        return string;
}

char *fd_to_string(int fd, size_t *string_size)
{
        const size_t buf_size = 1024;
        ssize_t bytes_read = 0;
        size_t buf_length = 0;
        char buf[buf_size];
        char *string = NULL;
        char *tmp = NULL;
        *string_size = 0;
        memset(buf, 0, buf_size);
        bytes_read = read(fd, buf, buf_size);
        if (bytes_read > 0) {
                buf_length = (size_t)bytes_read;
        }
        while (bytes_read > 0) {
                tmp = malloc(*string_size + buf_length);
                if (string != NULL) {
                        memcpy(tmp, string, *string_size);
                }
                memcpy(tmp + *string_size, buf, buf_length);
                *string_size += buf_length;
                if (string != NULL) {
                        free(string);
                }
                string = tmp;
                tmp = NULL;
                memset(buf, 0, buf_size);
                bytes_read = read(fd, buf, buf_size);
                if (bytes_read > 0) {
                        buf_length = (size_t)bytes_read;
                }
        }
        return string;
}

int main(int argc, char **argv) {
        ssize_t msg_size = 0;
        char *msg = NULL;
        if (argc > 1) {
                msg = file_to_string(argv[1], &msg_size);
        } else {
                msg = fd_to_string(STDIN_FILENO, &msg_size);
        }
        if (msg != NULL) {
                write(STDOUT_FILENO, msg, msg_size);
                free(msg);
        }
        return EXIT_SUCCESS;
}
