/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 12:53:42 by gnebie            #+#    #+#             */
/*   Updated: 2019/02/23 12:53:43 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */








/*

open les deux fichers slot et corpus
open le new file




lit les premieres lignes du fichier slot
stock dans un tableau (malloc) les index des premiers elements,
le no de case du tableau sera id de l'element
renvoie le tableau

separation par des \t
prends le tableau et transforme l'element du milieu en minuscule (fonction to lower addaptée pour les unicodes)

avec le tableau crée un arbre / dico ou chaque branche correspond a une lettre (! a unicode) contient un prev et un tableau de next de NBR_ELEM
							a
						g		i
						e[]		m
								e[]

a la fin de chaque branche creer un tableau si non et ajouter un end avec le numero de la ligne


fin de la creation du dico

parcours du dico
lit la premiere ligne du fichier corpus
avance dans le corpus en checkant si la phrase correspond a une entree du dico en avancant lettre par lettre dans la phrase
si une entree correspond (si on attends un end)

write l'entree grace a son id (peut passer par un buffer pour limiter les rights)
supprime le end correspondant
supprime l'element de l'arbre si plus de ends ni de sous branches et remonte a l'entree supperieur pour tester la meme chose

une branche de l'arbre correspond a :
	void *prev
	void *suite[alphabet_size] (pas opti e place mais en appel system)
	int  end_id (si plusieurs ends sur un elem alors error)






close le new file
close les deux fichiers





fonction qui prends un fd et renvoie ...
fonction qui prend un fd et qui renvoi ...
fonction qui parse les deux fonctions

*/

/* can't be more than to INT_MAX */
#define READ_LINE_SOUCRE_SIZE 1024

void		ft_memdel(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void		set_source_tab(char *buffer, char **elem_table, size_t size, char spliter)
{
	size_t		i = 0;
	int			index = 0;

	while (i < size)
	{
		if (buffer[i] == elem)
			elem_table[index++] = &buffer[i];
		i++;
	}
}

int			count_elem(char *buffer, size_t size, char elem)
{
	int			count_lines = 0;
	size_t		i = 0;

	while (i < size)
		if(buffer[i++] == elem)
			count_lines++;
	return (count_lines);
}

typedef struct	s_sources
{
	int		fd;
	char	*buffer;
	char	**table;
	size_t	buff_size;
	size_t	table_size;
	char	*last_elem;
	size_t	last_elem_size;
}				t_sources;


void		*get_tab_from_source(t_sources *sources)
{
	int				fd = sources->fd;
	char			*buffer;
	char			**elem_table;
	int				count_lines = 0
	int				read;

	int len_last = 0;

	if (!(buffer = malloc(sources->last_elem + READ_LINE_SOUCRE_SIZE)))
		return (-1);
	if (sources->last_elem)
		memcpy(buffer, sources->last_elem, sources->last_elem_size);
	read = read(fd, buffer + sources->last_elem, READ_LINE_SOUCRE_SIZE);
	if (read < 0 || (read == 0 && sources->last_elem == NULL))
		return (read);
	ft_memdel(&((void *)sources->last_elem))
	sources->last_elem_size = 0;
	if (read == READ_LINE_SOUCRE_SIZE)
	{
		;
		;
		/* get last elem */
	}
	count_lines = count_elem(buffer, read, '\n');
	elem_table = malloc(count_elem * sizeof(char *));
	set_source_tab(buffer, elem_table, size, '\n');

	return elem_table;
}

int			open_files(char *file_source, char *file_cmp, char *file_dest, int *fd_tab)
{
	fd_tab[0] = open(file_source, O_RDONLY)
	fd_tab[1] = open(file_cmp, O_RDONLY)
	fd_tab[2] = open(file_dest, O_WRONLY | O_CREAT | O_TRUNC, 0000755)
	if (fd_tab[2] < 0|| fd_tab[2] < 0|| fd_tab[2] < 0)
		return (-1);
	return (0);
}

int			close_files(int *fd_tab)
{
	int		ret;

	ret = 0;
	ret |= close(fd_tab[0]);
	ret |= close(fd_tab[1]);
	ret |= close(fd_tab[2]);
	return (ret);
}

int			main(int argc, char **argv)
{
	int i = 0;

	while (i < 10000000)
	{
		a[i] = 'a';
		i++;
	}
	write(1, a, 10000000);
	return 0;
}
