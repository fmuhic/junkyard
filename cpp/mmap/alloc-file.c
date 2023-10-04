#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    assert(argc >= 2 && "File path is required");
    const char *filepath = argv[1];

    int fd = open(filepath, O_RDWR);
    assert(fd >= 0);

    struct stat statbuf;
    int err = fstat(fd, &statbuf);
    assert(err >= 0 && "Unable to get file stats");

    char* mem = mmap(
        NULL, // hints kernel where to place allocated memory
        statbuf.st_size, // Size corresponds to the size of the file
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd, // File descriptor
        0 // Offset in file
    );
    assert(mem != MAP_FAILED && "Memory not allocated" );
    close(fd);

    for (int i = 0; i < statbuf.st_size / 2; i++)
    {
        char temp = mem[statbuf.st_size - i - 1];
        mem[statbuf.st_size - i - 1] = mem[i];
        mem[i] = temp;
    }

    ssize_t n = write(1, mem, statbuf.st_size);
    assert(n == statbuf.st_size && "Content not written to standard output");

    err = munmap(mem, statbuf.st_size);
    assert(err >= 0 && "Unable to deallocate memory" );

    return 0;
}
