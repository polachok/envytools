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

#ifndef H264_CABAC_H
#define H264_CABAC_H

#include "h264.h"
#include <inttypes.h>

struct h264_cabac_ctx_init {
	int8_t m;
	int8_t n;
};

enum h264_cabac_ctxidx {
	H264_CABAC_CTXIDX_MB_TYPE_SI_PRE = 0,
	H264_CABAC_CTXIDX_MB_TYPE_I = 3, /* also SI suffix */

	H264_CABAC_CTXIDX_MB_SKIP_FLAG_P = 11, /* and SP */
	H264_CABAC_CTXIDX_MB_TYPE_P_PRE = 14,
	H264_CABAC_CTXIDX_MB_TYPE_P_SUF = 17,
	H264_CABAC_CTXIDX_SUB_MB_TYPE_P = 21,

	H264_CABAC_CTXIDX_MB_SKIP_FLAG_B = 24,
	H264_CABAC_CTXIDX_MB_TYPE_B_PRE = 27,
	H264_CABAC_CTXIDX_MB_TYPE_B_SUF = 32,
	H264_CABAC_CTXIDX_SUB_MB_TYPE_B = 36,

	H264_CABAC_CTXIDX_MVD_X = 40,
	H264_CABAC_CTXIDX_MVD_Y = 47,

	H264_CABAC_CTXIDX_REF_IDX = 54,

	H264_CABAC_CTXIDX_MB_QP_DELTA = 60,
	H264_CABAC_CTXIDX_INTRA_CHROMA_PRED_MODE = 64,
	H264_CABAC_CTXIDX_PREV_INTRA_PRED_MODE_FLAG = 68,
	H264_CABAC_CTXIDX_REM_INTRA_PRED_MODE = 69,

	H264_CABAC_CTXIDX_MB_FIELD_DECODING_FLAG = 70,
	H264_CABAC_CTXIDX_CODED_BLOCK_PATTERN_LUMA = 73,
	H264_CABAC_CTXIDX_CODED_BLOCK_PATTERN_CHROMA = 77,

	H264_CABAC_CTXIDX_CODED_BLOCK_FLAG_CAT0 = 85,
	H264_CABAC_CTXIDX_CODED_BLOCK_FLAG_CAT1 = 89,
	H264_CABAC_CTXIDX_CODED_BLOCK_FLAG_CAT2 = 93,
	H264_CABAC_CTXIDX_CODED_BLOCK_FLAG_CAT3 = 97,
	H264_CABAC_CTXIDX_CODED_BLOCK_FLAG_CAT4 = 101,

	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT0 = 105,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT1 = 120,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT2 = 134,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT3 = 149,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT4 = 152,

	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT0 = 166,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT1 = 181,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT2 = 195,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT3 = 210,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT4 = 213,

	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT0 = 227,
	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT1 = 237,
	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT2 = 247,
	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT3 = 257,
	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT4 = 266,

	H264_CABAC_CTXIDX_TERMINATE = 276, /* special */

	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT0 = 277,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT1 = 292,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT2 = 306,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT3 = 321,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT4 = 324,

	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT0 = 338,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT1 = 353,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT2 = 367,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT3 = 382,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT4 = 385,

	H264_CABAC_CTXIDX_TRANSFORM_SIZE_8X8_FLAG = 399,

	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FRAME_CAT5 = 402,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FRAME_CAT5 = 417,
	H264_CABAC_CTXIDX_COEFF_ABS_LEVEL_MINUS1_PRE_CAT5 = 426,
	H264_CABAC_CTXIDX_SIGNIFICANT_COEFF_FLAG_FIELD_CAT5 = 436,
	H264_CABAC_CTXIDX_LAST_SIGNIFICANT_COEFF_FLAG_FIELD_CAT5 = 451,

	H264_CABAC_CTXIDX_NUM = 460,

	/* XXX: incomplete for 4:4:4 chroma type */

	/* XXX: incomplete for scalable video coding */
};

enum h264_cabac_ctxblockcat {
	H264_CTXBLOCKCAT_LUMA_DC = 0,
	H264_CTXBLOCKCAT_LUMA_AC = 1,
	H264_CTXBLOCKCAT_LUMA_4X4 = 2,
	H264_CTXBLOCKCAT_CHROMA_DC = 3,
	H264_CTXBLOCKCAT_CHROMA_AC = 4,
	/* 8x8 mode only */
	H264_CTXBLOCKCAT_LUMA_8X8 = 5,
	/* 4:4:4 mode only */
	H264_CTXBLOCKCAT_CB_DC = 6,
	H264_CTXBLOCKCAT_CB_AC = 7,
	H264_CTXBLOCKCAT_CB_4X4 = 8,
	H264_CTXBLOCKCAT_CB_8X8 = 9,
	H264_CTXBLOCKCAT_CR_DC = 10,
	H264_CTXBLOCKCAT_CR_AC = 11,
	H264_CTXBLOCKCAT_CR_4X4 = 12,
	H264_CTXBLOCKCAT_CR_8X8 = 13,
};

enum h264_cabac_se {
	/* slice data */
	H264_CABAC_SE_MB_SKIP_FLAG_P,
	H264_CABAC_SE_MB_SKIP_FLAG_B,
	H264_CABAC_SE_MB_FIELD_DECODING_FLAG,
	H264_CABAC_SE_END_OF_SLICE_FLAG,
	/* macroblock layer */
	H264_CABAC_SE_MB_TYPE_I,
	H264_CABAC_SE_MB_TYPE_SI,
	H264_CABAC_SE_MB_TYPE_P, /* and SP */
	H264_CABAC_SE_MB_TYPE_B,
	H264_CABAC_SE_CODED_BLOCK_PATTERN,
	H264_CABAC_SE_TRANSFORM_SIZE_8X8_FLAG,
	H264_CABAC_SE_MB_QP_DELTA,
	/* macroblock and sub-macroblock prediction */
	H264_CABAC_SE_PREV_INTRA_PRED_MODE_FLAG,
	H264_CABAC_SE_REM_INTRA_PRED_MODE,
	H264_CABAC_SE_INTRA_CHROMA_PRED_MODE,
	H264_CABAC_SE_REF_IDX,
	H264_CABAC_SE_MVD_X,
	H264_CABAC_SE_MVD_Y,
	H264_CABAC_SE_SUB_MB_TYPE_P,
	H264_CABAC_SE_SUB_MB_TYPE_B,
	/* residual block */
	H264_CABAC_SE_CODED_BLOCK_FLAG,
	H264_CABAC_SE_SIGNIFICANT_COEFF_FLAG,
	H264_CABAC_SE_LAST_SIGNIFICANT_COEFF_FLAG,
	H264_CABAC_SE_COEFF_ABS_LEVEL_MINUS1,
	H264_CABAC_SE_COEFF_SIGN_FLAG,
};

struct h264_cabac_context {
	struct h264_slice *slice;
	uint8_t pStateIdx[H264_CABAC_CTXIDX_NUM];
	uint8_t valMPS[H264_CABAC_CTXIDX_NUM];
	uint32_t codIOffset; /* and codILow */
	uint32_t codIRange;
	int firstBitFlag;
	int bitsOutstanding;
	int BinCount;
};

struct h264_cabac_context *h264_cabac_new(struct h264_slice *slice);
int h264_cabac_init_arith(struct bitstream *str, struct h264_cabac_context *cabac);
int h264_cabac_renorm(struct bitstream *str, struct h264_cabac_context *cabac);
int h264_cabac_decision(struct bitstream *str, struct h264_cabac_context *cabac, int ctxIdx, int *binVal);
int h264_cabac_bypass(struct bitstream *str, struct h264_cabac_context *cabac, int *binVal);
int h264_cabac_terminate(struct bitstream *str, struct h264_cabac_context *cabac, int *binVal);
void h264_cabac_destroy(struct h264_cabac_context *cabac);

#endif
