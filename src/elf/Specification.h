/*
 * File: Specification.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Specification_H_
#define _ELF_Specification_H_

#include <inttypes.h>
#include <tools/common.h>

namespace ELF {
    
typedef uint8_t  UChar;

enum FileIdentificatorBytes {

	 EI_NIDENT = 16,

	 EI_MAG0 = 0,
	 EI_MAG1 = 1,
	 EI_MAG2 = 2,
	 EI_MAG3 = 3,
	
	 EI_CLASS = 4,
	 EI_DATA = 5,
	 EI_VERSION = 6,

	 EI_OSABI  = 7,     /* 64 bit only OS/ABI identification */
	 EI_ABIVERSION = 8, /* 64 bit only OS/ABI identification */

	 EI_PAD = 9,

};

enum Class {
    ELFCLASSNONE = 0,
    ELFCLASS32 = 1,
    ELFCLASS64 = 2,
};

enum Data {
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2,
};

enum Version {
    EV_NONE = 0,
    EV_CURRENT = 1,
};


enum Type {
   ET_NONE = 0,        
   ET_REL = 1,         
   ET_EXEC = 2,        
   ET_DYN = 3,         
   ET_CORE = 4,        
   ET_LOOS = 0xfe00,   
   ET_HIOS = 0xfeff,   
   ET_LOPROC = 0xff00, 
   ET_HIPROC = 0xffff  
};

enum Machine {
   EM_NONE = 0,           // No machine
   EM_M32 = 1,            // AT&T WE 32100
   EM_SPARC = 2,          // SPARC
   EM_386 = 3,            // Intel 386
   EM_68K = 4,            // Motorola 68000
   EM_88K = 5,            // Motorola 88000
   EM_IAMCU = 6,          // Intel MCU
   EM_860 = 7,            // Intel 80860
   EM_MIPS = 8,           // MIPS R3000
   EM_S370 = 9,           // IBM System/370
   EM_MIPS_RS3_LE = 10,   // MIPS RS3000 Little-endian
   EM_PARISC = 15,        // Hewlett-Packard PA-RISC
   EM_VPP500 = 17,        // Fujitsu VPP500
   EM_SPARC32PLUS = 18,   // Enhanced instruction set SPARC
   EM_960 = 19,           // Intel 80960
   EM_PPC = 20,           // PowerPC
   EM_PPC64 = 21,         // PowerPC64
   EM_S390 = 22,          // IBM System/390
   EM_SPU = 23,           // IBM SPU/SPC
   EM_V800 = 36,          // NEC V800
   EM_FR20 = 37,          // Fujitsu FR20
   EM_RH32 = 38,          // TRW RH-32
   EM_RCE = 39,           // Motorola RCE
   EM_ARM = 40,           // ARM
   EM_ALPHA = 41,         // DEC Alpha
   EM_SH = 42,            // Hitachi SH
   EM_SPARCV9 = 43,       // SPARC V9
   EM_TRICORE = 44,       // Siemens TriCore
   EM_ARC = 45,           // Argonaut RISC Core
   EM_H8_300 = 46,        // Hitachi H8/300
   EM_H8_300H = 47,       // Hitachi H8/300H
   EM_H8S = 48,           // Hitachi H8S
   EM_H8_500 = 49,        // Hitachi H8/500
   EM_IA_64 = 50,         // Intel IA-64 processor architecture
   EM_MIPS_X = 51,        // Stanford MIPS-X
   EM_COLDFIRE = 52,      // Motorola ColdFire
   EM_68HC12 = 53,        // Motorola M68HC12
   EM_MMA = 54,           // Fujitsu MMA Multimedia Accelerator
   EM_PCP = 55,           // Siemens PCP
   EM_NCPU = 56,          // Sony nCPU embedded RISC processor
   EM_NDR1 = 57,          // Denso NDR1 microprocessor
   EM_STARCORE = 58,      // Motorola Star*Core processor
   EM_ME16 = 59,          // Toyota ME16 processor
   EM_ST100 = 60,         // STMicroelectronics ST100 processor
   EM_TINYJ = 61,         // Advanced Logic Corp. TinyJ embedded processor family
   EM_X86_64 = 62,        // AMD x86-64 architecture
   EM_PDSP = 63,          // Sony DSP Processor
   EM_PDP10 = 64,         // Digital Equipment Corp. PDP-10
   EM_PDP11 = 65,         // Digital Equipment Corp. PDP-11
   EM_FX66 = 66,          // Siemens FX66 microcontroller
   EM_ST9PLUS = 67,       // STMicroelectronics ST9+ 8/16 bit microcontroller
   EM_ST7 = 68,           // STMicroelectronics ST7 8-bit microcontroller
   EM_68HC16 = 69,        // Motorola MC68HC16 Microcontroller
   EM_68HC11 = 70,        // Motorola MC68HC11 Microcontroller
   EM_68HC08 = 71,        // Motorola MC68HC08 Microcontroller
   EM_68HC05 = 72,        // Motorola MC68HC05 Microcontroller
   EM_SVX = 73,           // Silicon Graphics SVx
   EM_ST19 = 74,          // STMicroelectronics ST19 8-bit microcontroller
   EM_VAX = 75,           // Digital VAX
   EM_CRIS = 76,          // Axis Communications 32-bit embedded processor
   EM_JAVELIN = 77,       // Infineon Technologies 32-bit embedded processor
   EM_FIREPATH = 78,      // Element 14 64-bit DSP Processor
   EM_ZSP = 79,           // LSI Logic 16-bit DSP Processor
   EM_MMIX = 80,          // Donald Knuth's educational 64-bit processor
   EM_HUANY = 81,         // Harvard University machine-independent object files
   EM_PRISM = 82,         // SiTera Prism
   EM_AVR = 83,           // Atmel AVR 8-bit microcontroller
   EM_FR30 = 84,          // Fujitsu FR30
   EM_D10V = 85,          // Mitsubishi D10V
   EM_D30V = 86,          // Mitsubishi D30V
   EM_V850 = 87,          // NEC v850
   EM_M32R = 88,          // Mitsubishi M32R
   EM_MN10300 = 89,       // Matsushita MN10300
   EM_MN10200 = 90,       // Matsushita MN10200
   EM_PJ = 91,            // picoJava
   EM_OPENRISC = 92,      // OpenRISC 32-bit embedded processor
   EM_ARC_COMPACT = 93,   // ARC International ARCompact processor (old
                          // spelling/synonym: EM_ARC_A5)
   EM_XTENSA = 94,        // Tensilica Xtensa Architecture
   EM_VIDEOCORE = 95,     // Alphamosaic VideoCore processor
   EM_TMM_GPP = 96,       // Thompson Multimedia General Purpose Processor
   EM_NS32K = 97,         // National Semiconductor 32000 series
   EM_TPC = 98,           // Tenor Network TPC processor
   EM_SNP1K = 99,         // Trebia SNP 1000 processor
   EM_ST200 = 100,        // STMicroelectronics (www.st.com) ST200
   EM_IP2K = 101,         // Ubicom IP2xxx microcontroller family
   EM_MAX = 102,          // MAX Processor
   EM_CR = 103,           // National Semiconductor CompactRISC microprocessor
   EM_F2MC16 = 104,       // Fujitsu F2MC16
   EM_MSP430 = 105,       // Texas Instruments embedded microcontroller msp430
   EM_BLACKFIN = 106,     // Analog Devices Blackfin (DSP) processor
   EM_SE_C33 = 107,       // S1C33 Family of Seiko Epson processors
   EM_SEP = 108,          // Sharp embedded microprocessor
   EM_ARCA = 109,         // Arca RISC Microprocessor
   EM_UNICORE = 110,      // Microprocessor series from PKU-Unity Ltd. and MPRC
                          // of Peking University
   EM_EXCESS = 111,       // eXcess: 16/32/64-bit configurable embedded CPU
   EM_DXP = 112,          // Icera Semiconductor Inc. Deep Execution Processor
   EM_ALTERA_NIOS2 = 113, // Altera Nios II soft-core processor
   EM_CRX = 114,          // National Semiconductor CompactRISC CRX
   EM_XGATE = 115,        // Motorola XGATE embedded processor
   EM_C166 = 116,         // Infineon C16x/XC16x processor
   EM_M16C = 117,         // Renesas M16C series microprocessors
   EM_DSPIC30F = 118,     // Microchip Technology dsPIC30F Digital Signal
                          // Controller
   EM_CE = 119,           // Freescale Communication Engine RISC core
   EM_M32C = 120,         // Renesas M32C series microprocessors
   EM_TSK3000 = 131,      // Altium TSK3000 core
   EM_RS08 = 132,         // Freescale RS08 embedded processor
   EM_SHARC = 133,        // Analog Devices SHARC family of 32-bit DSP
                          // processors
   EM_ECOG2 = 134,        // Cyan Technology eCOG2 microprocessor
   EM_SCORE7 = 135,       // Sunplus S+core7 RISC processor
   EM_DSP24 = 136,        // New Japan Radio (NJR) 24-bit DSP Processor
   EM_VIDEOCORE3 = 137,   // Broadcom VideoCore III processor
   EM_LATTICEMICO32 = 138, // RISC processor for Lattice FPGA architecture
   EM_SE_C17 = 139,        // Seiko Epson C17 family
   EM_TI_C6000 = 140,      // The Texas Instruments TMS320C6000 DSP family
   EM_TI_C2000 = 141,      // The Texas Instruments TMS320C2000 DSP family
   EM_TI_C5500 = 142,      // The Texas Instruments TMS320C55x DSP family
   EM_MMDSP_PLUS = 160,    // STMicroelectronics 64bit VLIW Data Signal Processor
   EM_CYPRESS_M8C = 161,   // Cypress M8C microprocessor
   EM_R32C = 162,          // Renesas R32C series microprocessors
   EM_TRIMEDIA = 163,      // NXP Semiconductors TriMedia architecture family
   EM_HEXAGON = 164,       // Qualcomm Hexagon processor
   EM_8051 = 165,          // Intel 8051 and variants
   EM_STXP7X = 166,        // STMicroelectronics STxP7x family of configurable
                           // and extensible RISC processors
   EM_NDS32 = 167,         // Andes Technology compact code size embedded RISC
                           // processor family
   EM_ECOG1 = 168,         // Cyan Technology eCOG1X family
   EM_ECOG1X = 168,        // Cyan Technology eCOG1X family
   EM_MAXQ30 = 169,        // Dallas Semiconductor MAXQ30 Core Micro-controllers
   EM_XIMO16 = 170,        // New Japan Radio (NJR) 16-bit DSP Processor
   EM_MANIK = 171,         // M2000 Reconfigurable RISC Microprocessor
   EM_CRAYNV2 = 172,       // Cray Inc. NV2 vector architecture
   EM_RX = 173,            // Renesas RX family
   EM_METAG = 174,         // Imagination Technologies META processor
                           // architecture
   EM_MCST_ELBRUS = 175,   // MCST Elbrus general purpose hardware architecture
   EM_ECOG16 = 176,        // Cyan Technology eCOG16 family
   EM_CR16 = 177,          // National Semiconductor CompactRISC CR16 16-bit
                           // microprocessor
   EM_ETPU = 178,          // Freescale Extended Time Processing Unit
   EM_SLE9X = 179,         // Infineon Technologies SLE9X core
   EM_L10M = 180,          // Intel L10M
   EM_K10M = 181,          // Intel K10M
   EM_AARCH64 = 183,       // ARM AArch64
   EM_AVR32 = 185,         // Atmel Corporation 32-bit microprocessor family
   EM_STM8 = 186,          // STMicroeletronics STM8 8-bit microcontroller
   EM_TILE64 = 187,        // Tilera TILE64 multicore architecture family
   EM_TILEPRO = 188,       // Tilera TILEPro multicore architecture family
   EM_MICROBLAZE = 189,    // Xilinx MicroBlaze 32-bit RISC soft processor core
   EM_CUDA = 190,          // NVIDIA CUDA architecture
   EM_TILEGX = 191,        // Tilera TILE-Gx multicore architecture family
   EM_CLOUDSHIELD = 192,   // CloudShield architecture family
   EM_COREA_1ST = 193,     // KIPO-KAIST Core-A 1st generation processor family
   EM_COREA_2ND = 194,     // KIPO-KAIST Core-A 2nd generation processor family
   EM_ARC_COMPACT2 = 195,  // Synopsys ARCompact V2
   EM_OPEN8 = 196,         // Open8 8-bit RISC soft processor core
   EM_RL78 = 197,          // Renesas RL78 family
   EM_VIDEOCORE5 = 198,    // Broadcom VideoCore V processor
   EM_78KOR = 199,         // Renesas 78KOR family
   EM_56800EX = 200,       // Freescale 56800EX Digital Signal Controller (DSC)
   EM_BA1 = 201,           // Beyond BA1 CPU architecture
   EM_BA2 = 202,           // Beyond BA2 CPU architecture
   EM_XCORE = 203,         // XMOS xCORE processor family
   EM_MCHP_PIC = 204,      // Microchip 8-bit PIC(r) family
   EM_INTEL205 = 205,      // Reserved by Intel
   EM_INTEL206 = 206,      // Reserved by Intel
   EM_INTEL207 = 207,      // Reserved by Intel
   EM_INTEL208 = 208,      // Reserved by Intel
   EM_INTEL209 = 209,      // Reserved by Intel
   EM_KM32 = 210,          // KM211 KM32 32-bit processor
   EM_KMX32 = 211,         // KM211 KMX32 32-bit processor
   EM_KMX16 = 212,         // KM211 KMX16 16-bit processor
   EM_KMX8 = 213,          // KM211 KMX8 8-bit processor
   EM_KVARC = 214,         // KM211 KVARC processor
   EM_CDP = 215,           // Paneve CDP architecture family
   EM_COGE = 216,          // Cognitive Smart Memory Processor
   EM_COOL = 217,          // iCelero CoolEngine
   EM_NORC = 218,          // Nanoradio Optimized RISC
   EM_CSR_KALIMBA = 219,   // CSR Kalimba architecture family
   EM_AMDGPU = 224,        // AMD GPU architecture
   EM_RISCV = 243,         // RISC-V
   EM_LANAI = 244,         // Lanai 32-bit processor
   EM_BPF = 247,           // Linux kernel bpf virtual machine
   EM_VE = 251,            // NEC SX-Aurora VE
   EM_CSKY = 252,          // C-SKY 32-bit processor
};


enum OSABI {
   ELFOSABI_NONE = 0,           // UNIX System V ABI
   ELFOSABI_HPUX = 1,           // HP-UX operating system
   ELFOSABI_NETBSD = 2,         // NetBSD
   ELFOSABI_GNU = 3,            // GNU/Linux
   ELFOSABI_LINUX = 3,          // Historical alias for ELFOSABI_GNU.
   ELFOSABI_HURD = 4,           // GNU/Hurd
   ELFOSABI_SOLARIS = 6,        // Solaris
   ELFOSABI_AIX = 7,            // AIX
   ELFOSABI_IRIX = 8,           // IRIX
   ELFOSABI_FREEBSD = 9,        // FreeBSD
   ELFOSABI_TRU64 = 10,         // TRU64 UNIX
   ELFOSABI_MODESTO = 11,       // Novell Modesto
   ELFOSABI_OPENBSD = 12,       // OpenBSD
   ELFOSABI_OPENVMS = 13,       // OpenVMS
   ELFOSABI_NSK = 14,           // Hewlett-Packard Non-Stop Kernel
   ELFOSABI_AROS = 15,          // AROS
   ELFOSABI_FENIXOS = 16,       // FenixOS
   ELFOSABI_CLOUDABI = 17,      // Nuxi CloudABI
   ELFOSABI_FIRST_ARCH = 64,    // First architecture-specific OS ABI
   ELFOSABI_AMDGPU_HSA = 64,    // AMD HSA runtime
   ELFOSABI_AMDGPU_PAL = 65,    // AMD PAL runtime
   ELFOSABI_AMDGPU_MESA3D = 66, // AMD GCN GPUs (GFX6+) for MESA runtime
   ELFOSABI_ARM = 97,           // ARM
   ELFOSABI_C6000_ELFABI = 64,  // Bare-metal TMS320C6000
   ELFOSABI_C6000_LINUX = 65,   // Linux TMS320C6000
   ELFOSABI_STANDALONE = 255,   // Standalone (embedded) application
   ELFOSABI_LAST_ARCH = 255     //
};

 // ARM Specific e_flags // * what is it - found in LLVM
 enum : uint32_t {
   EF_ARM_SOFT_FLOAT = 0x00000200U,     // Legacy pre EABI_VER5
   EF_ARM_ABI_FLOAT_SOFT = 0x00000200U, // EABI_VER5
   EF_ARM_VFP_FLOAT = 0x00000400U,      // Legacy pre EABI_VER5
   EF_ARM_ABI_FLOAT_HARD = 0x00000400U, // EABI_VER5
   EF_ARM_EABI_UNKNOWN = 0x00000000U,
   EF_ARM_EABI_VER1 = 0x01000000U,
   EF_ARM_EABI_VER2 = 0x02000000U,
   EF_ARM_EABI_VER3 = 0x03000000U,
   EF_ARM_EABI_VER4 = 0x04000000U,
   EF_ARM_EABI_VER5 = 0x05000000U,
   EF_ARM_EABIMASK = 0xFF000000U
 };

enum SegmentType {
   PT_NULL = 0,            // Unused segment.
   PT_LOAD = 1,            // Loadable segment.
   PT_DYNAMIC = 2,         // Dynamic linking information.
   PT_INTERP = 3,          // Interpreter pathname.
   PT_NOTE = 4,            // Auxiliary information.
   PT_SHLIB = 5,           // Reserved.
   PT_PHDR = 6,            // The program header table itself.
   PT_TLS = 7,             // The thread-local storage template.
   PT_LOOS = 0x60000000,   // Lowest operating system-specific pt entry type.
   PT_HIOS = 0x6fffffff,   // Highest operating system-specific pt entry type.
   PT_LOPROC = 0x70000000, // Lowest processor-specific program hdr entry type.
   PT_HIPROC = 0x7fffffff, // Highest processor-specific program hdr entry type.
  
   // x86-64 program header types.
   // These all contain stack unwind tables.
   PT_GNU_EH_FRAME = 0x6474e550,
   PT_SUNW_EH_FRAME = 0x6474e550,
   PT_SUNW_UNWIND = 0x6464e550,
  
   PT_GNU_STACK = 0x6474e551,    // Indicates stack executability.
   PT_GNU_RELRO = 0x6474e552,    // Read-only after relocation.
   PT_GNU_PROPERTY = 0x6474e553, // .note.gnu.property notes sections.
  
   PT_OPENBSD_RANDOMIZE = 0x65a3dbe6, // Fill with random data.
   PT_OPENBSD_WXNEEDED = 0x65a3dbe7,  // Program does W^X violations.
   PT_OPENBSD_BOOTDATA = 0x65a41be6,  // Section for boot arguments.
  
   // ARM program header types.
   PT_ARM_ARCHEXT = 0x70000000, // Platform architecture compatibility info
   // These all contain stack unwind tables.
   PT_ARM_EXIDX = 0x70000001,
   PT_ARM_UNWIND = 0x70000001,
  
   // MIPS program header types.
   PT_MIPS_REGINFO = 0x70000000,  // Register usage information.
   PT_MIPS_RTPROC = 0x70000001,   // Runtime procedure table.
   PT_MIPS_OPTIONS = 0x70000002,  // Options segment.
   PT_MIPS_ABIFLAGS = 0x70000003, // Abiflags segment.
};

enum SectionType {
   SHT_PROGBITS = 1,       // Program-defined contents.
   SHT_SYMTAB = 2,         // Symbol table.
   SHT_STRTAB = 3,         // String table.
   SHT_RELA = 4,           // Relocation entries; explicit addends.
   SHT_HASH = 5,           // Symbol hash table.
   SHT_DYNAMIC = 6,        // Information for dynamic linking.
   SHT_NOTE = 7,           // Information about the file.
   SHT_NOBITS = 8,         // Data occupies no space in the file.
   SHT_REL = 9,            // Relocation entries; no explicit addends.
   SHT_SHLIB = 10,         // Reserved.
   SHT_DYNSYM = 11,        // Symbol table.
   SHT_INIT_ARRAY = 14,    // Pointers to initialization functions.
   SHT_FINI_ARRAY = 15,    // Pointers to termination functions.
   SHT_PREINIT_ARRAY = 16, // Pointers to pre-init functions.
   SHT_GROUP = 17,         // Section group.
   SHT_SYMTAB_SHNDX = 18,  // Indices for SHN_XINDEX entries.
   // Experimental support for SHT_RELR sections. For details, see proposal
   // at https://groups.google.com/forum/#!topic/generic-abi/bX460iggiKg
   SHT_RELR = 19,         // Relocation entries; only offsets.
   SHT_LOOS = 0x60000000, // Lowest operating system-specific type.
   // Android packed relocation section types.
   // https://android.googlesource.com/platform/bionic/+/6f12bfece5dcc01325e0abba56a46b1bcf991c69/tools/relocation_packer/src/elf_file.cc#37
   SHT_ANDROID_REL = 0x60000001,
   SHT_ANDROID_RELA = 0x60000002,
   SHT_LLVM_ODRTAB = 0x6fff4c00,         // LLVM ODR table.
   SHT_LLVM_LINKER_OPTIONS = 0x6fff4c01, // LLVM Linker Options.
   SHT_LLVM_ADDRSIG = 0x6fff4c03,        // List of address-significant symbols
                                         // for safe ICF.
   SHT_LLVM_DEPENDENT_LIBRARIES =
       0x6fff4c04,                    // LLVM Dependent Library Specifiers.
   SHT_LLVM_SYMPART = 0x6fff4c05,     // Symbol partition specification.
   SHT_LLVM_PART_EHDR = 0x6fff4c06,   // ELF header for loadable partition.
   SHT_LLVM_PART_PHDR = 0x6fff4c07,   // Phdrs for loadable partition.
   SHT_LLVM_BB_ADDR_MAP = 0x6fff4c08, // LLVM Basic Block Address Map.
   SHT_LLVM_CALL_GRAPH_PROFILE = 0x6fff4c09, // LLVM Call Graph Profile.
   // Android's experimental support for SHT_RELR sections.
   // https://android.googlesource.com/platform/bionic/+/b7feec74547f84559a1467aca02708ff61346d2a/libc/include/elf.h#512
   SHT_ANDROID_RELR = 0x6fffff00,   // Relocation entries; only offsets.
   SHT_GNU_ATTRIBUTES = 0x6ffffff5, // Object attributes.
   SHT_GNU_HASH = 0x6ffffff6,       // GNU-style hash table.
   SHT_GNU_verdef = 0x6ffffffd,     // GNU version definitions.
   SHT_GNU_verneed = 0x6ffffffe,    // GNU version references.
   SHT_GNU_versym = 0x6fffffff,     // GNU symbol versions table.
   SHT_HIOS = 0x6fffffff,           // Highest operating system-specific type.
   SHT_LOPROC = 0x70000000,         // Lowest processor arch-specific type.
   // Fixme: All this is duplicated in MCSectionELF. Why??
   // Exception Index table
   SHT_ARM_EXIDX = 0x70000001U,
   // BPABI DLL dynamic linking pre-emption map
   SHT_ARM_PREEMPTMAP = 0x70000002U,
   //  Object file compatibility attributes
   SHT_ARM_ATTRIBUTES = 0x70000003U,
   SHT_ARM_DEBUGOVERLAY = 0x70000004U,
   SHT_ARM_OVERLAYSECTION = 0x70000005U,
   SHT_HEX_ORDERED = 0x70000000,   // Link editor is to sort the entries in
                                   // this section based on their sizes
   SHT_X86_64_UNWIND = 0x70000001, // Unwind information
  
   SHT_MIPS_REGINFO = 0x70000006,  // Register usage information
   SHT_MIPS_OPTIONS = 0x7000000d,  // General options
   SHT_MIPS_DWARF = 0x7000001e,    // DWARF debugging section.
   SHT_MIPS_ABIFLAGS = 0x7000002a, // ABI information.
  
   SHT_MSP430_ATTRIBUTES = 0x70000003U,
  
   SHT_RISCV_ATTRIBUTES = 0x70000003U,
  
   SHT_HIPROC = 0x7fffffff, // Highest processor arch-specific type.
   SHT_LOUSER = 0x80000000, // Lowest type reserved for applications.
   SHT_HIUSER = 0xffffffff  // Highest type reserved for applications.

};

enum SymbolBind {
   STB_LOCAL = 0,
   STB_GLOBAL = 1,
   STB_WEAK = 2,
   STB_GNU_UNIQUE = 10,
   STB_LOOS = 10,
   STB_HIOS = 12,
   STB_LOPROC = 13,
   STB_HIPROC = 15  
};

enum SymbolType {
   STT_NOTYPE = 0,
   STT_OBJECT = 1,
   STT_FUNC = 2,
   STT_SECTION = 3,
   STT_FILE = 4,
   STT_COMMON = 5,
   STT_TLS = 6,
   STT_GNU_IFUNC = 10,
   STT_LOOS = 10,
   STT_HIOS = 12,
   STT_LOPROC = 13,
   STT_HIPROC = 15
};

enum DynamicTags : uint32_t {
    DT_NULL = 0,
    DT_NEEDED = 1,
    DT_PLTRELSZ = 2,
    DT_PLTGOT = 3,
    DT_HASH = 4,
    DT_STRTAB = 5,
    DT_SYMTAB = 6,
    DT_RELA = 7,
    DT_RELASZ = 8,
    DT_RELAENT = 9,
    DT_STRSZ = 10,
    DT_SYMENT = 11,
    DT_INIT = 12,
    DT_FINI = 13,
    DT_SONAME = 14,
    DT_RPATH = 15,
    DT_SYMBOLIC = 16,
    DT_REL = 17,
    DT_RELSZ = 18,
    DT_RELENT = 19,
    DT_PLTREL = 20,
    DT_DEBUG = 21,
    DT_TEXTREL = 22,
    DT_JMPREL = 23,
    DT_BIND_NOW = 24,
    DT_INIT_ARRAY = 25,
    DT_FINI_ARRAY = 26,
    DT_INIT_ARRAYSZ = 27,
    DT_FINI_ARRAYSZ = 28,
    DT_RUNPATH = 29,
    DT_FLAGS = 30,
    DT_ENCODING = 32,
    DT_PREINIT_ARRAY = 32,
    DT_PREINIT_ARRAYSZ = 33,
    DT_MAXPOSTAGS = 34,
    DT_LOOS = 0x6000000d,
    DT_SUNW_AUXILIARY = 0x6000000d,
    DT_SUNW_RTLDINF = 0x6000000e,
    DT_SUNW_FILTER = 0x6000000e,
    DT_SUNW_CAP = 0x60000010,
    DT_SUNW_SYMTAB = 0x60000011,
    DT_SUNW_SYMSZ = 0x60000012,
    DT_SUNW_ENCODING = 0x60000013,
    DT_SUNW_SORTENT = 0x60000013,
    DT_SUNW_SYMSORT = 0x60000014,
    DT_SUNW_SYMSORTSZ = 0x60000015,
    DT_SUNW_TLSSORT = 0x60000016,
    DT_SUNW_TLSSORTSZ = 0x60000017,
    DT_SUNW_CAPINFO = 0x60000018,
    DT_SUNW_STRPAD = 0x60000019,
    DT_SUNW_CAPCHAIN = 0x6000001a,
    DT_SUNW_LDMACH = 0x6000001b,
    DT_SUNW_CAPCHAINENT = 0x6000001d,
    DT_SUNW_CAPCHAINSZ = 0x6000001f,
    DT_HIOS = 0x6ffff000,
    DT_VALRNGLO = 0x6ffffd00,
    DT_CHECKSUM = 0x6ffffdf8,
    DT_PLTPADSZ = 0x6ffffdf9,
    DT_MOVEENT = 0x6ffffdfa,
    DT_MOVESZ = 0x6ffffdfb,
    DT_POSFLAG_1 = 0x6ffffdfd,
    DT_SYMINSZ = 0x6ffffdfe,
    DT_SYMINENT = 0x6ffffdff,
    DT_VALRNGHI = 0x6ffffdff,
    DT_ADDRRNGLO = 0x6ffffe00,
    DT_GNUHASH = 0x6ffffef5,
    DT_CONFIG = 0x6ffffefa,
    DT_DEPAUDIT = 0x6ffffefb,
    DT_AUDIT = 0x6ffffefc,
    DT_PLTPAD = 0x6ffffefd,
    DT_MOVETAB = 0x6ffffefe,
    DT_SYMINFO = 0x6ffffeff,
    DT_ADDRRNGHI = 0x6ffffeff,
    DT_RELACOUNT = 0x6ffffff9,
    DT_RELCOUNT = 0x6ffffffa,
    DT_FLAGS_1 = 0x6ffffffb,
    DT_VERDEF = 0x6ffffffc,
    DT_VERDEFNUM = 0x6ffffffd,
    DT_VERNEED = 0x6ffffffe,
    DT_VERNEEDNUM = 0x6fffffff,
    DT_LOPROC = 0x70000000,
    DT_SPARC_REGISTER = 0x70000001,
    DT_AUXILIARY = 0x7ffffffd,
    DT_USED = 0x7ffffffe,
    DT_FILTER = 0x7fffffff,
    DT_HIPROC = 0x7fffffff,
};

namespace Map {
	extern ::Tools::ValueMap Class;
	extern ::Tools::ValueMap Data;
	extern ::Tools::ValueMap Version;
    extern ::Tools::ValueMap SegmentType;
    extern ::Tools::ValueMap SectionType;
    extern ::Tools::ValueMap SymbolBind;
    extern ::Tools::ValueMap SymbolType;
    extern ::Tools::ValueMap DynamicTag;
}


}

#endif /* _ELF_Specification_H_ */
