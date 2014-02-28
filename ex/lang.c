#include <stdio.h>
#include <locale.h>
#include <langinfo.h>

int main(void) {
 setlocale(LC_ALL,"");
printf ("Current charset = %s\n",
	nl_langinfo(CODESET));
}
