## @file
#
# TPM2 software stack package for all architectures
#
# Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
##

[Defines]
  DSC_SPECIFICATION              = 1.28
  PLATFORM_NAME                  = Tpm2Tss
  PLATFORM_GUID                  = F4398D8A-08C4-4743-89FE-6CC124618C69
  PLATFORM_VERSION               = 0.1
  SUPPORTED_ARCHITECTURES        = X64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[Components]
  Tpm2TssPkg/Tpm2TssUtilLib.inf
  Tpm2TssPkg/Tpm2TssMuLib.inf
  Tpm2TssPkg/Tpm2TssSysLib.inf
  Tpm2TssPkg/Tpm2TssTctiUefiLib.inf
  Tpm2TssPkg/Tpm2TssTcg2UtilLib.inf
  Tpm2TssPkg/Tpm2TssUefiUtilLib.inf
  Tpm2TssPkg/Tpm2TssUefiExampleLib.inf
  Tpm2TssPkg/Tcg2GetCaps.inf
  Tpm2TssPkg/Tcg2GetEventLog.inf
  Tpm2TssPkg/Tcg2GetPcrBanks.inf
  Tpm2TssPkg/Tpm2GetCapsFixed.inf

[LibraryClasses]
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLibDevicePathProtocol/UefiDevicePathLibDevicePathProtocol.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsicSev.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  HandleParsingLib|ShellPkg/Library/UefiHandleParsingLib/UefiHandleParsingLib.inf
  ShellCommandLib|ShellPkg/Library/UefiShellCommandLib/UefiShellCommandLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  Tpm2TssTctiUefiLib|Tpm2TssPkg/Tpm2TssTctiUefiLib.inf
  Tpm2TssTcg2UtilLib|Tpm2TssPkg/Tpm2TssTcg2UtilLib.inf
  Tpm2TssUtilLib|Tpm2TssPkg/Tpm2TssUtilLib.inf
  Tpm2TssMuLib|Tpm2TssPkg/Tpm2TssMuLib.inf
  Tpm2TssSysLib|Tpm2TssPkg/Tpm2TssSysLib.inf

[LibraryClasses.common.UEFI_APPLICATION]
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  DebugLib|OvmfPkg/Library/PlatformDebugLibIoPort/PlatformDebugLibIoPort.inf
  Tpm2TssUefiUtilLib|Tpm2TssPkg/Tpm2TssUefiUtilLib.inf
  Tpm2TssUefiExampleLib|Tpm2TssPkg/Tpm2TssUefiExampleLib.inf
