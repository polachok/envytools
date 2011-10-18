/*
 * Copyright (C) 2011 Marcin Kościelnicki <koriakin@0x04.net>
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

#include "ed2i.h"
#include <stdlib.h>

void ed2i_del_isa(struct ed2i_isa *isa) {
	ed2s_symtab_del(isa->symtab);
	int i;
	for (i = 0; i < isa->featuresnum; i++) {
		ed2_free_strings(isa->features[i].names, isa->features[i].namesnum);
		free(isa->features[i].description);
		free(isa->features[i].implies);
		free(isa->features[i].conflicts);
	}
	free(isa->features);
	for (i = 0; i < isa->variantsnum; i++) {
		ed2_free_strings(isa->variants[i].names, isa->variants[i].namesnum);
		free(isa->variants[i].description);
		free(isa->variants[i].features);
	}
	free(isa->variants);
	for (i = 0; i < isa->modesnum; i++) {
		ed2_free_strings(isa->modes[i].names, isa->modes[i].namesnum);
		free(isa->modes[i].description);
		free(isa->modes[i].features);
	}
	free(isa->modes);
	for (i = 0; i < isa->modesetsnum; i++) {
		ed2_free_strings(isa->modesets[i].names, isa->modesets[i].namesnum);
		free(isa->modesets[i].description);
	}
	free(isa->modesets);
	free(isa);
}