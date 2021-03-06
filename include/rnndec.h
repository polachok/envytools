/*
 * Copyright (C) 2010 Marcin Kościelnicki <koriakin@0x04.net>
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef RNNDEC_H
#define RNNDEC_H

#include "rnn.h"

struct rnndecvariant {
	struct rnnenum *en;
	int variant;
};

struct rnndeccolors {
	char *ceval;
	char *cimm;
	char *cname;
	char *cbool;
	char *cerr;
	char *cend;
};

struct rnndeccontext {
	struct rnndb *db;
	struct rnndecvariant **vars;
	int varsnum;
	int varsmax;
	struct rnndeccolors *colors;
};

struct rnndecaddrinfo {
	struct rnntypeinfo *typeinfo;
	int width;
	char *name;
};

extern struct rnndeccolors rnndec_colorsterm, rnndec_colorsnull;

struct rnndeccontext *rnndec_newcontext(struct rnndb *db);
int rnndec_varadd(struct rnndeccontext *ctx, char *varset, char *variant);
int rnndec_varmatch(struct rnndeccontext *ctx, struct rnnvarinfo *vi);
char *rnndec_decodeval(struct rnndeccontext *ctx, struct rnntypeinfo *ti, uint64_t value, int width);
struct rnndecaddrinfo *rnndec_decodeaddr(struct rnndeccontext *ctx, struct rnndomain *domain, uint64_t addr, int write);

#endif
