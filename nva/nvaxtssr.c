#include "nva.h"
#include <stdio.h>
#include <unistd.h>

uint32_t xt_rsr(int cnum, uint32_t sr, uint32_t *status) {
	nva_wr32(cnum, 0x700004, sr);
	nva_wr32(cnum, 0x70000, 1);
	while (nva_rd32(cnum, 0x70000));
	nva_wr32(cnum, 0x700000, 3);
	while (nva_rd32(cnum, 0x700000));
	*status = nva_rd32(cnum, 0x70000c);
	return nva_rd32(cnum, 0x700004);
}

void xt_wsr(int cnum, uint32_t sr, uint32_t val, uint32_t *status) {
	nva_wr32(cnum, 0x700004, sr);
	nva_wr32(cnum, 0x700008, val);
	nva_wr32(cnum, 0x70000, 1);
	while (nva_rd32(cnum, 0x70000));
	nva_wr32(cnum, 0x700000, 4);
	while (nva_rd32(cnum, 0x700000));
	*status = nva_rd32(cnum, 0x70000c);
}

int main(int argc, char **argv) {
	if (nva_init()) {
		fprintf (stderr, "PCI init failure!\n");
		return 1;
	}
	int c;
	int cnum =0;
	while ((c = getopt (argc, argv, "c:")) != -1)
		switch (c) {
			case 'c':
				sscanf(optarg, "%d", &cnum);
				break;
		}
	if (cnum >= nva_cardsnum) {
		if (nva_cardsnum)
			fprintf (stderr, "No such card.\n");
		else
			fprintf (stderr, "No cards found.\n");
		return 1;
	}
	int32_t a, b = 1;
	if (optind >= argc) {
		fprintf (stderr, "No address specified.\n");
		return 1;
	}
	sscanf (argv[optind], "%x", &a);
	if (optind + 1 < argc)
		sscanf (argv[optind + 1], "%x", &b);
	nva_wr32(cnum, 0x1700, 0x30);
	for (;b > 0; b--, a++) {
		printf("%02x: ", a);
		uint32_t status;
		uint32_t val = xt_rsr(cnum, a, &status);
		uint32_t oval = val;
		if (status) {
			printf("EXC%02x\n", status & 0x3f);
			continue;
		} else {
			printf("%08x ", val);
		}
		xt_wsr(cnum, a, 0xffffffff, &status);
		if (status) {
			printf("EXC%02x\n", status & 0x3f);
		}
		val = xt_rsr(cnum, a, &status);
		if (status) {
			printf("EXC%02x\n", status & 0x3f);
			continue;
		} else {
			printf("%08x ", val);
		}
		xt_wsr(cnum, a, 0, &status);
		if (status) {
			printf("EXC%02x\n", status & 0x3f);
		}
		val = xt_rsr(cnum, a, &status);
		if (status) {
			printf("EXC%02x\n", status & 0x3f);
			continue;
		} else {
			printf("%08x\n", val);
		}
		xt_wsr(cnum, a, oval, &status);
	}
	return 0;
}
