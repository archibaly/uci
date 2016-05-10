#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uci.h>

int wireless_get(const char *key, char *value, size_t size)
{
	char buff[1024];
	char *a = buff;

	snprintf(buff, sizeof(buff), "wireless.@wifi-iface[0].%s", key);

	struct uci_context *c;
	if (!(c = uci_alloc_context()))
		return -1;

	int ret = 0;
	struct uci_ptr p;
	if (uci_lookup_ptr(c, &p, a, true) != UCI_OK) {
		ret = -1;
		goto out;
	}

	if (p.flags & UCI_LOOKUP_COMPLETE)
		strlcpy(value, p.o->v.string, size);
	else
		ret = -1;
out:
	uci_free_context(c);

	return ret;

}

int wireless_set(const char *key, const char *value)
{
	char buff[1024];
	char *a = buff;

	snprintf(buff, sizeof(buff), "wireless.@wifi-iface[0].%s=%s", key, value);

	struct uci_context *c;
	if (!(c = uci_alloc_context()))
		return -1;

	int ret = 0;
	struct uci_ptr p;
	if (uci_lookup_ptr(c, &p, a, true) != UCI_OK) {
		ret = -1;
		goto out;
	}
	if (uci_set(c, &p) != UCI_OK) {
		ret = -1;
		goto out;
	}
	if (uci_save(c, p.p) != UCI_OK) {
		ret = -1;
		goto out;
	}
	if (uci_commit(c, &p.p, false) != UCI_OK) {
		ret = -1;
		goto out;
	}
out:
	uci_free_context(c);
	return ret;
}

int main(int argc, char **argv)
{
	char ssid[64];

	if (wireless_get("ssid", ssid, sizeof(ssid)) == 0)
		printf("ssid = %s\n", ssid);

	wireless_set("ssid", "123456");
	wireless_set("key", "88888888");

	return 0;
}
