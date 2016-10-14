#include <locale.h>
#include "src/ftprintf.h"

int main(void)
{
	char	*str;
	wchar_t	*wstr;
	wchar_t	*unicodestr;
	int		length;

	setlocale(LC_ALL, "fr_FR.UTF-8");

	str = "a sample string";
	wstr = L"a sample wide string";
	unicodestr = L"我是一只猫。";

	ft_printf("%%\n");
	printf("%%\n");
	fflush(stdout);
	ft_printf("%s\n", str);
	printf("%s\n", str);
	fflush(stdout);
	ft_printf("%S\n", wstr);
	printf("%S\n", wstr);
	fflush(stdout);
	ft_printf("%S\n", unicodestr);
	printf("\n%S\n", unicodestr);
	fflush(stdout);
	unicodestr = L"unicode string 我是一只猫。";
	ft_printf("%S\n", unicodestr);
	printf("\n%S\n", unicodestr);
	fflush(stdout);
	unicodestr = L"我是一只猫。 ok !";
	ft_printf("%S\n", unicodestr);
	printf("\n%S\n", unicodestr);
	fflush(stdout);
	unicodestr = L"unicode string 我是一只猫。 ok !";
	ft_printf("%S\n", unicodestr);
	printf("\n%S\n", unicodestr);
	fflush(stdout);
	return (0);
	ft_printf("%c", '@');
	printf("\n%c\n", '@');
	fflush(stdout);
	ft_printf("%x", 0xf347f);
	printf("\n%x\n", 0xf347f);
	fflush(stdout);
	ft_printf("%o", 0xf347f);
	printf("\n%o\n", 0xf347f);
	fflush(stdout);
	ft_printf("%u", 0xf347f);
	printf("\n%u\n", 0xf347f);
	fflush(stdout);
	ft_printf("%p", &length);
	printf("\n%p\n", &length);
	fflush(stdout);
	ft_printf("%s", "hello world !"); // error
	printf("\n%s\n", "hello world !");
	fflush(stdout);
	//test_S("{%30S}", L"我是一只猫。");
	ft_printf("%C", L'我');
	printf("\n%C\n", L'我');
	fflush(stdout);
	ft_printf("Petit test: %i%o%x%s%u ET %C", 0xf347f, 0xf347f, 0xf347f, "0xf347f", 0xf347f, L'我');
	printf("\nPetit test: %i%o%x%s%u ET %C\n", 0xf347f, 0xf347f, 0xf347f, "0xf347f", 0xf347f, L'我');
	fflush(stdout);
	//ft_printf("%+8.4lli", (long long int)sizeof(t_fdata));
	//ft_printf("sizeof(t_fdata): %-+.4lli==abc==\n", (long long int)sizeof(t_fdata));
	//printf("\n%+8.4lli\n", (long long int)sizeof(t_fdata));
	//fflush(stdout);
	//ft_printf("sizeof(t_fdata): %lli==abc==\n", (int)sizeof(t_fdata));

	//length = asprintf(&str, "sizeof(t_fdata): %i\n", (int)sizeof(t_fdata));
	//printf("\n==============\nlength of string: %i\n", length);
	return (0);
}
