/*
 * Copyright (c) 2015-2018, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <debug.h>
#include <mmio.h>
#include "rcar_def.h"
#include "cpg_registers.h"
#include "rcar_private.h"

static void bl2_secure_cpg_init(void);

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_H3) || (RCAR_LSI == RCAR_H3N)
static void bl2_realtime_cpg_init_h3(void);
static void bl2_system_cpg_init_h3(void);
#endif

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_M3)
static void bl2_realtime_cpg_init_m3(void);
static void bl2_system_cpg_init_m3(void);
#endif

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_M3N)
static void bl2_realtime_cpg_init_m3n(void);
static void bl2_system_cpg_init_m3n(void);
#endif

#if (RCAR_LSI == RCAR_E3)
static void bl2_realtime_cpg_init_e3(void);
static void bl2_system_cpg_init_e3(void);
#endif

typedef struct {
	uintptr_t adr;
	uint32_t val;
} reg_setting_t;

static void bl2_secure_cpg_init(void)
{
	uint32_t stop_cr2, reset_cr2;

#if (RCAR_LSI == RCAR_E3)
	reset_cr2 = 0x10000000U stop_cr2 = 0xEFFFFFFFU;
#else
	reset_cr2 = 0x14000000U;
	stop_cr2 = 0xEBFFFFFFU;
#endif
	/** Secure Module Stop Control Registers */
	cpg_write(SCMSTPCR0, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR1, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR2, stop_cr2);
	cpg_write(SCMSTPCR3, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR4, 0x7FFFFFFFU);
	cpg_write(SCMSTPCR5, 0xBFFFFFFFU);
	cpg_write(SCMSTPCR6, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR7, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR8, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR9, 0xFFFDFFFFU);
	cpg_write(SCMSTPCR10, 0xFFFFFFFFU);
	cpg_write(SCMSTPCR11, 0xFFFFFFFFU);

	/** Secure Software Reset Access Enable Control Registers */
	cpg_write(SCSRSTECR0, 0x00000000U);
	cpg_write(SCSRSTECR1, 0x00000000U);
	cpg_write(SCSRSTECR2, reset_cr2);
	cpg_write(SCSRSTECR3, 0x00000000U);
	cpg_write(SCSRSTECR4, 0x80000003U);
	cpg_write(SCSRSTECR5, 0x40000000U);
	cpg_write(SCSRSTECR6, 0x00000000U);
	cpg_write(SCSRSTECR7, 0x00000000U);
	cpg_write(SCSRSTECR8, 0x00000000U);
	cpg_write(SCSRSTECR9, 0x00020000U);
	cpg_write(SCSRSTECR10, 0x00000000U);
	cpg_write(SCSRSTECR11, 0x00000000U);
}

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_H3) || (RCAR_LSI == RCAR_H3N)
static void bl2_realtime_cpg_init_h3(void)
{
	uint32_t cut = mmio_read_32(RCAR_PRR) & RCAR_CUT_MASK;
	uint32_t cr0, cr8;

	cr0 = (cut == RCAR_CUT_VER10 || cut == RCAR_CUT_VER11) ?
	    0x00200000U : 0x00210000U;
	cr8 = (cut == RCAR_CUT_VER10 || cut == RCAR_CUT_VER11) ?
	    0x01F1FFF4U : 0x01F1FFF7U;

	cpg_write(RMSTPCR0, cr0);
	cpg_write(RMSTPCR1, 0xFFFFFFFFU);
	cpg_write(RMSTPCR2, 0x040E0FDCU);
	cpg_write(RMSTPCR3, 0xFFFFFFDFU);
	cpg_write(RMSTPCR4, 0x80000004U);
	cpg_write(RMSTPCR5, 0xC3FFFFFFU);
	cpg_write(RMSTPCR6, 0xFFFFFFFFU);
	cpg_write(RMSTPCR7, 0xFFFFFFFFU);
	cpg_write(RMSTPCR8, cr8);
	cpg_write(RMSTPCR9, 0xFFFFFFFEU);
	cpg_write(RMSTPCR10, 0xFFFEFFE0U);
	cpg_write(RMSTPCR11, 0x000000B7U);
}

static void bl2_system_cpg_init_h3(void)
{
	/** System Module Stop Control Registers */
	cpg_write(SMSTPCR0, 0x00210000U);
	cpg_write(SMSTPCR1, 0xFFFFFFFFU);
	cpg_write(SMSTPCR2, 0x040E2FDCU);
	cpg_write(SMSTPCR3, 0xFFFFFBDFU);
	cpg_write(SMSTPCR4, 0x80000004U);
	cpg_write(SMSTPCR5, 0xC3FFFFFFU);
	cpg_write(SMSTPCR6, 0xFFFFFFFFU);
	cpg_write(SMSTPCR7, 0xFFFFFFFFU);
	cpg_write(SMSTPCR8, 0x01F1FFF5U);
	cpg_write(SMSTPCR9, 0xFFFFFFFFU);
	cpg_write(SMSTPCR10, 0xFFFEFFE0U);
	cpg_write(SMSTPCR11, 0x000000B7U);
}
#endif

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_M3)
static void bl2_realtime_cpg_init_m3(void)
{
	/** Realtime Module Stop Control Registers */
	cpg_write(RMSTPCR0, 0x00200000U);
	cpg_write(RMSTPCR1, 0xFFFFFFFFU);
	cpg_write(RMSTPCR2, 0x040E0FDCU);
	cpg_write(RMSTPCR3, 0xFFFFFFDFU);
	cpg_write(RMSTPCR4, 0x80000004U);
	cpg_write(RMSTPCR5, 0xC3FFFFFFU);
	cpg_write(RMSTPCR6, 0xFFFFFFFFU);
	cpg_write(RMSTPCR7, 0xFFFFFFFFU);
	cpg_write(RMSTPCR8, 0x01F1FFF7U);
	cpg_write(RMSTPCR9, 0xFFFFFFFEU);
	cpg_write(RMSTPCR10, 0xFFFEFFE0U);
	cpg_write(RMSTPCR11, 0x000000B7U);
}

static void bl2_system_cpg_init_m3(void)
{
	/** System Module Stop Control Registers */
	cpg_write(SMSTPCR0, 0x00200000U);
	cpg_write(SMSTPCR1, 0xFFFFFFFFU);
	cpg_write(SMSTPCR2, 0x040E2FDCU);
	cpg_write(SMSTPCR3, 0xFFFFFBDFU);
	cpg_write(SMSTPCR4, 0x80000004U);
	cpg_write(SMSTPCR5, 0xC3FFFFFFU);
	cpg_write(SMSTPCR6, 0xFFFFFFFFU);
	cpg_write(SMSTPCR7, 0xFFFFFFFFU);
	cpg_write(SMSTPCR8, 0x01F1FFF7U);
	cpg_write(SMSTPCR9, 0xFFFFFFFFU);
	cpg_write(SMSTPCR10, 0xFFFEFFE0U);
	cpg_write(SMSTPCR11, 0x000000B7U);
}
#endif

#if (RCAR_LSI == RCAR_AUTO) || (RCAR_LSI == RCAR_M3N)
static void bl2_realtime_cpg_init_m3n(void)
{
	/** Realtime Module Stop Control Registers */
	cpg_write(RMSTPCR0, 0x00210000U);
	cpg_write(RMSTPCR1, 0xFFFFFFFFU);
	cpg_write(RMSTPCR2, 0x040E0FDCU);
	cpg_write(RMSTPCR3, 0xFFFFFFDFU);
	cpg_write(RMSTPCR4, 0x80000004U);
	cpg_write(RMSTPCR5, 0xC3FFFFFFU);
	cpg_write(RMSTPCR6, 0xFFFFFFFFU);
	cpg_write(RMSTPCR7, 0xFFFFFFFFU);
	cpg_write(RMSTPCR8, 0x00F1FFF7U);
	cpg_write(RMSTPCR9, 0xFFFFFFFFU);
	cpg_write(RMSTPCR10, 0xFFFFFFE0U);
	cpg_write(RMSTPCR11, 0x000000B7U);
}

static void bl2_system_cpg_init_m3n(void)
{
	/* System Module Stop Control Registers */
	cpg_write(SMSTPCR0, 0x00210000U);
	cpg_write(SMSTPCR1, 0xFFFFFFFFU);
	cpg_write(SMSTPCR2, 0x040E2FDCU);
	cpg_write(SMSTPCR3, 0xFFFFFBDFU);
	cpg_write(SMSTPCR4, 0x80000004U);
	cpg_write(SMSTPCR5, 0xC3FFFFFFU);
	cpg_write(SMSTPCR6, 0xFFFFFFFFU);
	cpg_write(SMSTPCR7, 0xFFFFFFFFU);
	cpg_write(SMSTPCR8, 0x00F1FFF7U);
	cpg_write(SMSTPCR9, 0xFFFFFFFFU);
	cpg_write(SMSTPCR10, 0xFFFFFFE0U);
	cpg_write(SMSTPCR11, 0x000000B7U);
}
#endif

#if (RCAR_LSI == RCAR_E3)
static void bl2_realtime_cpg_init_e3(void)
{
	/* Realtime Module Stop Control Registers */
	cpg_write(RMSTPCR0, 0x00210000U);
	cpg_write(RMSTPCR1, 0xFFFFFFFFU);
	cpg_write(RMSTPCR2, 0x000E0FDCU);
	cpg_write(RMSTPCR3, 0xFFFFFFDFU);
	cpg_write(RMSTPCR4, 0x80000004U);
	cpg_write(RMSTPCR5, 0xC3FFFFFFU);
	cpg_write(RMSTPCR6, 0xFFFFFFFFU);
	cpg_write(RMSTPCR7, 0xFFFFFFFFU);
	cpg_write(RMSTPCR8, 0x00F1FFF7U);
	cpg_write(RMSTPCR9, 0xFFFFFFDFU);
	cpg_write(RMSTPCR10, 0xFFFFFFE8U);
	cpg_write(RMSTPCR11, 0x000000B7U);
}

static void bl2_system_cpg_init_e3(void)
{
	/* System Module Stop Control Registers */
	cpg_write(SMSTPCR0, 0x00210000U);
	cpg_write(SMSTPCR1, 0xFFFFFFFFU);
	cpg_write(SMSTPCR2, 0x000E2FDCU);
	cpg_write(SMSTPCR3, 0xFFFFFBDFU);
	cpg_write(SMSTPCR4, 0x80000004U);
	cpg_write(SMSTPCR5, 0xC3FFFFFFU);
	cpg_write(SMSTPCR6, 0xFFFFFFFFU);
	cpg_write(SMSTPCR7, 0xFFFFFFFFU);
	cpg_write(SMSTPCR8, 0x00F1FFF7U);
	cpg_write(SMSTPCR9, 0xFFFFFFDFU);
	cpg_write(SMSTPCR10, 0xFFFFFFE8U);
	cpg_write(SMSTPCR11, 0x000000B7U);
}
#endif

void bl2_cpg_init(void)
{
	uint32_t boot_cpu = mmio_read_32(RCAR_MODEMR) & MODEMR_BOOT_CPU_MASK;
#if RCAR_LSI == RCAR_AUTO
	uint32_t product = mmio_read_32(RCAR_PRR) & RCAR_PRODUCT_MASK;
#endif
	bl2_secure_cpg_init();

	if (boot_cpu == MODEMR_BOOT_CPU_CA57 ||
	    boot_cpu == MODEMR_BOOT_CPU_CA53) {
#if RCAR_LSI == RCAR_AUTO

		switch (product) {
		case RCAR_PRODUCT_H3:
			bl2_realtime_cpg_init_h3();
			break;
		case RCAR_PRODUCT_M3:
			bl2_realtime_cpg_init_m3();
			break;
		case RCAR_PRODUCT_M3N:
			bl2_realtime_cpg_init_m3n();
			break;
		default:
			panic();
			break;
		}
#elif (RCAR_LSI == RCAR_H3) || (RCAR_LSI == RCAR_H3N)
		bl2_realtime_cpg_init_h3();
#elif RCAR_LSI == RCAR_M3
		bl2_realtime_cpg_init_m3();
#elif RCAR_LSI == RCAR_M3N
		bl2_realtime_cpg_init_m3n();
#elif RCAR_LSI == RCAR_E3
		bl2_realtime_cpg_init_e3();
#else
#error "Don't have CPG initialize routine(unknown)."
#endif
	}
}

void bl2_system_cpg_init(void)
{
#if RCAR_LSI == RCAR_AUTO
	uint32_t product = mmio_read_32(RCAR_PRR) & RCAR_PRODUCT_MASK;

	switch (product) {
	case RCAR_PRODUCT_H3:
		bl2_system_cpg_init_h3();
		break;
	case RCAR_PRODUCT_M3:
		bl2_system_cpg_init_m3();
		break;
	case RCAR_PRODUCT_M3N:
		bl2_system_cpg_init_m3n();
		break;
	default:
		panic();
		break;
	}
#elif (RCAR_LSI == RCAR_H3) || (RCAR_LSI == RCAR_H3N)
	bl2_system_cpg_init_h3();
#elif RCAR_LSI == RCAR_M3
	bl2_system_cpg_init_m3();
#elif RCAR_LSI == RCAR_M3N
	bl2_system_cpg_init_m3n();
#elif RCAR_LSI == RCAR_E3
	bl2_system_cpg_init_e3();
#else
#error "Don't have CPG initialize routine(unknown)."
#endif
}