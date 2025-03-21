
#include "libft.h"


void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lstlast(*alst);
	tmp->next = new;
}
