#include "get_next_line.h"

/*
Free the memory allocated to all element in the list.
*/
static void	*ft_free_lst(t_list *lst)
{
	t_list	*temporary;

	while (lst != NULL)
	{
		free(lst->content);
		temporary = lst->next;
		free(lst);
		lst = temporary;
	}
	return (NULL);
}

/*
On the first call, read the file and call the function ft_new_node(). From the second call, check if there is anything 
left to copy in the buffer before erasing it with a new read() call.

Return the index of the buffer immediately after a line break "\n" or the last character.
*/
static ssize_t	ft_read_content(int fd, ssize_t len_bef, t_list **lst,
	char *buffer)
{
	ssize_t			read_len;

	if (len_bef < BUFFER_SIZE && len_bef > 0 && buffer[len_bef - 1]
		&& buffer[len_bef])
	{
		read_len = ft_new_node(lst, (buffer + len_bef),
				(BUFFER_SIZE - len_bef));
		if (read_len < 0)
			return (-1);
		if (len_bef + read_len < BUFFER_SIZE)
			return (len_bef + read_len + 1);
	}
	read_len = read(fd, buffer, BUFFER_SIZE);
	while (read_len > 0)
	{
		buffer[read_len] = '\0';
		len_bef = ft_new_node(lst, buffer, read_len);
		if (len_bef < 0)
			return (-1);
		if (len_bef < read_len)
			break ;
		read_len = read(fd, buffer, BUFFER_SIZE);
	}
	return (len_bef + 1);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	len_bef = 0;
	char			*line;
	t_list			*lst;

	lst = NULL;
	line = NULL;
	len_bef = ft_read_content(fd, len_bef, &lst, buffer);
	if (lst && len_bef != -1)
		ft_join_content(lst, &line);
	ft_free_lst(lst);
	return (line);
}
