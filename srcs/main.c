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

#include "sort_file_with_file.h"

const char alphabet_simple[]        = "abcdefghijklmnopqrstuvwxyz"; /*  */
const char alphabet_ponctuation[]   = " '-"; /*  */
const char *alphabet_propre[]       = {"à","â","æ","ç","è","é","ê","ë","î","ï","ô","œ","ù","û","ü","ÿ", NULL};
const char *alphabet_propre_upper[]   = {"À","Â","Æ","Ç","È","É","Ê","Ë","Î","Ï","Ô","Œ","Ù","Û","Ü","Ÿ", NULL};

#define START_ALPHABET_PROPRE (sizeof(alphabet_simple) + sizeof(alphabet_ponctuation))

typedef struct	s_tread_object
{
	t_dico_tree		*dico_tree;
	t_sources		*check_file;
	int				line_nbr;
}				t_tread_object;

#define TREADS_SIZE 1
pthread_mutex_t mutex;

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
		i++;
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

void		delete_dico_branch(t_dico_branch *dico)
{
	void		**ab = NULL;
	size_t			i = 0;

	ab = (void *)&dico->alpha;
	while (i < ALPHABET_SIZE)
	{
		if (ab[i])
			delete_dico_branch(ab[i]);
		i++;
	}
	free(dico);
}

void		delete_dico_tree(t_dico_tree *dico_tree)
{
	void			**ab = NULL;
	size_t			i = 0;

	ab = (void *)&dico_tree->alpha;
	while (i < ALPHABET_SIZE)
	{
		if (ab[i])
			delete_dico_branch(ab[i]);
		ab[i] = NULL;
		i++;
	}
}

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

t_dico_branch		*create_dico_branch(void *prev)
{
	t_dico_branch *branch = calloc(sizeof(t_dico_branch), 1);
	branch->end_id = -1;
	branch->prev = prev;
	return branch;
}

int		create_dictionnary_from_line(char *line, size_t size, size_t tab_id, t_dico_branch *dico_branch)
{
	int			inc_size;
	int			nbr;
	void		**ab = NULL;

	if (size == 0)
	{
		dico_branch->end_id = tab_id;
		return 0;
	}
	ab = (void *)&dico_branch->alpha;
	nbr = get_alphabet_id(line, &inc_size);
	if (nbr == -1)
	{
		printf("c'est un bug");
		return (-1);
	}
	if (ab[nbr] == NULL)
	{
		// printf("no create : %s ", line);
		ab[nbr] = create_dico_branch(dico_branch);
	}
	size -= inc_size;
	line += inc_size;
	int ret = create_dictionnary_from_line(line, size, tab_id, ab[nbr]);

	return (ret);
}

int		create_dictionnary_from_line_begin(char *line, size_t size, t_dico_tree *dico, size_t tab_id)
{
	int			inc_size;
	int			nbr;
	void		**ab = NULL;

	ab = (void *)&dico->alpha;
	nbr = get_alphabet_id(line, &inc_size);
	if (nbr == -1)
	{
		printf("c'est un bug");
		delete_dico_tree(dico);
		return (-1);
	}
	if (ab[nbr] == NULL)
	{
		// printf("no create : %s ", line);
		ab[nbr] = create_dico_branch(dico);
	}
	size -= inc_size;
	line += inc_size;
	int ret = create_dictionnary_from_line(line, size, tab_id, ab[nbr]);
	if (ret == -1)
		delete_dico_tree(dico);
	return ret;
}


void	print_first(t_dico_branch *dico_branch)
{
	void		**ab = NULL;
	size_t			i = 0;

	ab = (void *)&dico_branch->alpha;
	while (i < ALPHABET_SIZE)
	{
		if (ab[i])
		{
			printf("%zu\n", i);
			print_first(ab[i]);
			return ;
		}
		i++;
	}
}

void	count_dico(t_dico_branch *dico_branch, int *count)
{
	void		**ab = NULL;
	size_t			i = 0;

	ab = (void *)&dico_branch->alpha;
	while (i < ALPHABET_SIZE)
	{
		if (ab[i])
		{
			(*count)++;
			count_dico(ab[i], count);
		}
		i++;
	}
}

int		create_dictionnary(t_sources *source, t_dico_tree *dico)
{
	size_t		i = 0;
	char		*line;
	size_t		size;

	char **source_tab = source->table;
	dico->source = source;
	while (i < source->table_size)
	{
		line = source_tab[i];
		size = get_source_line(&line);
		if (change_alphabet(line, size) == -1)
			SYSERROR("change_alphabet", 0)
		if (create_dictionnary_from_line_begin(line, size, dico, i))
			SYSERROR("create_dictionnary_from_line", -1)
		i++;
	}
	/*
	print_first((void *)dico);
	int count_dico_nbr = 0;
	count_dico((void *)dico, &count_dico_nbr);
	*/
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
	printf("readed %d %d \n", sources->fd, readed);
	save_read = readed;
	readed += sources->last_elem_size;
	if (readed <= 0)
	{
		ft_memdel((void *)&buffer);
		return (readed);
	}
	sources->last_elem = NULL;
	sources->last_elem_size = 0;
	if (save_read == READ_LINE_SOUCRE_SIZE)
	{
		int len = readed ;
		while (len > 0 && buffer[--len] != '\n')
			;
		if (len != 0 || buffer[len] == '\n')
			len++;
		if (len != readed)
		{
			sources->last_elem = buffer + len;
			sources->last_elem_size = readed - len;
			// if (len != 0)
			// 	len--;
			readed = len;
		}
	}
	delete_sources(sources);
	count_lines = count_elem(buffer, readed, '\n');
	if (!(elem_table = malloc((count_lines + 1) * sizeof(char *))))
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
	pthread_mutex_destroy(&mutex);
	return (ret);
}

int			open_files(char *file_source, char *file_cmp, char *file_dest, int *fd_tab)
{
	fd_tab[0] = open(file_source, O_RDONLY);
	fd_tab[1] = open(file_cmp, O_RDONLY);
	fd_tab[2] = open(file_dest, O_WRONLY | O_CREAT | O_TRUNC, 0000755);
	if (fd_tab[0] < 0 || fd_tab[1] < 0 || fd_tab[2] < 0)
	{
		close_files(fd_tab);
		return (-1);
	}
	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (0);
}

int		print_id(t_dico_tree *dico, int id)
{
	printf("find : %s", dico->source->table[id]);
	return (0);
}

int		dico_print_by_id(t_dico_branch *dico_branch, t_dico_tree *dico_tree)
{
	int ret = pthread_mutex_lock(&mutex);
	if (ret == -1)
		return (ret);
	void			**ab = NULL;
	size_t			i;

	/*
	send id to print
	delete end_id
	*/
	print_id(dico_tree, dico_branch->end_id);
	dico_branch->end_id = -1;
	/*
	check if null, if null et end id go prev et delete branch et retest
	*/
	while ((void *)dico_branch != (void *)dico_tree)
	{
		if (dico_branch->end_id != -1)
			return (pthread_mutex_unlock(&mutex));
		ab = (void *)&dico_branch->alpha;
		i = 0;
		while (i < ALPHABET_SIZE)
		{
			if (ab[i] != NULL)
				return (pthread_mutex_unlock(&mutex));
			i++;
		}
		void *tmp = dico_branch;
		dico_branch = dico_branch->prev;
		free(tmp);
		ab = (void *)&dico_branch->alpha;
		i = 0;
		while (i < ALPHABET_SIZE)
		{
			if (ab[i] == tmp)
			{
				ab[i] = NULL;
				break ;
			}
			i++;
		}
	}
	return pthread_mutex_unlock(&mutex);
}

int		test_line(char *line, t_dico_branch *dico_branch, t_dico_tree *dico_tree)
{
	int			nbr = 0;
	int			al_id = 0;
	void		**ab = NULL;

	printf("line : %c\n", *line);
	if (dico_branch->end_id != -1)
		if (dico_print_by_id(dico_branch, dico_tree))
			SYSERROR("test_line_begin", -1)
	if (*line == '\0')
		return (0);
	if ((al_id = get_alphabet_id(line, &nbr)) == -1)
		SYSERROR("test_line_begin", -1)
	line += nbr;
	ab = (void *)&dico_branch->alpha;
	if (test_line(line, ab[al_id], dico_tree) == -1)
		SYSERROR("test_line_begin", -1)
	return (0);
}

int		test_line_begin(char *line, t_dico_tree *dico_tree)
{
	int			nbr = 0;
	int			al_id = 0;
	void		**ab = NULL;

	if (*line == '\0')
		return (0);
	if ((al_id = get_alphabet_id(line, &nbr)) == -1)
		SYSERROR("test_line_begin", -1)
	line += nbr;

	printf("hello\n");
	ab = (void *)&dico_tree->alpha;
	if (test_line(line, ab[al_id], dico_tree) == -1)
		SYSERROR("test_line_begin", -1)
	return (0);
}

void	*test_tread_lines(void *treads_obj)
{
	t_tread_object		*tread_obj = treads_obj;
	size_t				i = tread_obj->line_nbr;
	t_dico_tree			*dico_tree = tread_obj->dico_tree;
	t_sources			*check_file = tread_obj->check_file;

	printf("thread %d hello \n", tread_obj->line_nbr);

	printf("%zu\n", check_file->table_size);
	while (i < check_file->table_size)
	{
		printf("%s\n", check_file->table[i]);
		test_line_begin(check_file->table[i], dico_tree);
		i += TREADS_SIZE;
	}
	free(tread_obj);
	printf("exit \n");
	pthread_exit(NULL);
}

int		test_check_file_lines(t_dico_tree *dico_tree, t_sources *check_file)
{
	size_t				i = 0;
	pthread_t			treads[TREADS_SIZE];
	t_tread_object		*tread_obj;

	while (i < TREADS_SIZE)
	{
		tread_obj = malloc(sizeof(t_tread_object));
		tread_obj->line_nbr = i;
		tread_obj->dico_tree = dico_tree;
		tread_obj->check_file = check_file;
		if (pthread_create(&(treads[i]), NULL, test_tread_lines, tread_obj))
			SYSERROR("pthread_create", -1)
		i++;
	}
	i = 0;
	while (i < TREADS_SIZE)
	{
		if (pthread_join(treads[i++], NULL))
			SYSERROR("pthread_join", -1)
	}
	printf("end join \n");
	return(0);

}

int		search_in_dico(t_dico_tree *dico_tree, t_sources *check_file)
{
	int			ret = 0;

	ret = get_tab_from_source(check_file);
	while (ret > 0)
	{
		test_check_file_lines(dico_tree, check_file);
		delete_sources(check_file);
		return 0;
		ret = get_tab_from_source(check_file);
	}
	delete_sources(check_file);
	return ret;
}

int		return_to_begin(int fd)
{
	return lseek(fd, 0, SEEK_SET);
}

int		run_sort_file_with_file(t_sources *source, t_dico_tree *dico_tree, t_sources *check_file)
{
	int		ret;

	if ((ret = get_tab_from_source(source)) < 0)
		SYSERROR("get_tab_from_source malloc error", ret)
	if (ret == 0)
		return ret;
	if (create_dictionnary(source, dico_tree) < 0)
		SYSERROR("create_dictionnary malloc error", -1)
	if (search_in_dico(dico_tree, check_file) == -1)
		SYSERROR("create_dictionnary malloc error", -1)
	return 1;
}

int		sort_file_with_file(int *fd_tab)
{
	t_sources		source = {NULL, NULL, 0, 0, NULL, 0, -1, 0};
	t_sources		check_file = {NULL, NULL, 0, 0, NULL, 0, -1, 0};
	t_dico_tree		dico_tree = {};
	int				ret = 1;

	source.fd = fd_tab[0];
	check_file.fd = fd_tab[1];
	bzero((void *)&dico_tree, sizeof(t_dico_tree));

	while (ret)
	{
		ret = run_sort_file_with_file(&source, &dico_tree, &check_file);
		break ;
		if (return_to_begin(check_file.fd))
			SYSERROR("create_dictionnary malloc error", -1)
	}
	delete_sources(&source);
	delete_sources(&check_file);
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
