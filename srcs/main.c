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










/* can't be more than to INT_MAX */
#define READ_LINE_SOUCRE_SIZE 1024
#define PRINT_BUFF_SIZE 1024
#define SYSERROR(message, ret) {sys_error(message); return ret; }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


typedef struct	s_sources
{
	char	*buffer;
	char	**table;
	size_t	buff_size;
	size_t	table_size;
	char	*last_elem;
	size_t	last_elem_size;
	int		fd;
	int		padding;
}				t_sources;

typedef struct	s_alphabet
{
	/* alhabect courant */
	void		*a;
	void		*b;
	void		*c;
	void		*d;
	void		*e;
	void		*f;
	void		*g;
	void		*h;
	void		*i;
	void		*j;
	void		*k;
	void		*l;
	void		*m;
	void		*n;
	void		*o;
	void		*p;
	void		*q;
	void		*r;
	void		*s;
	void		*t;
	void		*u;
	void		*v;
	void		*w;
	void		*x;
	void		*y;
	void		*z;

	/* alphabet propre */
	void		*a_grave;
	void		*a_circ;
	void		*a_e;
	void		*c_ced;
	void		*e_aigu;
	void		*e_grave;
	void		*e_circ;
	void		*e_trema;
	void		*a;
	void		*a;
	void		*a;
	void		*a;
	void		*a;
	void		*a;

	/* ponctuation */
	void		*space;
	void		*apostrophe;
	void		*tiret;
	void		*point;
	void		*virgule;

	/* unused ponctuation */
	/*
	void		*point_virgule;
	void		*deux_point;
	void		*point_exclamation;
	void		*point_interogation;
	void		*gillemet_droit;
	void		*parenthese_gauche;
	void		*parenthese_droite;
	void		*crochet_gauche;
	void		*crochet_droite;
	void		*cheveron_gauche;
	void		*cheveron_droite;
	void		*deux_point;

	*/

}				t_alphabet;


typedef struct	s_dico_branch
{
	void		*prev
	t_alphabet	alpha;
	int			*end_id;
}				t_dico_branch;

typedef struct	s_dico_tree
{
	t_alphabet	alpha;
	char		print_buffer[PRINT_BUFF_SIZE];
}				t_dico_tree;

void		sys_error(char *message)
{
	perror(message);
}

void		ft_memdel(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void		ft_mem_tab_del(void ***tab, size_t tab_size)
{
	size_t		i = 0;

	if (*tab)
		while (i < tab_size)
			ft_memdel((void *)&(*tab)[i++]);
	ft_memdel((void *)tab);
}

void		set_source_tab(char *buffer, char **elem_table, size_t size, char spliter)
{
	size_t		i = 0;
	int			index = 0;

	while (i < size)
	{
		if (buffer[i] == spliter)
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


void		delete_sources(t_sources *sources)
{
	ft_memdel((void *)&(sources->buffer));
	ft_memdel((void *)&sources->table);
	// ft_mem_tab_del((void *)&sources->table, sources->table_size);
	sources->table_size = 0;
	sources->buff_size = 0;
}

int				get_tab_from_source(t_sources *sources)
{
	int				fd = sources->fd;
	char			*buffer;
	char			**elem_table;
	int				count_lines = 0;
	int				readed;

	if (!(buffer = malloc(sources->last_elem_size + READ_LINE_SOUCRE_SIZE)))
		SYSERROR("buffer = malloc fail", -1)
	if (sources->last_elem)
		memcpy(buffer, sources->last_elem, sources->last_elem_size);
	readed = read(fd, buffer + sources->last_elem_size, READ_LINE_SOUCRE_SIZE);
	if (readed < 0 || (readed == 0 && sources->last_elem == NULL))
	{
		ft_memdel((void *)&buffer);
		return (readed);
	}
	sources->last_elem = NULL;
	sources->last_elem_size = 0;
	if (readed == READ_LINE_SOUCRE_SIZE)
	{
		int len = readed;
		while (buffer[--len] != '\n')
			printf("[%*s]",(int)(readed - len), &buffer[len]);
		len++;
		if (len != readed)
		{
			sources->last_elem = buffer + len;
			sources->last_elem_size = readed - len;
		}
	}
	int o = 0;
	delete_sources(sources);
	count_lines = count_elem(buffer, readed, '\n');
	if (!(elem_table = malloc(count_lines * sizeof(char *))))
	{
		ft_memdel((void *)&buffer);
		SYSERROR("elem_table = malloc fail", -1)
	}
	set_source_tab(buffer, elem_table, count_lines, '\n');
	sources->table = elem_table;
	sources->table_size = count_lines;
	sources->buffer = buffer;
	return 1;
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

int			open_files(char *file_source, char *file_cmp, char *file_dest, int *fd_tab)
{
	fd_tab[0] = open(file_source, O_RDONLY);
	fd_tab[1] = open(file_cmp, O_RDONLY);
	fd_tab[2] = open(file_dest, O_WRONLY | O_CREAT | O_TRUNC, 0000755);
	if (fd_tab[2] < 0 || fd_tab[2] < 0 || fd_tab[2] < 0)
	{
		close_files(fd_tab);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("print usage");
		return (0);
	}
	int fd_tab[3];
	t_sources source = {NULL, NULL, 0, 0, NULL, 0, -1, 0};
	t_dico_tree dico_tree = {}

	if (open_files(argv[1], argv[2], argv[3], fd_tab) == -1)
		SYSERROR("open error : ", -1)
	source.fd = fd_tab[0];
	if ((get_tab_from_source(&source)) < 0)
		SYSERROR("get_tab_from_source malloc error", -1)
	if (create_dictionnary() < 0)

	delete_sources(&source);
	if (close_files(fd_tab))
		SYSERROR("close error : ", -1)
	// getchar();
	return 0;
}
