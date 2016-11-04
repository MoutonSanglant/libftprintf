#include <stdio.h>
#include <locale.h>
#include "src/ftprintf.h"

int main(void)
{
	char	*str;
	wchar_t	*wstr;
	wchar_t	*unicodestr;
	int		length;
	int		nb;

	nb = 42;

	//setlocale(LC_ALL, "fr_FR.UTF-8");
	setlocale(LC_ALL, "en_US.UTF-8");

	//printf("{%-30S}", L"我是一只猫。");
	//printf("{%+05.S}", L"42 c est cool");
	//printf("%-17S", L"বशݜݗ");
	//printf("%4.2S", L"ݗݜशব");
	//printf("%-17.11S", L"ݗݜशবݜ");
	//printf("%97.35S", L"uèéeêëēėęOবशݜݗèéeêëēėęO");
	//fflush(stdout);

	char	buf[100];
	char	ft_buf[100];
	char	r_buf[3];
	char	ft_r_buf[3];
	char	long_buf[50000];
	char	ft_long_buf[50000];
/*
	sprintf(buf, "hello !");
	ft_sprintf(ft_buf, "hello !");
	printf("**_sprintf: %s\nft_sprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	sprintf(buf, "hello %s !", "world");
	ft_sprintf(ft_buf, "hello %s !", "world");
	printf("**_sprintf: %s\nft_sprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 3, "hello !");
	ft_snprintf(ft_buf, 3, "hello !");
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

*/	
	snprintf(buf, 3, "hello %s !", "world");
	ft_snprintf(ft_buf, 3, "hello %s !", "world");
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 12, "%i, %i, %i, %i :: %i !", 41, 311, 849301, 0, 42);
	ft_snprintf(ft_buf, 12, "%i, %i, %i, %i :: %i !", 41, 311, 849301, 0, 42);
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 12, "%u, %u, %u, %u :: %u !", 41, 311, 849301, 0, 42);
	ft_snprintf(ft_buf, 12, "%u, %u, %u, %u :: %u !", 41, 311, 849301, 0, 42);
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 12, "%x, %x, %x, %x :: %x !", 41, 311, 849301, 0, 42);
	ft_snprintf(ft_buf, 12, "%x, %x, %x, %x :: %x !", 41, 311, 849301, 0, 42);
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 12, "%o, %o, %o, %o :: %o !", 41, 311, 849301, 0, 42);
	ft_snprintf(ft_buf, 12, "%o, %o, %o, %o :: %o !", 41, 311, 849301, 0, 42);
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	snprintf(buf, 12, "%u, %u, %u, %u :: %u !", 41, 311, 849301, 0, 42);
	ft_snprintf(ft_buf, 12, "%u, %u, %u, %u :: %u !", 41, 311, 849301, 0, 42);
	printf("**_snprintf: %s\nft_snprintf: %s\n", buf, ft_buf);
	fflush(stdout);

	sprintf(long_buf, "-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	ft_sprintf(ft_long_buf, "-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	printf("**_sprintf: %s\nft_sprintf: %s\n", long_buf, ft_long_buf);
	fflush(stdout);

	snprintf(long_buf, 5, "-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	ft_snprintf(ft_long_buf, 5, "-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	printf("**_snprintf: %s\nft_snprintf: %s\n", long_buf, ft_long_buf);
	fflush(stdout);
	
	ft_printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	fflush(stdout);
	write(1, "\n", 1);
	
	//return (0);

	ft_printf("hello %s !\n", "world");
	printf("hello %s !\n", "world");
	fflush(stdout);

	//return (0);

	ft_printf("{%10RN}\n");
	printf("{%10RN}\n");
	fflush(stdout);


	write(1, "==========\n==========", 11);
	ft_printf("%-i\n", -42);
	printf("%-i\n", -42);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("% d\n", -42);
	printf("% d\n", -42);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%+05d\n", 42);
	printf("%+05d\n", 42);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%+07.3d\n", 42);
	printf("%+07.3d\n", 42);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	//ft_printf("%0-20d\n", 4242);
	//printf("%0-20d\n", 4242);
	//fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%i %0i %i\n", 4242, 4242, 4242);
	printf("%i %0i %i\n", 4242, 4242, 4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%0i\n", -4242);
	printf("%0i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%010i\n", 4242);
	printf("%010i\n", 4242);
	fflush(stdout);


	write(1, "==========\n==========", 11);
	ft_printf("%10i\n", -4242);
	printf("%10i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%.10i\n", 4242);
	printf("%.10i\n", 4242);
	fflush(stdout);

	write(1, "**********\n==========", 11);
	ft_printf("%.10i\n", -4242);
	printf("%.10i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%2i\n", 4242);
	printf("%2i\n", 4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%2i\n", -4242);
	printf("%2i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%.2i\n", -4242);
	printf("%.2i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%10.6i\n", 4242);
	printf("%10.6i\n", 4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%10.6i\n", -4242);
	printf("%10.6i\n", -4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%6.10i\n", 4242);
	printf("%6.10i\n", 4242);
	fflush(stdout);

	write(1, "==========\n==========", 11);
	ft_printf("%6.10i\n", -4242);
	printf("%6.10i\n", -4242);
	fflush(stdout);

	ft_printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	fflush(stdout);
	return (0);

	ft_printf("%2.0s is a string\n", "this");
	printf("%2.0s is a string\n", "this");
	fflush(stdout);

	ft_printf("p: %p\n", &length);
	printf("p: %p\n", &length);
	fflush(stdout);

	ft_printf("%+i\n", nb);
	printf("%+i\n", nb);
	fflush(stdout);
	//return (0);

	ft_printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	printf("-- %s %C, %s, %s, ok.\n", "hello", L'該', NULL, "");
	fflush(stdout);

	//return (0);

	str = "a sample string";
	wstr = L"a sample wide string";
	unicodestr = L"我是一只猫。";

	ft_printf("Test 1: %s %s\n", "un", "deux");
	printf("Test 1: %s %s\n", "un", "deux");
	fflush(stdout);
	//return (0);

	ft_printf("%p\n", &length);
	printf("%p\n", &length);
	fflush(stdout);

	ft_printf("a %% with text\n");
	printf("b %% with text\n");
	fflush(stdout);

	ft_printf("%%\n");
	printf("%%\n");
	fflush(stdout);

	//return (0);

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
	
	//return (0);
	
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
