#include "get_next_line.h"

int main()
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	/*
	•	read: Returns an integer (ssize_t), so > 0 is valid and correct.
	•	get_next_line: Returns a pointer (char *), so != NULL is the appropriate check.
	*/
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}