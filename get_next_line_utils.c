#include "get_next_line.h"

void	ft_join_content(t_list *lst, char **line)
{
	t_list	*temp;
	size_t	index;
	size_t	l_index;

	l_index = 0;
	temp = lst;
	while (temp->next)
	{
		l_index += BUFFER_SIZE;
		temp = temp->next;
	}
	index = 0;
	while (temp->content[index++])
		l_index++;
	*line = (char *)malloc(sizeof(char) * (l_index + 1));
	l_index = 0;
	while (lst)
	{
		index = 0;
		while (lst->content[index])
			(*line)[l_index++] = lst->content[index++];
		lst = lst->next;
	}
	(*line)[l_index] = '\0';
}

/*
Adds the new node to the end of the linked list. If the list was 
empty, the list pointer then points to the new node wich become 
the first element of the linked list. These changes are made by 
reference.
*/
void	ft_add_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!*lst)
		*lst = new_node;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	ft_new_node(t_list **lst, char *buffer, ssize_t size)
{
	size_t	index;
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof (t_list));
	if (!new_node)
		return (-1);
	new_node->next = NULL;
	ft_add_back(lst, new_node);
	new_node->content = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_node->content)
		return (-1);
	index = 0;
	while (buffer[index] != '\0')
	{
		new_node->content[index] = buffer[index];
		if (buffer[index] == '\n')
		{
			new_node->content[index + 1] = '\0';
			return (index);
		}
		index++;
	}
	new_node->content[index] = '\0';
	return (index);
}
