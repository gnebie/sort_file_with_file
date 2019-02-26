/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file_with_file.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:08:49 by gnebie            #+#    #+#             */
/*   Updated: 2019/02/25 23:08:50 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SORT_FILE_WITH_FILE_H
# define SORT_FILE_WITH_FILE_H

/*
** **************************
**      __INCLUDES START
** __________________________
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

/*
** __________________________
**      __INCLUDES END
** **************************
*/

/*
** **************************
**      __DEFINES START
** __________________________
*/
/* can't be more than to INT_MAX */
#define READ_LINE_SOUCRE_SIZE (1024 * 1024)
#define PRINT_BUFF_SIZE 1024
#define SYSERROR(message, ret) {sys_error(message, __FILE__, __LINE__); return ret; }


/*
** __________________________
**      __DEFINES END
** **************************
*/

/*
** **************************
**      __STRUCTURES START
** __________________________
*/


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

#define ALPHABET_SIZE (sizeof(t_alphabet) / 8)

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
	t_alphabet	alpha;
	void		*prev;
	int			end_id;
}				t_dico_branch;

typedef struct	s_dico_tree
{
	t_alphabet	alpha;
	char		print_buffer[PRINT_BUFF_SIZE];
	t_sources	*source;
}				t_dico_tree;


/*
** __________________________
**      __STRUCTURES END
** **************************
*/

/*
** **************************
**      __GLOBALES START
** __________________________
*/

/*
** __________________________
**      __GLOBALES END
** **************************
*/

/*
** **************************
**      __PROTOTYPES START
** __________________________
*/

/*
** Prototypes internes
*/

/*
** Prototypes externes
*/

/*
** __________________________
**      __PROTOTYPES END
** **************************
*/

#endif
