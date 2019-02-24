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
#define READ_LINE_SOUCRE_SIZE (1024 * 1024)
#define PRINT_BUFF_SIZE 1024
#define SYSERROR(message, ret) {sys_error(message, __FILE__, __LINE__); return ret; }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


const char alphabet_simple[]        = "abcdefghijklmnopqrstuvwxyz"; /*  */
const char alphabet_ponctuation[]   = " '-"; /*  */
const char *alphabet_propre[]       = {"à","â","æ","ç","è","é","ê","ë","î","ï","ô","œ","ù","û","ü","ÿ", NULL};
const char *alphabet_propre_upper[]   = {"À","Â","Æ","Ç","È","É","Ê","Ë","Î","Ï","Ô","Œ","Ù","Û","Ü","Ÿ", NULL};
#define START_ALPHABET_PROPRE (sizeof(alphabet_simple) + sizeof(alphabet_ponctuation))

void		delete_dico_tree(t_dico_tree *dico_tree)
{
	(void)dico_tree;
}

int		get_alphabet_id(char *str, int *size)
{
	char		c = *str;

	*size = 1;
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	if (c == ' ')
		return 26;
	if (c == '\'')
		return 27;
	if (c == '-')
		return 28;
	int i = 0;
	while (alphabet_propre[i])
	{
		*size = strlen(alphabet_propre[i]);
		if (!strncmp(str, alphabet_propre[i], *size))
			return i + START_ALPHABET_PROPRE;
	}
	return -1;
}

int		change_alphabet(char *str, size_t size)
{
	char		c;
	size_t		i = 0;

	while (i < size)
	{
		c = str[i];
		printf("%c\n", c);
		if (c >= 'A' && c <= 'Z')
		{
			str[i] = c - 'A' + 'a';
			i++;
		}
		else if (strchr(alphabet_ponctuation, c))
			i++;
		else
		{
			int j = 0;
			char *oldstr = &str[i];
			while (alphabet_propre[j])
			{
				size_t len = strlen(alphabet_propre_upper[j]);
				if (!strncmp(&str[i], alphabet_propre_upper[j], len))
				{
					memcpy(&str[i], alphabet_propre_upper[j], len);
					i += len;
					break ;
				}
				j++;
			}
			if (&str[i] == oldstr)
				i++;
		}
	}
	return (0);
}

typedef struct	s_alphabet
{
	/* alhabect courant */
	void		*a;						/* a */
	void		*b;						/* b */
	void		*c;						/* c */
	void		*d;						/* d */
	void		*e;						/* e */
	void		*f;						/* f */
	void		*g;						/* g */
	void		*h;						/* h */
	void		*i;						/* i */
	void		*j;						/* j */
	void		*k;						/* k */
	void		*l;						/* l */
	void		*m;						/* m */
	void		*n;						/* n */
	void		*o;						/* o */
	void		*p;						/* p */
	void		*q;						/* q */
	void		*r;						/* r */
	void		*s;						/* s */
	void		*t;						/* t */
	void		*u;						/* u */
	void		*v;						/* v */
	void		*w;						/* w */
	void		*x;						/* x */
	void		*y;						/* y */
	void		*z;						/* z */

	/* ponctuation */
	void		*space;					/*   */
	void		*apostrophe;			/* ' */
	void		*tiret;					/* - */

	/* alphabet propre */
	void		*a_grave;				/* à */
	void		*a_circ;				/* â */
	void		*a_e;					/* æ */
	void		*c_cedille;				/* ç */
	void		*e_aigu;				/* è */
	void		*e_grave;				/* é */
	void		*e_circ;				/* ê */
	void		*e_trema;				/* ë */
	void		*i_circ;				/* î */
	void		*i_trema;				/* ï */
	void		*o_circ;				/* ô */
	void		*o_e;					/* œ */
	void		*u_grave;				/* ù */
	void		*u_circ;				/* û */
	void		*u_trema;				/* ü */
	void		*y_trema;				/* ÿ */

# ifdef __FULL_FRENCH_LANGUAGE

	/* unused ponctuation */
	void		*point;					/* . */
	void		*virgule;				/* , */
	void		*point_virgule;			/* ; */
	void		*deux_point;			/* : */
	void		*point_exclamation;		/* ! */
	void		*point_interogation;	/* ? */
	void		*gillemet_droit;		/* " */
	void		*parenthese_gauche;		/* ( */
	void		*parenthese_droite;		/* ) */
	void		*crochet_gauche;		/* [ */
	void		*crochet_droite;		/* ] */
	void		*cheveron_gauche;		/* « */
	void		*cheveron_droite;		/* » */
	void		*triple_point;			/* … */

# endif

}				t_alphabet;


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



typedef struct	s_dico_branch
{
	void		*prev;
	t_alphabet	alpha;
	int			*end_id;
}				t_dico_branch;

typedef struct	s_dico_tree
{
	t_alphabet	alpha;
	char		print_buffer[PRINT_BUFF_SIZE];
}				t_dico_tree;

void		sys_error(char *message, char *file, int line)
{
	printf("%s %d", file, line);
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
	size_t		i = 1;
	int			index = 0;

	elem_table[index++] = buffer;
	while (i < size)
	{
		if (buffer[i] == spliter)
		{
			buffer[i] = 0;
			elem_table[index++] = &buffer[i + 1];
		}
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

size_t		get_source_line(char **line)
{
	size_t	size = 0;

	while (**line && **line != '\t')
		(*line)++;
	(*line)++;
	while((*line)[size] && (*line)[size] != '\t')
		size++;
	return size;
}

int		create_dictionnary_from_line(char *line, size_t size, t_dico_tree *dico, size_t tab_id)
{
	int			inc_size;
	size_t		i;
	int			nbr;

	while (i < size)
	{
		nbr = get_alphabet_id(&line[i], &inc_size);
		if (nbr == -1)
		{
			printf("c'est un bug");
			delete_dico_tree(dico);
			return (-1)
		}

		i += inc_size;
		;
	}
}

int		create_dictionnary(t_sources *source, t_dico_tree *dico)
{
	size_t		i = 0;
	char		*line;
	size_t		size;

	char **source_tab = source->table;
	while (i < source->table_size)
	{
		line = source_tab[i];
		size = get_source_line(&line);
		if (change_alphabet(line, size) == -1)
			SYSERROR("change_alphabet", 0)
		if (create_dictionnary_from_line(line, size, dico, i))
			SYSERROR("create_dictionnary_from_line", -1)
		printf("%.*s\n", (int)size, line);
		i++;
	}
	return (0);
}

int				get_tab_from_source(t_sources *sources)
{
	int				fd = sources->fd;
	char			*buffer;
	char			**elem_table;
	int				count_lines = 0;
	int				readed;
	int				save_read;

	if (!(buffer = malloc(sources->last_elem_size + READ_LINE_SOUCRE_SIZE + 1)))
		SYSERROR("buffer = malloc fail", -1)
	// buffer[sources->last_elem_size + READ_LINE_SOUCRE_SIZE] = 0;
	if (sources->last_elem)
		memcpy(buffer, sources->last_elem, sources->last_elem_size);
	readed = read(fd, buffer + sources->last_elem_size, READ_LINE_SOUCRE_SIZE);
	save_read = readed;
	readed += sources->last_elem_size;
	if (readed + sources->last_elem_size <= 0)
	{
		ft_memdel((void *)&buffer);
		return (readed);
	}
	sources->last_elem = NULL;
	sources->last_elem_size = 0;
	if (save_read == READ_LINE_SOUCRE_SIZE)
	{
		printf("hello\n");
		int len = readed ;
		while (len > 0 && buffer[--len] != '\n')
			;
		if (len != 0 || buffer[len] == '\n')
			len++;
		if (len != readed)
		{
			sources->last_elem = buffer + len;
			sources->last_elem_size = readed - len;
			printf("lasssssssst\n");
			// if (len != 0)
			// 	len--;
			readed = len;
		}
	}
	delete_sources(sources);
	count_lines = count_elem(buffer, readed, '\n');
	if (!(elem_table = malloc(count_lines * sizeof(char *))))
	{
		ft_memdel((void *)&buffer);
		SYSERROR("elem_table = malloc fail", -1)
	}
	set_source_tab(buffer, elem_table, readed, '\n');

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

int		run_sort_file_with_file(t_sources *source, t_dico_tree *dico_tree)
{
	int		ret;

	if ((ret = get_tab_from_source(source)) < 0)
		SYSERROR("get_tab_from_source malloc error", ret)
	if (ret == 0)
		return ret;
	if (create_dictionnary(source, dico_tree) < 0)
		SYSERROR("create_dictionnary malloc error", -1)
	return 1;
}

int		sort_file_with_file(int *fd_tab)
{
	t_sources		source = {NULL, NULL, 0, 0, NULL, 0, -1, 0};
	t_dico_tree		dico_tree = {};
	int				ret = 1;

	source.fd = fd_tab[0];

	while (ret)
	{
		ret = run_sort_file_with_file(&source, &dico_tree);
	}
	delete_sources(&source);
	delete_dico_tree(&dico_tree);
	return ret;

}

int			main(int argc, char **argv)
{
	int fd_tab[3];

	if (argc != 4)
		SYSERROR("print usage", 0);

	if (open_files(argv[1], argv[2], argv[3], fd_tab) == -1)
		SYSERROR("open error : ", -1)

	if (sort_file_with_file(fd_tab) == -1)
		sys_error("sort_file_with_file", __FILE__, __LINE__);

	if (close_files(fd_tab))
		SYSERROR("close error : ", -1)
	getchar();
	return 0;
}
