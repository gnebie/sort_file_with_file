# sort_file_with_file


```
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

```
