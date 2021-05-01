#include <unistd.h>

int main(int argc, char **argv)
{
		execve("/bin/bash", NULL, NULL);
}
