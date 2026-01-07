## :open_book: Description

> [!NOTE]
**No artificial intelligence was used in the creation of this project.**

The goal of this project was to recode the get_next_line() function, which reads the contents of a file line by line from a file descriptor, where a “line” is a sequence of characters ending with “\n” (new line) or the end of the file (EOF). The function must work with any file size and any line length. This project is not limited to simply reading files; it involves understanding how to efficiently handle data that arrives in unpredictable blocks while maintaining state between function calls.

:brain: **This project allowed me to greatly improve the following skills:**
- Dynamic Memory Allocation
- Linked list
- Memory Management & Pointers
- Buffered Input/Output
- State Management in Functions

## :key: Instructions

To use the function ft_get_next-line(), clone the directory with the command `git clone git@github.com:Belladone-Bzz/Get_Next_Line.git` in the terminal.

Then go in the directory with the command `cd Get_Next_Line`.

Since the project is not a program, if you want to use it, you can add a main.c file in which the following code can be added, remembering to replace "file_txt_name" with the name of the file to be read ;

```\
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*result;

	fd = open("file_txt_name", O_RDONLY);
	while (1)
	{
		result = get_next_line(fd);
		printf("l: %s", result);
		if (result == NULL)
			break ;
		free (result);
	}
	return (0);
}
```

To compile, run the command `cc -Wall -Wextra -Wall -D BUFFER_SIZE=X *.c` X being the desired buffer size.

If you do not specify BUFFER_SIZE during compilation with the command `cc -Wall -Wextra -Wall *.c`, it will be automatically set to 8.

Then run the function with the command `./a.out`.

## :mag_right: Project structure

This project was carried out using linked list wich are a flexible structure and allow for more efficient memory managment. A simplified schematic version of the project design is shown in the diagram below.

<img width="1394" height="965" alt="Screenshot From 2026-01-05 19-57-44" src="https://github.com/user-attachments/assets/0b0273e9-df15-4f2d-a900-71ad5f380ed9" />


This get_next_line project is divided between 3 files : `get_next_line.c`, `get_next_line_utils.c` and `get_next_line.h`. While the header purpose is typical, functions are naturally divided between the other two C files.

### get_next_line.c

|NAME|PROTOTYPE|DECRIPTION|RETURN VALUES|
|---|---|---|---|
|ft_free_lst|static void *ft_free_lst(t_list *lst)|Free the memory allocated to all element in the list|Nothing|
|ft_read_content|static ssize_t	ft_read_content(int fd, ssize_t len_bef, t_list **lst, char *buffer)|On the first call, read the file and call the function ft_new_node(). From the second call, check if there is anything left to copy in the buffer before erasing it with a new read() call|The index of the buffer immediately after which a line break '\n' or the last character.|
|ft_get_next_line|char *get_next_line(int fd)|Call the ft_read_content() function, then the ft_join_content() function when a line break '\n' is found. If there is a problem, call the ft_free_lst() function to free memory allocated to the elements of the list| The string containing all characters before a line break '\n' inside the file referenced by the file descriptor fd|

### get_next_line_utils.c

|NAME|PROTOTYPE|DECRIPTION|RETURN VALUES|
|---|---|---|---|
|ft_join_content|void ft_join_content(t_list *lst, char **line)|Copies the content of the elements of the linked list into a character string> The character string is modified by reference.|Nothing|
|ft_add_back|void ft_add_back(t_list **lst, t_list *new_node)|Adds the new node to the end of the linked list. If the list was empty, the list pointer then points to the new node wich become the first element of the linked list. These changes are made by reference.| Nothing|
|ft_new_node|int ft_new_node(t_list **lst, char *buffer, ssize_t size)|Creates a new node and then call the ft_add_back() function to place it at the end of the linked list. Then copy the buffer into the content of this new node until it encounter a line break '\n' or until the end of the buffer|Returns the index where copying stopped.|
