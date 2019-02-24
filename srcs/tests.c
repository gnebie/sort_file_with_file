
#include "sort_file_with_file.h"

void		test_alphabet(void)
{
	int i = 0;
	while (alphabet_propre[i])
	{
		printf("\t\t\t %s %s \n", alphabet_propre[i], alphabet_propre_upper[i]);
		if (strlen(alphabet_propre[i]) != strlen(alphabet_propre_upper[i]))
		{
			printf("error %s %s \n", alphabet_propre[i], alphabet_propre_upper[i]);
		}
		i++;
	}
	exit (0);
}
