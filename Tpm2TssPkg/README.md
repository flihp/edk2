# Tpm2Tss
The TCG TPM software stack working group specifies a family of standard API
for driving interactions with TPM2 devices from various types of software
(commonly referred to as the TPM2 Software Stack / TSS2). Intel has been a
key contributor to the definition of these specifications and has lead the
effort to implement the APIs and infrastructure as OSS. Our initial
implementation work has focused on generic use-cases for \*nix operating
systems (Linux distros & BSD). Porting this work to new platforms has proven
to be quite easy however and as interest has grown we've expanded our support
to include building on Windows under Visual Studio.

The open source code is available from the tpm2-software community:
https://github.com/tpm2-software/tpm2-tss

## scope
This document describes efforts to integrate the lower layers of this
software stack into the EDK2 build system. Initially this work is intended
to enable use of these APIs by UEFI applications. Eventually the scope may
expand to include use of these APIs by other parts of EDK2.

## software stack design
This software stack is designed in layers, each satisfying the needs of a
particular use-case. Along side these layers are several support libraries
intended to for use by the various layers and other libraries as needed.
An overview of these layers is available in the TCG specification "TSS 2.0
Overview and Common Structures Specification":
https://trustedcomputinggroup.org/resource/tss-overview-common-structures-specification/

This document describes the various layers in the software architecture,
many of which map directly to separate programming libraries. These layers
map to distinct use-cases with the higher layers existing to service richly
featured client applications and the lower layers intended for use in highly
constrained firmware environments.

## context object
The TSS2 relies on several common software design patterns. The context object
pattern is used by layers that must maintain state across function invocation.
The remainder of this document assumes that the reader is familiar with this
pattern as well as several others (dependency injection etc).

## components
For the purposes of this work we consider the System API (libtss2-sys) to be
the minimal TSS2 implementation required to do useful work in a UEFI
application. As described in the software stack design document referenced
above an implementation of libtss2-sys may build upon other layers and utility
libraries. The following sections describe the required libtss2-sys
API and implementation as well as the required support libraries.

### libtss2-tcti-uefi
The TPM2 Command Transmission Interface (TCTI) is an abstraction used to
reduce coupling between the application layer and the mechanism used to
transport data between the application and lower layers (device driver,
resource manager, remote device etc). libtss2-sys and the higher layers in
the TSS2 are provided with an instance of a TCTI when instantiated.
They then use this TCTI instance to transmit TPM2 commands and receive
responses.

Since the TCTI library is specific to the IPC mechanism in use we must have
a TCTI specific to UEFI. This TCTI is implemented as a thin software layer
that invokes the SubmitCommand from the TCG2 UEFI protocol. This is
effectively an adapter between the interface expected by the TSS2 programming
APIs and the one exposed by the TCG2 UEFI protocol.

### libtss2-mu
Like most C APIs the TSS2 APIs take C types as parameters and return values.
TPM2 command and responses on the other hand are sent to the TPM2 as byte
buffers in network byte order. This is true of the Linux kernel interface as
well as the Windows TBS and UEFI TCG2 protocol. This results in a lot of code
in the programming APIs simply converting TPM2 objects from C types to a
network byte stream and back again.

To minimize code duplication and promote general best practices the TSS2
defines an API dedicated to these transforms. This process is referred to as
"type marshalling" and "type unmarshalling" in the specification and
libtss2-mu provides both a marshalling and unmarshalling function for each
TPM2 object / C type. Use of this library by TSS2 layers is not strictly
required though it is encouraged. The tpm2-tss OSS project uses libtss2-mu
throughout.

### libtss2-sys
The System API, implemented in libtss2-sys, is a 1-to-1 mapping of C functions
to TPM2 commands. Applications using libtss2-sys send commands to the TPM2 by
invoking these functions while passing them parameters as documented in part 3
of the TPM2 library specification. Internally the libtss2-sys implementation
uses libtss2-mu to transform these parameters from C types into TPM2 command
buffers. The command buffers are then transmitted to the next layer of the
TSS2 using the TCTI instance passed to the libtss2-sys initialization
function. When the response is received the process is reversed and the
response data returned to the caller.

## EDK2 build integration
Integrating the TSS2 libraries and example UEFI applications into the EDK2
build requires two high level tasks:
1) The source code for the TSS2 must be integrated with the EDK2 source tree
as git submodules.
2) Meta-data files describing how to build the TSS2 libraries and example
applications must be created.

The initial approach taken in integrating TSS2 into EDK2 has side-stepped the
complexities of identifying the appropriate location in the source tree to
store this new data. Instead we've opted to create a new \*Pkg directory in
the root of the EDK2 source tree: `Tpm2TssPkg`. The following sections will
describe:
1) Each of the repositories that are included as submodules.
2) The EDK2 build metadata necessary to build the required libraries and
applications.
3) Issues associated with integrating each into the logical structure of the
EDK2 build tree.

The package `.dec` and `.dsc` files are located in the root of the
`Tpm2TssPkg` directory. The `.dec` file is very straight forward declaring
a simple `Includes` section where the public headers are located as well as
an `Includes.common.private` section identifying where the internal headers
live. The `.dsc` file identifies the minimal LibraryClasses necessary to
build the libraries as well as the example UEFI applications. The `.dsc`
file is a necessary evil required to enable this initial demonstration and
will hopefully not be necessary in future iterations of this work.

### https://github.com/tpm2-software/tpm2-tss.git
The TSS2 project began as a single repository hosting a single programming
library. It has since grown to include ~5 libraries including several common
TCTI libraries (interfaces to Windows TBS, Linux kernel driver, the TPM2
simulator) as well as the standard programming APIs (libtss2-mu, libtss2-sys
and libtss2-esys). For the purposes of a minimal use-case we only need the
core headers that define C types for TPM2 objects, the type marshalling
library (libtss2-mu) and the system API (libtss2-sys) as discussed above.

Both of the required libraries have minimal external dependencies and only
require the standard C library. All other code in these libraries is simply
c99. The structure of the TSS2 source code is such that an additional utility
library containing utility functions common to both libraries. The current
prototype is structured such that the submodule for the tpm2-tss repo is
cloned directly under the top level `Tpm2TssPkg` alongside the `.inf` and
`.dec` files related to `libtss2-mu` and `libtss2-sys`:
Tpm2TssPkg
./Tpm2TssPkg/
├── tpm2-tss/
├── Tpm2TssMuLib.dec
├── Tpm2TssMuLib.inf
├── Tpm2TssSysLib.dec
├── Tpm2TssSysLib.inf
├── Tpm2TssUtilLib.dec
└── Tpm2TssUtilLib.inf

### https://github.com/tpm2-software/tpm2-tcti-uefi.git
Enabling use of the TSS2 libraries from UEFI requires an adapter layer
described above as the TCTI layer. For UEFI this layer is incredibly thin
and is little more than adapter between the TCG2 protocol driver and the
lowest layer of the TSS2 (libtss2-sys). This TCTI is known as
`libtss2-tcti-uefi`. It's implemented in the `tpm2-tcti-uefi` repository
alongside two utility libraries and several example UEFI applications.

Building the core TCTI library for UEFI under EDK2 is straightforward.
Hosting this library in the `MdePkg` would be ideal. This was however
complicated by this same repo also hosting example UEFI applications as well
as a shared application utility library. According to
https://github.com/tianocore/tianocore.github.io/wiki/MdePkg, applications
and non-base libraries cannot be in `MdePkg`. Normally splitting the
implementation across multiple directories would not be an issue however this
code is pulled in as a submodule. It's possible to use submodules to clone
the same repo in multiple places in the EDK2 source tree however this seemed
like a far worse option than lumping the initial implementation into a single
directory:

./Tpm2TssPkg
├── string.h
├── tpm2-tcti-uefi
├── Tcg2GetCaps.inf
├── Tcg2GetEventLog.inf
├── Tcg2GetPcrBanks.inf
├── Tpm2GetCapsFixed.inf
├── Tpm2TssTcg2UtilLib.dec
├── Tpm2TssTcg2UtilLib.inf
├── Tpm2TssTctiUefiLib.dec
├── Tpm2TssTctiUefiLib.inf
├── Tpm2TssUefiExampleLib.dec
├── Tpm2TssUefiExampleLib.inf
├── Tpm2TssUefiUtilLib.dec
├── Tpm2TssUefiUtilLib.inf
├── Tpm2TssUtilLib.dec
└── Tpm2TssUtilLib.inf

Feedback on other more clean approaches to integrate this work with EDK2 would
be welcomed.
