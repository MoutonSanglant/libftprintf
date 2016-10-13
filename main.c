#include "src/ftprintf.h"

int main(void)
{
	char	*str;
	int		length;

	ft_printf("sizeof(t_fdata): %i==abc==\n", (int)sizeof(t_fdata));

	length = asprintf(&str, "sizeof(t_fdata): %i\n", (int)sizeof(t_fdata));
	printf("\n==============\nlength of string: %i\n", length);
	return (0);
}
