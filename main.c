#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uci.h>

int main(int argc, char **argv)
{
	struct uci_context *c;
	struct uci_ptr p;
	char *a = strdup("wireless.@wifi-iface[0].ssidd");

	c = uci_alloc_context();

	uci_lookup_ptr(c, &p, a, true);

	int ret = 0;
	if (p.flags & UCI_LOOKUP_COMPLETE)
		printf("%s\n", p.o->v.string);
	else
		ret = -1;

	uci_free_context(c);
	free(a);

	return ret;
}
