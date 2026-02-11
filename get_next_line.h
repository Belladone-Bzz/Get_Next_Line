#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

/*
Read the contents of a file line by line from a file descriptor and
return a malloc'ed string of this content until a "\n".
*/
char	*get_next_line(int fd);
/*
Copie the content of the elements of the linked list into a 
character string. The character string is modified by reference.
*/
void	ft_join_content(t_list *lst, char **line);
/*
Create a new node and then call the ft_add_back() function to place it at the 
end of the linked list. When done, copy the buffer into the content of this 
new node until it encounter a line break '\n' or until the end of the buffer.

Return the index of the buffer where copying stopped.
*/
int		ft_new_node(t_list **lst, char *buffer, ssize_t size);

#endif