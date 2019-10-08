/*
 * Copyright (c) 2019, Intel Corporation. All rights reserved.
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */
#ifndef __STRING_H__
#define __STRING_H__

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>

#define MAX_STRING_SIZE 0x1000

#define memcpy(dest,source,count) CopyMem(dest,source,(UINTN)(count))
#define memset(dest,ch,count) SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define memmove(dest,source,count) CopyMem(dest,source,(UINTN)(count))
#define strlen(str) (size_t)(AsciiStrnLenS(str,MAX_STRING_SIZE))
#define strchr(str,ch) ScanMem8((VOID *)(str),AsciiStrSize(str),(UINT8)ch)

#endif
