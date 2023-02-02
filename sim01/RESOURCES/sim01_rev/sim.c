typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned char    dwfenc;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned long    qword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef struct eh_frame_hdr eh_frame_hdr, *Peh_frame_hdr;

struct eh_frame_hdr {
    byte eh_frame_hdr_version; // Exception Handler Frame Header Version
    dwfenc eh_frame_pointer_encoding; // Exception Handler Frame Pointer Encoding
    dwfenc eh_frame_desc_entry_count_encoding; // Encoding of # of Exception Handler FDEs
    dwfenc eh_frame_table_encoding; // Exception Handler Table Encoding
};

typedef struct fde_table_entry fde_table_entry, *Pfde_table_entry;

struct fde_table_entry {
    dword initial_loc; // Initial Location
    dword data_loc; // Data location
};

typedef void _IO_lock_t;

typedef struct _IO_marker _IO_marker, *P_IO_marker;

typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

typedef long __off_t;

typedef long __off64_t;

typedef ulong size_t;

struct _IO_FILE {
    int _flags;
    char * _IO_read_ptr;
    char * _IO_read_end;
    char * _IO_read_base;
    char * _IO_write_base;
    char * _IO_write_ptr;
    char * _IO_write_end;
    char * _IO_buf_base;
    char * _IO_buf_end;
    char * _IO_save_base;
    char * _IO_backup_base;
    char * _IO_save_end;
    struct _IO_marker * _markers;
    struct _IO_FILE * _chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    ushort _cur_column;
    char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t * _lock;
    __off64_t _offset;
    void * __pad1;
    void * __pad2;
    void * __pad3;
    void * __pad4;
    size_t __pad5;
    int _mode;
    char _unused2[20];
};

struct _IO_marker {
    struct _IO_marker * _next;
    struct _IO_FILE * _sbuf;
    int _pos;
};

typedef ulong sizetype;

typedef bool _Bool;


// WARNING! conflicting data type names: /DWARF/libio.h/_IO_marker - /libio.h/_IO_marker


// WARNING! conflicting data type names: /DWARF/libio.h/_IO_FILE - /stdio.h/_IO_FILE

typedef enum ConfigDataCodes {
    CPU_SCHED_SJF_N_CODE=0,
    CPU_SCHED_SRTF_P_CODE=1,
    CPU_SCHED_FCFS_P_CODE=2,
    CPU_SCHED_RR_P_CODE=3,
    CPU_SCHED_FCFS_N_CODE=4,
    LOGTO_MONITOR_CODE=5,
    LOGTO_FILE_CODE=6,
    LOGTO_BOTH_CODE=7,
    NON_PREEMPTIVE_CODE=8,
    PREEMPTIVE_CODE=9
} ConfigDataCodes;

typedef enum ConfigCodeMessages {
    CFG_FILE_ACCESS_ERR=0,
    CFG_CORRUPT_DESCRIPTOR_ERR=1,
    CFG_DATA_OUT_OF_RANGE_ERR=2,
    CFG_CORRUPT_PROMPT_ERR=3,
    CFG_VERSION_CODE=4,
    CFG_MD_FILE_NAME_CODE=5,
    CFG_CPU_SCHED_CODE=6,
    CFG_QUANT_CYCLES_CODE=7,
    CFG_MEM_DISPLAY_CODE=8,
    CFG_MEM_AVAILABLE_CODE=9,
    CFG_PROC_CYCLES_CODE=10,
    CFG_IO_CYCLES_CODE=11,
    CFG_LOG_TO_CODE=12,
    CFG_LOG_FILE_NAME_CODE=13
} ConfigCodeMessages;

typedef struct _IO_FILE FILE;

typedef long __time_t;

typedef long __suseconds_t;

typedef enum OpCodeMessages {
    BAD_ARG_VAL=-1,
    NO_ACCESS_ERR=0,
    MD_FILE_ACCESS_ERR=1,
    MD_CORRUPT_DESCRIPTOR_ERR=2,
    OPCMD_ACCESS_ERR=3,
    CORRUPT_OPCMD_ERR=4,
    CORRUPT_OPCMD_ARG_ERR=5,
    UNBALANCED_START_END_ERR=6,
    COMPLETE_OPCMD_FOUND_MSG=7,
    LAST_OPCMD_FOUND_MSG=8
} OpCodeMessages;

typedef struct timeval timeval, *Ptimeval;

struct timeval {
    __time_t tv_sec;
    __suseconds_t tv_usec;
};

typedef struct CmdLineDataStruct CmdLineDataStruct, *PCmdLineDataStruct;

typedef struct CmdLineDataStruct CmdLineData;

struct CmdLineDataStruct {
    _Bool programRunFlag;
    _Bool configDisplayFlag;
    _Bool mdDisplayFlag;
    _Bool runSimFlag;
    char fileName[64];
};

typedef enum anon_enum_32.conflict1d9 {
    ALL_PROCESSES_IN_EXIT=-606,
    ALL_PROCESSES_IN_WAIT=-505,
    NO_PROCESS_ID=-1,
    CPU_SCHED_SJF_N_CODE=0,
    INITIALIZE_INTERRUPT_MGR=0,
    INITIALIZE_REPORT_SYSTEM=0,
    LOGICAL_ZERO=0,
    NEW_STATE=0,
    ZERO_TIMER=0,
    ADD_REPORT_ITEM=1,
    CHECK_FOR_INTERRUPT=1,
    CPU_SCHED_SRTF_P_CODE=1,
    LAP_TIMER=1,
    OPEN_MEMORY=1,
    READY_STATE=1,
    COMPLETE_REPORT=2,
    CPU_SCHED_FCFS_P_CODE=2,
    RUNNING_STATE=2,
    SET_IO_START=2,
    STOP_TIMER=2,
    USED_MEMORY=2,
    BLOCKED_STATE=3,
    CPU_SCHED_RR_P_CODE=3,
    MIN_NUM_ARGS=3,
    RESOLVE_ALL_INTERRUPTS=3,
    CPU_SCHED_FCFS_N_CODE=4,
    EXIT_STATE=4,
    LAST_FOUR_LETTERS=4,
    LOGTO_MONITOR_CODE=5,
    LOGTO_FILE_CODE=6,
    LOGTO_BOTH_CODE=7,
    NON_PREEMPTIVE_CODE=8,
    PREEMPTIVE_CODE=9
} anon_enum_32.conflict1d9;

typedef struct MemNodeType MemNodeType, *PMemNodeType;

struct MemNodeType {
    int physicalStart;
    int physicalStop;
    int memBlockState;
    int processNumber;
    int logicalStart;
    int logicalStop;
    struct MemNodeType * nextNode;
};

typedef struct ConfigDataType ConfigDataType, *PConfigDataType;

struct ConfigDataType {
    double version;
    char metaDataFileName[96];
    int cpuSchedCode;
    int quantumCycles;
    _Bool memDisplay;
    undefined field5_0x71;
    undefined field6_0x72;
    undefined field7_0x73;
    int memAvailable;
    int procCycleRate;
    int ioCycleRate;
    int logToCode;
    char logToFileName[96];
    undefined field13_0xe4;
    undefined field14_0xe5;
    undefined field15_0xe6;
    undefined field16_0xe7;
};

typedef struct PcbNodeType PcbNodeType, *PPcbNodeType;

typedef struct OpCodeType OpCodeType, *POpCodeType;

struct OpCodeType {
    int pid;
    char command[5];
    char inOutArg[5];
    char strArg1[15];
    undefined field4_0x1d;
    undefined field5_0x1e;
    undefined field6_0x1f;
    int intArg2;
    int intArg3;
    double opEndTime;
    struct OpCodeType * nextNode;
};

struct PcbNodeType {
    int pid;
    int state;
    int timeRemaining;
    undefined field3_0xc;
    undefined field4_0xd;
    undefined field5_0xe;
    undefined field6_0xf;
    double startTime;
    _Bool quantumTimeOut;
    undefined field9_0x19;
    undefined field10_0x1a;
    undefined field11_0x1b;
    undefined field12_0x1c;
    undefined field13_0x1d;
    undefined field14_0x1e;
    undefined field15_0x1f;
    struct OpCodeType * currentOpCode;
    struct OpCodeType * opCodeList;
    struct MemNodeType * memList;
    struct PcbNodeType * nextNode;
};

typedef enum InterruptMgrCode {
    INITIALIZE_INTERRUPT_MGR=0,
    CHECK_FOR_INTERRUPT=1,
    SET_IO_START=2,
    RESOLVE_ALL_INTERRUPTS=3
} InterruptMgrCode;

typedef struct ReportNode ReportNode, *PReportNode;

struct ReportNode {
    char dispString[96];
    struct ReportNode * nextNode;
};


// WARNING! conflicting data type names: /time.h/timeval - /DWARF/time.h/timeval

typedef struct timezone timezone, *Ptimezone;

typedef struct timezone * __timezone_ptr_t;

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};


// WARNING! conflicting data type names: /stdio.h/FILE - /DWARF/stdio.h/FILE

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

struct evp_pkey_ctx_st {
};

typedef struct Elf64_Phdr Elf64_Phdr, *PElf64_Phdr;

typedef enum Elf_ProgramHeaderType {
    PT_NULL=0,
    PT_LOAD=1,
    PT_DYNAMIC=2,
    PT_INTERP=3,
    PT_NOTE=4,
    PT_SHLIB=5,
    PT_PHDR=6,
    PT_TLS=7,
    PT_GNU_EH_FRAME=1685382480,
    PT_GNU_STACK=1685382481,
    PT_GNU_RELRO=1685382482
} Elf_ProgramHeaderType;

struct Elf64_Phdr {
    enum Elf_ProgramHeaderType p_type;
    dword p_flags;
    qword p_offset;
    qword p_vaddr;
    qword p_paddr;
    qword p_filesz;
    qword p_memsz;
    qword p_align;
};

typedef struct Elf64_Shdr Elf64_Shdr, *PElf64_Shdr;

typedef enum Elf_SectionHeaderType {
    SHT_NULL=0,
    SHT_PROGBITS=1,
    SHT_SYMTAB=2,
    SHT_STRTAB=3,
    SHT_RELA=4,
    SHT_HASH=5,
    SHT_DYNAMIC=6,
    SHT_NOTE=7,
    SHT_NOBITS=8,
    SHT_REL=9,
    SHT_SHLIB=10,
    SHT_DYNSYM=11,
    SHT_INIT_ARRAY=14,
    SHT_FINI_ARRAY=15,
    SHT_PREINIT_ARRAY=16,
    SHT_GROUP=17,
    SHT_SYMTAB_SHNDX=18,
    SHT_ANDROID_REL=1610612737,
    SHT_ANDROID_RELA=1610612738,
    SHT_GNU_ATTRIBUTES=1879048181,
    SHT_GNU_HASH=1879048182,
    SHT_GNU_LIBLIST=1879048183,
    SHT_CHECKSUM=1879048184,
    SHT_SUNW_move=1879048186,
    SHT_SUNW_COMDAT=1879048187,
    SHT_SUNW_syminfo=1879048188,
    SHT_GNU_verdef=1879048189,
    SHT_GNU_verneed=1879048190,
    SHT_GNU_versym=1879048191
} Elf_SectionHeaderType;

struct Elf64_Shdr {
    dword sh_name;
    enum Elf_SectionHeaderType sh_type;
    qword sh_flags;
    qword sh_addr;
    qword sh_offset;
    qword sh_size;
    dword sh_link;
    dword sh_info;
    qword sh_addralign;
    qword sh_entsize;
};

typedef struct Elf64_Dyn Elf64_Dyn, *PElf64_Dyn;

typedef enum Elf64_DynTag {
    DT_NULL=0,
    DT_NEEDED=1,
    DT_PLTRELSZ=2,
    DT_PLTGOT=3,
    DT_HASH=4,
    DT_STRTAB=5,
    DT_SYMTAB=6,
    DT_RELA=7,
    DT_RELASZ=8,
    DT_RELAENT=9,
    DT_STRSZ=10,
    DT_SYMENT=11,
    DT_INIT=12,
    DT_FINI=13,
    DT_SONAME=14,
    DT_RPATH=15,
    DT_SYMBOLIC=16,
    DT_REL=17,
    DT_RELSZ=18,
    DT_RELENT=19,
    DT_PLTREL=20,
    DT_DEBUG=21,
    DT_TEXTREL=22,
    DT_JMPREL=23,
    DT_BIND_NOW=24,
    DT_INIT_ARRAY=25,
    DT_FINI_ARRAY=26,
    DT_INIT_ARRAYSZ=27,
    DT_FINI_ARRAYSZ=28,
    DT_RUNPATH=29,
    DT_FLAGS=30,
    DT_PREINIT_ARRAY=32,
    DT_PREINIT_ARRAYSZ=33,
    DT_RELRSZ=35,
    DT_RELR=36,
    DT_RELRENT=37,
    DT_ANDROID_REL=1610612751,
    DT_ANDROID_RELSZ=1610612752,
    DT_ANDROID_RELA=1610612753,
    DT_ANDROID_RELASZ=1610612754,
    DT_ANDROID_RELR=1879040000,
    DT_ANDROID_RELRSZ=1879040001,
    DT_ANDROID_RELRENT=1879040003,
    DT_GNU_PRELINKED=1879047669,
    DT_GNU_CONFLICTSZ=1879047670,
    DT_GNU_LIBLISTSZ=1879047671,
    DT_CHECKSUM=1879047672,
    DT_PLTPADSZ=1879047673,
    DT_MOVEENT=1879047674,
    DT_MOVESZ=1879047675,
    DT_FEATURE_1=1879047676,
    DT_POSFLAG_1=1879047677,
    DT_SYMINSZ=1879047678,
    DT_SYMINENT=1879047679,
    DT_GNU_HASH=1879047925,
    DT_TLSDESC_PLT=1879047926,
    DT_TLSDESC_GOT=1879047927,
    DT_GNU_CONFLICT=1879047928,
    DT_GNU_LIBLIST=1879047929,
    DT_CONFIG=1879047930,
    DT_DEPAUDIT=1879047931,
    DT_AUDIT=1879047932,
    DT_PLTPAD=1879047933,
    DT_MOVETAB=1879047934,
    DT_SYMINFO=1879047935,
    DT_VERSYM=1879048176,
    DT_RELACOUNT=1879048185,
    DT_RELCOUNT=1879048186,
    DT_FLAGS_1=1879048187,
    DT_VERDEF=1879048188,
    DT_VERDEFNUM=1879048189,
    DT_VERNEED=1879048190,
    DT_VERNEEDNUM=1879048191,
    DT_AUXILIARY=2147483645,
    DT_FILTER=2147483647
} Elf64_DynTag;

struct Elf64_Dyn {
    enum Elf64_DynTag d_tag;
    qword d_val;
};

typedef struct Elf64_Rela Elf64_Rela, *PElf64_Rela;

struct Elf64_Rela {
    qword r_offset; // location to apply the relocation action
    qword r_info; // the symbol table index and the type of relocation
    qword r_addend; // a constant addend used to compute the relocatable field value
};

typedef struct Gnu_BuildId Gnu_BuildId, *PGnu_BuildId;

struct Gnu_BuildId {
    dword namesz; // Length of name field
    dword descsz; // Length of description field
    dword type; // Vendor specific type
    char name[4]; // Build-id vendor name
    byte description[20]; // Build-id value
};

typedef struct Elf64_Ehdr Elf64_Ehdr, *PElf64_Ehdr;

struct Elf64_Ehdr {
    byte e_ident_magic_num;
    char e_ident_magic_str[3];
    byte e_ident_class;
    byte e_ident_data;
    byte e_ident_version;
    byte e_ident_osabi;
    byte e_ident_abiversion;
    byte e_ident_pad[7];
    word e_type;
    word e_machine;
    dword e_version;
    qword e_entry;
    qword e_phoff;
    qword e_shoff;
    dword e_flags;
    word e_ehsize;
    word e_phentsize;
    word e_phnum;
    word e_shentsize;
    word e_shnum;
    word e_shstrndx;
};

typedef struct Elf64_Sym Elf64_Sym, *PElf64_Sym;

struct Elf64_Sym {
    dword st_name;
    byte st_info;
    byte st_other;
    word st_shndx;
    qword st_value;
    qword st_size;
};




int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = __gmon_start__();
  return iVar1;
}



void FUN_00400690(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)(undefined *)0x0)();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void free(void *__ptr)

{
  free(__ptr);
  return;
}



void __isoc99_fscanf(void)

{
  __isoc99_fscanf();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = puts(__s);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int fclose(FILE *__stream)

{
  int iVar1;
  
  iVar1 = fclose(__stream);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = printf(__format);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int gettimeofday(timeval *__tv,__timezone_ptr_t __tz)

{
  int iVar1;
  
  iVar1 = gettimeofday(__tv,__tz);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int fgetc(FILE *__stream)

{
  int iVar1;
  
  iVar1 = fgetc(__stream);
  return iVar1;
}



void __libc_start_main(void)

{
  __libc_start_main();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int fprintf(FILE *__stream,char *__format,...)

{
  int iVar1;
  
  iVar1 = fprintf(__stream,__format);
  return iVar1;
}



void __gmon_start__(void)

{
  __gmon_start__();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void * malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = malloc(__size);
  return pvVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

FILE * fopen(char *__filename,char *__modes)

{
  FILE *pFVar1;
  
  pFVar1 = fopen(__filename,__modes);
  return pFVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int sprintf(char *__s,char *__format,...)

{
  int iVar1;
  
  iVar1 = sprintf(__s,__format);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  size_t sVar1;
  
  sVar1 = fwrite(__ptr,__size,__n,__s);
  return sVar1;
}



void _start(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 in_stack_00000000;
  undefined auStack8 [8];
  
  __libc_start_main(main,in_stack_00000000,&stack0x00000008,__libc_csu_init,__libc_csu_fini,param_3,
                    auStack8);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



// WARNING: Removing unreachable block (ram,0x004007c7)
// WARNING: Removing unreachable block (ram,0x004007d1)

void deregister_tm_clones(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x00400804)
// WARNING: Removing unreachable block (ram,0x0040080e)

void register_tm_clones(void)

{
  return;
}



void __do_global_dtors_aux(void)

{
  if (completed_6355 == '\0') {
    deregister_tm_clones();
    completed_6355 = '\x01';
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00400854)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void frame_dummy(void)

{
  register_tm_clones();
  return;
}



int main(int argc,char **argv)

{
  _Bool _Var1;
  CmdLineData cmdLineData;
  char errorMessage [128];
  OpCodeType *metaDataPtr;
  ConfigDataType *configDataPtr;
  _Bool configUploadSuccess;
  
  configDataPtr = (ConfigDataType *)0x0;
  metaDataPtr = (OpCodeType *)0x0;
  configUploadSuccess = false;
  puts("\nSimulator Program");
  puts("=================\n");
  _Var1 = processCmdLine(argc,argv,&cmdLineData);
  if (_Var1 == false) {
    showCommandLineFormat();
  }
  else {
    _Var1 = getConfigData(cmdLineData.fileName,&configDataPtr,errorMessage);
    if (_Var1 == false) {
      printf("\nConfig Upload Error: %s, program aborted\n\n",errorMessage);
    }
    else {
      if (cmdLineData.configDisplayFlag != false) {
        displayConfigData(configDataPtr);
      }
      configUploadSuccess = true;
    }
    if ((configUploadSuccess != false) &&
       ((cmdLineData.mdDisplayFlag != false || (cmdLineData.runSimFlag != false)))) {
      _Var1 = getMetaData(configDataPtr->metaDataFileName,&metaDataPtr,errorMessage);
      if (_Var1 == false) {
        printf("\nMetadata Upload Error: %s, program aborted\n",errorMessage);
      }
      else {
        if (cmdLineData.mdDisplayFlag != false) {
          displayMetaData(metaDataPtr);
        }
        if (cmdLineData.runSimFlag != false) {
          runSim(configDataPtr,metaDataPtr);
        }
      }
    }
    configDataPtr = clearConfigData(configDataPtr);
    metaDataPtr = clearMetaDataList(metaDataPtr);
  }
  puts("\nSimulator Program End.\n");
  return 0;
}



void clearCmdLineStruct(CmdLineData *clDataPtr)

{
  clDataPtr->programRunFlag = false;
  clDataPtr->configDisplayFlag = false;
  clDataPtr->mdDisplayFlag = false;
  clDataPtr->runSimFlag = false;
  clDataPtr->fileName[0] = '\0';
  return;
}



_Bool processCmdLine(int numArgs,char **strVector,CmdLineData *clDataPtr)

{
  bool bVar1;
  bool bVar2;
  _Bool _Var3;
  int iVar4;
  int iVar5;
  int fileStrSubLoc;
  int fileStrLen;
  int argIndex;
  _Bool correctConfigFileFlag;
  _Bool atLeastOneSwitchFlag;
  
  clearCmdLineStruct(clDataPtr);
  bVar1 = false;
  bVar2 = false;
  argIndex = 1;
  if (2 < numArgs) {
    for (; argIndex < numArgs; argIndex = argIndex + 1) {
      iVar4 = compareString(strVector[argIndex],"-dc");
      if (iVar4 == 0) {
        clDataPtr->configDisplayFlag = true;
        bVar1 = true;
      }
      else {
        iVar4 = compareString(strVector[argIndex],"-dm");
        if (iVar4 == 0) {
          clDataPtr->mdDisplayFlag = true;
          bVar1 = true;
        }
        else {
          iVar4 = compareString(strVector[argIndex],"-rs");
          if (iVar4 == 0) {
            clDataPtr->runSimFlag = true;
            bVar1 = true;
          }
          else {
            iVar4 = getStringLength(strVector[(long)numArgs + -1]);
            iVar5 = findSubString(strVector[(long)numArgs + -1],".cnf");
            if ((iVar5 == -1) || (iVar4 + -4 != iVar5)) {
              clearCmdLineStruct(clDataPtr);
            }
            else {
              copyString(clDataPtr->fileName,strVector[(long)numArgs + -1]);
              bVar2 = true;
            }
          }
        }
      }
    }
  }
  if ((bVar1) && (bVar2)) {
    _Var3 = true;
  }
  else {
    _Var3 = false;
  }
  return _Var3;
}



void showCommandLineFormat(void)

{
  puts("Command Line Format:");
  puts("     sim_0x [-dc] [-dm] [-rs] <config file name>");
  puts("     -dc [optional] displays configuration data");
  puts("     -dm [optional] displays meta data");
  puts("     -rs [optional] runs simulator");
  puts("     required config file name");
  return;
}



OpCodeType * addInterruptOpCode(OpCodeType *localPtr,OpCodeType *newNode)

{
  OpCodeType *pOVar1;
  OpCodeType *addedNode;
  
  if (localPtr == (OpCodeType *)0x0) {
    localPtr = (OpCodeType *)malloc(0x38);
    copyOpCode(localPtr,newNode);
    localPtr->nextNode = (OpCodeType *)0x0;
  }
  else {
    pOVar1 = addInterruptOpCode(localPtr->nextNode,newNode);
    localPtr->nextNode = pOVar1;
  }
  return localPtr;
}



ReportNode * addSimNode(ReportNode *localNode,char *textString)

{
  ReportNode *pRVar1;
  ReportNode *newNode;
  
  if (localNode == (ReportNode *)0x0) {
    localNode = (ReportNode *)malloc(0x68);
    copyString((char *)localNode,textString);
    localNode->nextNode = (ReportNode *)0x0;
  }
  else {
    pRVar1 = addSimNode(localNode->nextNode,textString);
    localNode->nextNode = pRVar1;
  }
  return localNode;
}



PcbNodeType * clearAllPcbNodes(PcbNodeType *wkgPcbPtr)

{
  if (wkgPcbPtr != (PcbNodeType *)0x0) {
    clearAllPcbNodes(wkgPcbPtr->nextNode);
    free(wkgPcbPtr);
  }
  return (PcbNodeType *)0x0;
}



void diagDisplayPcbList(PcbNodeType *listHead)

{
  PcbNodeType *wkgPtr;
  
  wkgPtr = listHead;
  if (listHead == (PcbNodeType *)0x0) {
    puts("\nEmpty PCB List");
  }
  else {
    for (; wkgPtr != (PcbNodeType *)0x0; wkgPtr = wkgPtr->nextNode) {
      printf("PCB pid: %d, state: %d, time remaining: %d,\n",(ulong)(uint)wkgPtr->pid,
             (ulong)(uint)wkgPtr->state,(ulong)(uint)wkgPtr->timeRemaining);
      printf("\tcurrent command: %s, ",wkgPtr->opCodeList->command);
      printf("\tcurrent op code: %s, \n");
      printf("\tfirst int arg: %d, second int arg: %d\n\n",(ulong)(uint)wkgPtr->opCodeList->intArg2,
             (ulong)(uint)wkgPtr->opCodeList->intArg3);
    }
  }
  return;
}



OpCodeType * getNextOpCode(PcbNodeType *pcbListPtr,int pcbIdNum)

{
  PcbNodeType *pPVar1;
  PcbNodeType *pcbPtr;
  
  pPVar1 = getPcbById(pcbListPtr,pcbIdNum);
  if (pPVar1->currentOpCode == (OpCodeType *)0x0) {
    pPVar1->currentOpCode = pPVar1->opCodeList;
  }
  else if (pPVar1->currentOpCode->intArg2 == 0) {
    pPVar1->currentOpCode = pPVar1->currentOpCode->nextNode;
  }
  return pPVar1->currentOpCode;
}



int getNextProcess(ConfigDataType *config,PcbNodeType *pcbListPtr)

{
  int iVar1;
  PcbNodeType *pPVar2;
  int maxIterations;
  int origPcbId;
  int newBlockedCount;
  int loopCount;
  int minId;
  int minTime;
  PcbNodeType *wkgPtr;
  
  iVar1 = getNextProcess::pcbId;
  minTime = 0;
  minId = -1;
  loopCount = 0;
  newBlockedCount = 0;
  wkgPtr = pcbListPtr;
  if ((config->cpuSchedCode == 2) || (config->cpuSchedCode == 4)) {
    for (; wkgPtr != (PcbNodeType *)0x0; wkgPtr = wkgPtr->nextNode) {
      if (wkgPtr->state == 1) {
        return wkgPtr->pid;
      }
      if ((wkgPtr->state == 3) || (wkgPtr->state == 0)) {
        newBlockedCount = newBlockedCount + 1;
      }
    }
  }
  else if (config->cpuSchedCode == 3) {
    pPVar2 = getPcbById(pcbListPtr,getNextProcess::pcbId);
    if (((pPVar2->state != 3) && (pPVar2->state != 4)) && (pPVar2->quantumTimeOut != true)) {
      pPVar2->quantumTimeOut = false;
      return pPVar2->pid;
    }
    pPVar2->quantumTimeOut = false;
    if (pPVar2->nextNode != (PcbNodeType *)0x0) {
      wkgPtr = pPVar2->nextNode;
    }
    getNextProcess::pcbId = wkgPtr->pid;
    while (loopCount < 2) {
      pPVar2 = getPcbById(pcbListPtr,getNextProcess::pcbId);
      if (pPVar2->state == 1) {
        return pPVar2->pid;
      }
      if ((pPVar2->state == 3) || (pPVar2->state == 0)) {
        newBlockedCount = newBlockedCount + 1;
      }
      if (pPVar2->nextNode == (PcbNodeType *)0x0) {
        loopCount = loopCount + 1;
        wkgPtr = pcbListPtr;
      }
      else {
        wkgPtr = pPVar2->nextNode;
      }
      getNextProcess::pcbId = wkgPtr->pid;
    }
  }
  else {
    for (; (wkgPtr != (PcbNodeType *)0x0 && (wkgPtr->state != 1)); wkgPtr = wkgPtr->nextNode) {
      if ((wkgPtr->state == 0) || (wkgPtr->state == 3)) {
        newBlockedCount = newBlockedCount + 1;
      }
    }
    if (wkgPtr != (PcbNodeType *)0x0) {
      minId = wkgPtr->pid;
      minTime = wkgPtr->timeRemaining;
      wkgPtr = wkgPtr->nextNode;
    }
    for (; wkgPtr != (PcbNodeType *)0x0; wkgPtr = wkgPtr->nextNode) {
      if ((wkgPtr->state == 1) && (wkgPtr->timeRemaining < minTime)) {
        minId = wkgPtr->pid;
        minTime = wkgPtr->timeRemaining;
      }
      else if ((wkgPtr->state == 3) || (wkgPtr->state == 0)) {
        newBlockedCount = newBlockedCount + 1;
      }
    }
  }
  if (minId < 0) {
    if (newBlockedCount < 1) {
      minId = -0x25e;
    }
    else {
      minId = -0x1f9;
    }
  }
  getNextProcess::pcbId = iVar1;
  return minId;
}



PcbNodeType * getPcbById(PcbNodeType *pcbListPtr,int pcbIdNum)

{
  PcbNodeType *wkgPtr;
  
  wkgPtr = pcbListPtr;
  while( true ) {
    if (wkgPtr == (PcbNodeType *)0x0) {
      return (PcbNodeType *)0x0;
    }
    if (wkgPtr->pid == pcbIdNum) break;
    wkgPtr = wkgPtr->nextNode;
  }
  return wkgPtr;
}



PcbNodeType * insertPcbNode(PcbNodeType *pcbListPtr,PcbNodeType *newNode)

{
  PcbNodeType *local_20;
  PcbNodeType *wkgPtr;
  
  if ((pcbListPtr == (PcbNodeType *)0x0) ||
     (wkgPtr = pcbListPtr, newNode->opCodeList->intArg2 < pcbListPtr->opCodeList->intArg2)) {
    newNode->nextNode = pcbListPtr;
    local_20 = newNode;
  }
  else {
    while ((wkgPtr->nextNode != (PcbNodeType *)0x0 &&
           (wkgPtr->nextNode->opCodeList->intArg2 <= newNode->opCodeList->intArg2))) {
      wkgPtr = wkgPtr->nextNode;
    }
    newNode->nextNode = wkgPtr->nextNode;
    wkgPtr->nextNode = newNode;
    local_20 = pcbListPtr;
  }
  return local_20;
}



_Bool processIntRequest(InterruptMgrCode ctrlCode,OpCodeType *wkgOpCode,PcbNodeType *pcbListPtr)

{
  PcbNodeType *pPVar1;
  double dVar2;
  char reportString [128];
  double currentTime;
  PcbNodeType *localPcbPtr;
  _Bool returnVal;
  OpCodeType *rmvdOpCode;
  OpCodeType *wkgOpListPtr;
  
  rmvdOpCode = (OpCodeType *)0x0;
  returnVal = false;
  if (ctrlCode == INITIALIZE_INTERRUPT_MGR) {
    processIntRequest::intOpListHeadPtr = (OpCodeType *)0x0;
    returnVal = true;
  }
  else if (ctrlCode == CHECK_FOR_INTERRUPT) {
    wkgOpListPtr = processIntRequest::intOpListHeadPtr;
    while (wkgOpListPtr != (OpCodeType *)0x0) {
      pPVar1 = getPcbById(pcbListPtr,wkgOpListPtr->pid);
      dVar2 = accessTimer(1,reportString);
      if (wkgOpListPtr->opEndTime < dVar2) {
        if (pPVar1->state != 4) {
          return true;
        }
        rmvdOpCode = wkgOpListPtr;
      }
      if (rmvdOpCode == (OpCodeType *)0x0) {
        wkgOpListPtr = wkgOpListPtr->nextNode;
      }
      else {
        processIntRequest::intOpListHeadPtr =
             removeOpCodeNode(processIntRequest::intOpListHeadPtr,rmvdOpCode);
        rmvdOpCode = (OpCodeType *)0x0;
        wkgOpListPtr = processIntRequest::intOpListHeadPtr;
      }
    }
  }
  else if (ctrlCode == SET_IO_START) {
    dVar2 = accessTimer(1,reportString);
    wkgOpCode->opEndTime = (double)wkgOpCode->intArg2 / 1000.0 + dVar2;
    processIntRequest::intOpListHeadPtr =
         addInterruptOpCode(processIntRequest::intOpListHeadPtr,wkgOpCode);
  }
  else if (ctrlCode == RESOLVE_ALL_INTERRUPTS) {
    wkgOpListPtr = processIntRequest::intOpListHeadPtr;
    while (wkgOpListPtr != (OpCodeType *)0x0) {
      pPVar1 = getPcbById(pcbListPtr,wkgOpListPtr->pid);
      dVar2 = accessTimer(1,reportString);
      if (wkgOpListPtr->opEndTime < dVar2) {
        if (pPVar1->state != 4) {
          sprintf(reportString,"OS: Interrupted by process %d, %s %sput operation",
                  (ulong)(uint)wkgOpListPtr->pid,wkgOpListPtr->strArg1,wkgOpListPtr->inOutArg);
          runSimReport(1,(ConfigDataType *)0x0,reportString);
          pPVar1->state = 1;
          sprintf(reportString,"OS: Process %d set from BLOCKED to READY",
                  (ulong)(uint)wkgOpListPtr->pid);
          runSimReport(1,(ConfigDataType *)0x0,reportString);
        }
        rmvdOpCode = wkgOpListPtr;
      }
      if (rmvdOpCode == (OpCodeType *)0x0) {
        wkgOpListPtr = wkgOpListPtr->nextNode;
      }
      else {
        processIntRequest::intOpListHeadPtr =
             removeOpCodeNode(processIntRequest::intOpListHeadPtr,rmvdOpCode);
        rmvdOpCode = (OpCodeType *)0x0;
        wkgOpListPtr = processIntRequest::intOpListHeadPtr;
      }
    }
    returnVal = true;
  }
  return returnVal;
}



OpCodeType * removeOpCodeNode(OpCodeType *headPtr,OpCodeType *removedPtr)

{
  OpCodeType *wkgPtr;
  
  wkgPtr = headPtr;
  if (removedPtr == headPtr) {
    headPtr = headPtr->nextNode;
  }
  else {
    for (; wkgPtr->nextNode != removedPtr; wkgPtr = wkgPtr->nextNode) {
    }
    wkgPtr->nextNode = wkgPtr->nextNode->nextNode;
    free(removedPtr);
  }
  return headPtr;
}



ReportNode * removeReportNodes(ReportNode *localNode)

{
  if (localNode != (ReportNode *)0x0) {
    if (localNode->nextNode != (ReportNode *)0x0) {
      removeReportNodes(localNode->nextNode);
    }
    free(localNode);
  }
  return (ReportNode *)0x0;
}



void runSim(ConfigDataType *configPtr,OpCodeType *metaDataMstrPtr)

{
  int iVar1;
  bool bVar2;
  _Bool _Var3;
  uint pcbIdNum;
  int iVar4;
  PcbNodeType *pcbListPtr_00;
  char reportString [128];
  PcbNodeType *pcbListPtr;
  int currentPid;
  _Bool isPreemptive;
  int lastPid;
  _Bool runFlag;
  OpCodeType *wkgOpCode;
  PcbNodeType *pcbWkgPtr;
  
  wkgOpCode = (OpCodeType *)0x0;
  bVar2 = true;
  lastPid = -1;
  showSimStart(configPtr);
  pcbListPtr_00 = setAllPCB(configPtr,metaDataMstrPtr);
  iVar1 = metaDataMstrPtr->nextNode->intArg3;
  processIntRequest(INITIALIZE_INTERRUPT_MGR,(OpCodeType *)0x0,pcbListPtr_00);
  setNewToReady(configPtr,pcbListPtr_00);
  processMemRequest(configPtr,metaDataMstrPtr);
  do {
    pcbIdNum = getNextProcess(configPtr,pcbListPtr_00);
    if (pcbIdNum == 0xfffffda2) {
      runSimReport(1,configPtr,"OS: System stop");
      bVar2 = false;
    }
    else if (pcbIdNum == 0xfffffe07) {
      runCpuIdle(configPtr,pcbListPtr_00);
    }
    else {
      setNewToReady(configPtr,pcbListPtr_00);
      wkgOpCode = getNextOpCode(pcbListPtr_00,pcbIdNum);
      iVar4 = compareString(wkgOpCode->command,"app");
      if ((((iVar4 != 0) || (iVar4 = compareString(wkgOpCode->strArg1,"start"), iVar4 != 0)) &&
          (iVar1 == 9)) && (pcbIdNum != lastPid)) {
        pcbWkgPtr = getPcbById(pcbListPtr_00,pcbIdNum);
        sprintf(reportString,"OS: Process %d selected with %d ms remaining",(ulong)pcbIdNum,
                (ulong)(uint)pcbWkgPtr->timeRemaining);
        runSimReport(1,configPtr,reportString);
        sprintf(reportString,"OS: Process %d set from READY to RUNNING",(ulong)pcbIdNum);
        runSimReport(1,configPtr,reportString);
      }
      iVar4 = compareString(wkgOpCode->command,"app");
      if ((iVar4 == 0) && (iVar4 = compareString(wkgOpCode->strArg1,"start"), iVar4 == 0)) {
        pcbWkgPtr = getPcbById(pcbListPtr_00,pcbIdNum);
        sprintf(reportString,"OS: Process %d selected with %d ms remaining",(ulong)pcbIdNum,
                (ulong)(uint)pcbWkgPtr->timeRemaining);
        runSimReport(1,configPtr,reportString);
        sprintf(reportString,"OS: Process %d set from READY to RUNNING",(ulong)pcbIdNum);
        runSimReport(1,configPtr,reportString);
        wkgOpCode->intArg2 = 0;
      }
      else {
        iVar4 = compareString(wkgOpCode->command,"app");
        if ((iVar4 == 0) && (iVar4 = compareString(wkgOpCode->strArg1,"end"), iVar4 == 0)) {
          sprintf(reportString,"OS: Process %d ended",(ulong)pcbIdNum);
          runSimReport(1,configPtr,reportString);
          wkgOpCode->pid = pcbIdNum;
          copyString(reportString,"clearOne");
          copyString(wkgOpCode->strArg1,reportString);
          processMemRequest(configPtr,wkgOpCode);
          pcbWkgPtr = getPcbById(pcbListPtr_00,pcbIdNum);
          pcbWkgPtr->state = 4;
          sprintf(reportString,"OS: Process %d set to EXIT",(ulong)pcbIdNum);
          runSimReport(1,configPtr,reportString);
        }
        else {
          iVar4 = compareString(wkgOpCode->command,"mem");
          if (iVar4 == 0) {
            sprintf(reportString,"Process: %d, mem %s request (%d, %d)",(ulong)(uint)wkgOpCode->pid,
                    wkgOpCode->strArg1,(ulong)(uint)wkgOpCode->intArg2,
                    (ulong)(uint)wkgOpCode->intArg3);
            runSimReport(1,configPtr,reportString);
            _Var3 = processMemRequest(configPtr,wkgOpCode);
            if (_Var3 == false) {
              sprintf(reportString,"Process: %d, failed mem %s request",(ulong)(uint)wkgOpCode->pid,
                      wkgOpCode->strArg1);
              runSimReport(1,configPtr,reportString);
              sprintf(reportString,"OS: Segmentation fault, Process %d ended",
                      (ulong)(uint)wkgOpCode->pid);
              runSimReport(1,configPtr,reportString);
              copyString(wkgOpCode->strArg1,"clearOne");
              processMemRequest(configPtr,wkgOpCode);
              pcbWkgPtr->state = 4;
              sprintf(reportString,"OS: Process %d set to EXIT",(ulong)pcbIdNum);
              runSimReport(1,configPtr,reportString);
            }
            else {
              sprintf(reportString,"Process: %d, successful mem %s request",
                      (ulong)(uint)wkgOpCode->pid,wkgOpCode->strArg1);
              runSimReport(1,configPtr,reportString);
              wkgOpCode->intArg2 = 0;
            }
          }
          else {
            iVar4 = compareString(wkgOpCode->command,"dev");
            if (iVar4 == 0) {
              sprintf(reportString,"Process: %d, %s %sput operation start",
                      (ulong)(uint)wkgOpCode->pid,wkgOpCode->strArg1,wkgOpCode->inOutArg);
              runSimReport(1,configPtr,reportString);
              wkgOpCode->intArg2 = wkgOpCode->intArg2 * configPtr->ioCycleRate;
              processIoOp(wkgOpCode,pcbListPtr_00);
              pcbWkgPtr = getPcbById(pcbListPtr_00,pcbIdNum);
              pcbWkgPtr->timeRemaining = pcbWkgPtr->timeRemaining - wkgOpCode->intArg2;
              wkgOpCode->intArg2 = 0;
            }
            else {
              iVar4 = compareString(wkgOpCode->command,"cpu");
              if (iVar4 == 0) {
                sprintf(reportString,"Process: %d, %s %s operation start",
                        (ulong)(uint)wkgOpCode->pid,wkgOpCode->command,wkgOpCode->strArg1);
                runSimReport(1,configPtr,reportString);
                processRunOp(configPtr,wkgOpCode,pcbListPtr_00);
              }
            }
          }
        }
      }
    }
    processIntRequest(RESOLVE_ALL_INTERRUPTS,wkgOpCode,pcbListPtr_00);
    lastPid = pcbIdNum;
  } while (bVar2);
  clearAllPcbNodes(pcbListPtr_00);
  copyString(wkgOpCode->strArg1,"clearAll");
  processMemRequest(configPtr,wkgOpCode);
  runSimReport(1,configPtr,"OS: Simulation end");
  runSimReport(2,configPtr,reportString);
  accessTimer(2,reportString);
  return;
}



void runSimReport(int reportControl,ConfigDataType *configPtr,char *textString)

{
  int iVar1;
  FILE *__s;
  int local_cc;
  char outputString [128];
  char timeString [32];
  char WRITE_FLAG [2];
  FILE *outFilePtr;
  ReportNode *workingNode;
  
  WRITE_FLAG = 0x77;
  getSubString(outputString,textString,0,2);
  if (runSimReport::OS_Toggle != false) {
    iVar1 = compareString(outputString,"OS:");
    if (iVar1 != 0) {
      copyString(outputString,"\n ");
      runSimReport::OS_Toggle = false;
      goto LAB_00401ebc;
    }
  }
  if (runSimReport::OS_Toggle != true) {
    iVar1 = compareString(outputString,"OS:");
    if (iVar1 == 0) {
      copyString(outputString,"\n ");
      runSimReport::OS_Toggle = true;
      goto LAB_00401ebc;
    }
  }
  copyString(outputString," ");
LAB_00401ebc:
  if (reportControl == 0) {
    runSimReport::localNode = (ReportNode *)0x0;
    runSimReport::config = (ConfigDataType *)malloc(0xe8);
    copyConfigData(runSimReport::config,configPtr);
    accessTimer(1,timeString);
    local_cc = 1;
    if (runSimReport::config->logToCode == 6) {
      puts("Simulator running with output to file\n");
    }
  }
  else {
    accessTimer(1,timeString);
    local_cc = reportControl;
  }
  if (local_cc == 1) {
    concatenateString(outputString,timeString);
    concatenateString(outputString,", ");
    concatenateString(outputString,textString);
    if ((runSimReport::config->logToCode == 7) || (runSimReport::config->logToCode == 6)) {
      runSimReport::localNode = addSimNode(runSimReport::localNode,outputString);
    }
    if ((runSimReport::config->logToCode == 7) || (runSimReport::config->logToCode == 5)) {
      puts(outputString);
    }
  }
  else {
    workingNode = runSimReport::localNode;
    __s = fopen(runSimReport::config->logToFileName,WRITE_FLAG);
    fwrite("\n==================================================\n",1,0x34,__s);
    fwrite("Simulator Log File Header\n\n",1,0x1b,__s);
    fprintf(__s,"File Name                       : %s\n",runSimReport::config->metaDataFileName);
    configCodeToString(runSimReport::config->cpuSchedCode,outputString);
    fprintf(__s,"CPU Scheduling                  : %s\n",outputString);
    fprintf(__s,"Quantum Cycles                  : %d\n",
            (ulong)(uint)runSimReport::config->quantumCycles);
    fprintf(__s,"Memory Available (KB)           : %d\n",
            (ulong)(uint)runSimReport::config->memAvailable);
    fprintf(__s,"Processor Cycle Rate (ms/cycle) : %d\n",
            (ulong)(uint)runSimReport::config->procCycleRate);
    fprintf(__s,"I/O Cycle Rate (ms/cycle)       : %d\n\n",
            (ulong)(uint)runSimReport::config->ioCycleRate);
    fwrite("================\n",1,0x11,__s);
    fwrite("Begin Simulation\n\n",1,0x12,__s);
    for (; workingNode != (ReportNode *)0x0; workingNode = workingNode->nextNode) {
      fprintf(__s,"%s\n",workingNode);
    }
    fwrite("\nEnd Simulation - Complete\n",1,0x1b,__s);
    fwrite("=========================\n\n",1,0x1b,__s);
    fclose(__s);
    runSimReport::localNode = removeReportNodes(runSimReport::localNode);
    free(runSimReport::config);
  }
  return;
}



PcbNodeType * setAllPCB(ConfigDataType *configPtr,OpCodeType *metaDataMstrPtr)

{
  int iVar1;
  int iVar2;
  PcbNodeType *newNode;
  OpCodeType *local_48;
  PcbNodeType *newPcbNodePtr;
  int pidSet;
  PcbNodeType *pcbHeadPtr;
  
  pcbHeadPtr = (PcbNodeType *)0x0;
  pidSet = 0;
  iVar1 = compareString(metaDataMstrPtr->command,"sys");
  if ((iVar1 == 0) && (iVar1 = compareString(metaDataMstrPtr->strArg1,"start"), iVar1 == 0)) {
    local_48 = metaDataMstrPtr->nextNode;
    while ((iVar1 = compareString(local_48->command,"sys"), iVar1 != 0 &&
           (iVar1 = compareString(local_48->strArg1,"end"), iVar1 != 0))) {
      iVar1 = compareString(local_48->command,"app");
      if ((iVar1 == 0) && (iVar1 = compareString(local_48->strArg1,"start"), iVar1 == 0)) {
        newNode = (PcbNodeType *)malloc(0x40);
        newNode->pid = pidSet;
        newNode->state = 0;
        newNode->timeRemaining = 0;
        newNode->startTime = (double)local_48->intArg2;
        newNode->quantumTimeOut = false;
        newNode->currentOpCode = (OpCodeType *)0x0;
        newNode->opCodeList = local_48;
        newNode->memList = (MemNodeType *)0x0;
        newNode->nextNode = (PcbNodeType *)0x0;
        while ((iVar1 = compareString(local_48->command,"app"), iVar1 != 0 ||
               (iVar1 = compareString(local_48->strArg1,"end"), iVar1 != 0))) {
          iVar1 = compareString(local_48->command,"mem");
          if (iVar1 != 0) {
            iVar1 = newNode->timeRemaining;
            iVar2 = calcOpTime(configPtr,local_48);
            newNode->timeRemaining = iVar1 + iVar2;
            if ((configPtr->cpuSchedCode == 0) || (configPtr->cpuSchedCode == 4)) {
              local_48->intArg3 = 8;
            }
            else {
              local_48->intArg3 = 9;
            }
          }
          local_48->pid = pidSet;
          local_48 = local_48->nextNode;
        }
        pcbHeadPtr = insertPcbNode(pcbHeadPtr,newNode);
        pidSet = pidSet + 1;
      }
      local_48 = local_48->nextNode;
    }
  }
  else {
    pcbHeadPtr = (PcbNodeType *)0x0;
  }
  return pcbHeadPtr;
}



void setNewToReady(ConfigDataType *configPtr,PcbNodeType *pcbListPtr)

{
  double dVar1;
  char timeString [32];
  char reportString [128];
  double timeVal;
  PcbNodeType *wkgPtr;
  
  for (wkgPtr = pcbListPtr; wkgPtr != (PcbNodeType *)0x0; wkgPtr = wkgPtr->nextNode) {
    if (wkgPtr->state == 0) {
      dVar1 = accessTimer(1,timeString);
      if (wkgPtr->startTime <= dVar1) {
        wkgPtr->state = 1;
        sprintf(reportString,"OS: Process %d set to READY state from NEW state",
                (ulong)(uint)wkgPtr->pid);
        runSimReport(1,configPtr,reportString);
      }
    }
  }
  return;
}



void showSimStart(ConfigDataType *configPtr)

{
  puts("Simulator Run");
  puts("-------------\n");
  runSimReport(0,configPtr,"OS: Simulator start");
  return;
}



MemNodeType *
createNewMemNode(int physStart,int physEnd,int memState,int procNum,int logStart,int logStop)

{
  MemNodeType *pMVar1;
  MemNodeType *tempNode;
  
  pMVar1 = (MemNodeType *)malloc(0x20);
  pMVar1->physicalStart = physStart;
  pMVar1->physicalStop = physEnd;
  pMVar1->memBlockState = memState;
  pMVar1->processNumber = procNum;
  pMVar1->logicalStart = logStart;
  pMVar1->logicalStop = logStop;
  pMVar1->nextNode = (MemNodeType *)0x0;
  return pMVar1;
}



void defragMemory(MemNodeType *headPtr)

{
  MemNodeType *__ptr;
  MemNodeType *removePtr;
  MemNodeType *wkgPtr;
  
  wkgPtr = headPtr;
  while (wkgPtr != (MemNodeType *)0x0) {
    if (((wkgPtr->memBlockState == 1) && (wkgPtr->nextNode != (MemNodeType *)0x0)) &&
       (wkgPtr->nextNode->memBlockState == 1)) {
      reuseMemNode(wkgPtr,1,-1,wkgPtr->physicalStart,wkgPtr->nextNode->physicalStop,0,0);
      __ptr = wkgPtr->nextNode;
      wkgPtr->nextNode = __ptr->nextNode;
      free(__ptr);
    }
    else {
      wkgPtr = wkgPtr->nextNode;
    }
  }
  return;
}



void diagMemDump(MemNodeType *memPtr,char *dispStr,_Bool displayFlag)

{
  char dispString [32];
  MemNodeType *wkgMemPtr;
  
  if (displayFlag != false) {
    puts("--------------------------------------------------");
    puts(dispStr);
    wkgMemPtr = memPtr;
    if (memPtr == (MemNodeType *)0x0) {
      puts("No memory configured");
    }
    for (; wkgMemPtr != (MemNodeType *)0x0; wkgMemPtr = wkgMemPtr->nextNode) {
      if (wkgMemPtr->memBlockState == 1) {
        copyString(dispString,"Open");
      }
      else {
        copyString(dispString,"Used");
      }
      if (wkgMemPtr->processNumber == -1) {
        printf("%d [ %s, P#: x, ",(ulong)(uint)wkgMemPtr->physicalStart,dispString);
      }
      else {
        printf("%d [ %s, P#: %d, ",(ulong)(uint)wkgMemPtr->physicalStart,dispString,
               (ulong)(uint)wkgMemPtr->processNumber);
      }
      printf("%d-%d ] %d\n",(ulong)(uint)wkgMemPtr->logicalStart,(ulong)(uint)wkgMemPtr->logicalStop
             ,(ulong)(uint)wkgMemPtr->physicalStop);
    }
    puts("--------------------------------------------------");
  }
  return;
}



_Bool processMemRequest(ConfigDataType *configPtr,OpCodeType *opCodePtr)

{
  uint procNum;
  MemNodeType *pMVar1;
  _Bool _Var2;
  int iVar3;
  int iVar4;
  MemNodeType *pMVar5;
  char displayStr [64];
  MemNodeType *tempNodePtr;
  int highMemLoc;
  int lowMemLoc;
  int processId;
  int logicalHigh;
  int requestedMemory;
  _Bool displayFlag;
  int highestMemLoc;
  int lowestMemLoc;
  MemNodeType *wkgMemPtr;
  MemNodeType *trlgPtr;
  int logicalOffset;
  int logicalLow;
  
  _Var2 = configPtr->memDisplay;
  if (processMemRequest::memHeadPtr == (MemNodeType *)0x0) {
    processMemRequest::memHeadPtr = createNewMemNode(0,configPtr->memAvailable + -1,1,-1,0,0);
    copyString(displayStr,"After memory initialization");
    diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
    _Var2 = true;
  }
  else {
    iVar3 = compareString(opCodePtr->strArg1,"clearAll");
    if ((iVar3 == 0) || (iVar3 = compareString(opCodePtr->strArg1,"clearOne"), iVar3 == 0)) {
      logicalLow = 1;
      logicalOffset = 1;
    }
    else {
      logicalLow = opCodePtr->intArg2;
      logicalOffset = opCodePtr->intArg3;
    }
    iVar3 = logicalLow + logicalOffset + -1;
    procNum = opCodePtr->pid;
    iVar4 = compareString(opCodePtr->strArg1,"allocate");
    if (((iVar4 == 0) || (iVar4 = compareString(opCodePtr->strArg1,"access"), iVar4 == 0)) &&
       ((logicalLow < 0 ||
        (((logicalOffset < 1 || (configPtr->memAvailable <= logicalLow)) ||
         (configPtr->memAvailable <= iVar3)))))) {
      copyString(displayStr,"After limits out of range");
      diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
      _Var2 = false;
    }
    else {
      iVar4 = compareString(opCodePtr->strArg1,"allocate");
      if (iVar4 == 0) {
        for (wkgMemPtr = processMemRequest::memHeadPtr; wkgMemPtr != (MemNodeType *)0x0;
            wkgMemPtr = wkgMemPtr->nextNode) {
          if ((wkgMemPtr->processNumber == procNum) &&
             (((wkgMemPtr->logicalStart <= logicalLow && (logicalLow <= wkgMemPtr->logicalStop)) ||
              ((wkgMemPtr->logicalStart <= iVar3 && (iVar3 <= wkgMemPtr->logicalStop)))))) {
            copyString(displayStr,"After allocate overlap failure");
            diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
            return false;
          }
        }
        wkgMemPtr = processMemRequest::memHeadPtr;
        trlgPtr = processMemRequest::memHeadPtr;
        while ((wkgMemPtr != (MemNodeType *)0x0 &&
               ((wkgMemPtr->memBlockState == 2 ||
                ((wkgMemPtr->physicalStop - wkgMemPtr->physicalStart) + 1 < logicalOffset))))) {
          trlgPtr = wkgMemPtr;
          wkgMemPtr = wkgMemPtr->nextNode;
        }
        if (wkgMemPtr != (MemNodeType *)0x0) {
          if ((wkgMemPtr->physicalStop - wkgMemPtr->physicalStart) + 1 != logicalOffset) {
            iVar4 = logicalOffset + wkgMemPtr->physicalStart;
            pMVar5 = createNewMemNode(wkgMemPtr->physicalStart,iVar4 + -1,2,procNum,logicalLow,iVar3
                                     );
            pMVar1 = pMVar5;
            if (wkgMemPtr != processMemRequest::memHeadPtr) {
              trlgPtr->nextNode = pMVar5;
              pMVar1 = processMemRequest::memHeadPtr;
            }
            processMemRequest::memHeadPtr = pMVar1;
            wkgMemPtr->physicalStart = iVar4;
            pMVar5->nextNode = wkgMemPtr;
            copyString(displayStr,"After allocate success");
            diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
            return true;
          }
          reuseMemNode(wkgMemPtr,2,procNum,wkgMemPtr->physicalStart,wkgMemPtr->physicalStop,
                       logicalLow,iVar3);
        }
        copyString(displayStr,"After allocate failure");
        diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
      }
      else {
        iVar4 = compareString(opCodePtr->strArg1,"access");
        if (iVar4 != 0) {
          iVar3 = compareString(opCodePtr->strArg1,"clearOne");
          if (iVar3 == 0) {
            for (wkgMemPtr = processMemRequest::memHeadPtr; wkgMemPtr != (MemNodeType *)0x0;
                wkgMemPtr = wkgMemPtr->nextNode) {
              if (wkgMemPtr->processNumber == procNum) {
                reuseMemNode(wkgMemPtr,1,-1,wkgMemPtr->physicalStart,wkgMemPtr->physicalStop,0,0);
              }
            }
            defragMemory(processMemRequest::memHeadPtr);
            sprintf(displayStr,"After clear process %d success",(ulong)procNum);
            diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
            return true;
          }
          wkgMemPtr = processMemRequest::memHeadPtr;
          while (wkgMemPtr != (MemNodeType *)0x0) {
            pMVar1 = wkgMemPtr->nextNode;
            free(wkgMemPtr);
            wkgMemPtr = pMVar1;
          }
          processMemRequest::memHeadPtr = (MemNodeType *)0x0;
          copyString(displayStr,"After clear all process success");
          diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
          return true;
        }
        for (wkgMemPtr = processMemRequest::memHeadPtr; wkgMemPtr != (MemNodeType *)0x0;
            wkgMemPtr = wkgMemPtr->nextNode) {
          if (((wkgMemPtr->processNumber == procNum) && (wkgMemPtr->logicalStart <= logicalLow)) &&
             ((logicalLow <= wkgMemPtr->logicalStop &&
              ((wkgMemPtr->logicalStart <= iVar3 && (iVar3 <= wkgMemPtr->logicalStop)))))) {
            copyString(displayStr,"After access success");
            diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
            return true;
          }
        }
        copyString(displayStr,"After access failure");
        diagMemDump(processMemRequest::memHeadPtr,displayStr,_Var2);
      }
      _Var2 = false;
    }
  }
  return _Var2;
}



void reuseMemNode(MemNodeType *tempNode,int memState,int procNum,int phyStart,int phyStop,
                 int logStart,int logStop)

{
  tempNode->memBlockState = memState;
  tempNode->processNumber = procNum;
  tempNode->physicalStart = phyStart;
  tempNode->physicalStop = phyStop;
  tempNode->logicalStart = logStart;
  tempNode->logicalStop = logStop;
  return;
}



void processIoOp(OpCodeType *opCodePtr,PcbNodeType *pcbListPtr)

{
  PcbNodeType *pPVar1;
  char reportString [128];
  PcbNodeType *localPcbPtr;
  
  if (opCodePtr->intArg3 == 8) {
    runTimer(opCodePtr->intArg2);
    sprintf(reportString,"Process: %d, %s %sput operation end",(ulong)(uint)opCodePtr->pid,
            opCodePtr->strArg1,opCodePtr->inOutArg);
    runSimReport(1,(ConfigDataType *)0x0,reportString);
  }
  else {
    sprintf(reportString,"OS: Process %d blocked for %sput operation",(ulong)(uint)opCodePtr->pid,
            opCodePtr->inOutArg);
    runSimReport(1,(ConfigDataType *)0x0,reportString);
    pPVar1 = getPcbById(pcbListPtr,opCodePtr->pid);
    pPVar1->state = 3;
    sprintf(reportString,"OS: Process %d set from RUNNING to BLOCKED",(ulong)(uint)opCodePtr->pid);
    runSimReport(1,(ConfigDataType *)0x0,reportString);
    processIntRequest(SET_IO_START,opCodePtr,pcbListPtr);
  }
  return;
}



void processRunOp(ConfigDataType *configPtr,OpCodeType *opCodePtr,PcbNodeType *pcbListPtr)

{
  int milliSeconds;
  bool bVar1;
  PcbNodeType *pPVar2;
  bool bVar3;
  char reportString [128];
  PcbNodeType *pcbWkgPtr;
  int oneCycle;
  _Bool isPreemptive;
  _Bool interruptFound;
  _Bool continueRun;
  int cyclesToRun;
  int quantumCount;
  
  milliSeconds = configPtr->procCycleRate;
  quantumCount = configPtr->quantumCycles;
  cyclesToRun = opCodePtr->intArg2;
  bVar1 = true;
  interruptFound = false;
  bVar3 = opCodePtr->intArg3 == 9;
  pPVar2 = getPcbById(pcbListPtr,opCodePtr->pid);
  while (bVar1) {
    runTimer(milliSeconds);
    pPVar2->timeRemaining = pPVar2->timeRemaining - milliSeconds;
    cyclesToRun = cyclesToRun + -1;
    quantumCount = quantumCount + -1;
    interruptFound = processIntRequest(CHECK_FOR_INTERRUPT,opCodePtr,pcbListPtr);
    if ((cyclesToRun == 0) || (((bVar3 && (quantumCount == 0)) || (interruptFound != false)))) {
      bVar1 = false;
    }
  }
  if (((cyclesToRun < 1) || (!bVar3)) || (interruptFound == true)) {
    sprintf(reportString,"Process: %d, %s %s operation end",(ulong)(uint)opCodePtr->pid,
            opCodePtr->command,opCodePtr->strArg1);
    runSimReport(1,configPtr,reportString);
  }
  else {
    pPVar2->quantumTimeOut = true;
    sprintf(reportString,"OS: Process %d quantum time out, cpu process operation end",
            (ulong)(uint)opCodePtr->pid);
    runSimReport(1,configPtr,reportString);
  }
  opCodePtr->intArg2 = cyclesToRun;
  return;
}



// WARNING: Could not reconcile some variable overlaps

void runCpuIdle(ConfigDataType *configPtr,PcbNodeType *pcbListPtr)

{
  int milliSeconds;
  char reportString [128];
  OpCodeType *dummyPtr;
  int oneCycle;
  _Bool interruptFound;
  
  interruptFound = false;
  milliSeconds = configPtr->procCycleRate;
  reportString._0_8_ = 0x20555043203a534f;
  reportString._8_8_ = 0x6c61202c656c6469;
  reportString._16_8_ = 0x657669746361206c;
  reportString._24_8_ = 0x737365636f727020;
  reportString._32_8_ = 0x6b636f6c62207365;
  reportString._40_2_ = 0x6465;
  reportString[42] = '\0';
  runSimReport(1,configPtr,reportString);
  while (interruptFound != true) {
    runTimer(milliSeconds);
    interruptFound = processIntRequest(CHECK_FOR_INTERRUPT,(OpCodeType *)0x0,pcbListPtr);
  }
  reportString._0_8_ = 0x20555043203a534f;
  reportString._8_8_ = 0x7075727265746e69;
  reportString._16_8_ = 0x6920646e65202c74;
  reportString._24_8_ = CONCAT44(reportString._28_4_,0x656c64);
  runSimReport(1,configPtr,reportString);
  return;
}



OpCodeType * addNode(OpCodeType *localPtr,OpCodeType *newNode)

{
  OpCodeType *pOVar1;
  
  if (localPtr == (OpCodeType *)0x0) {
    localPtr = (OpCodeType *)malloc(0x38);
    localPtr->pid = newNode->pid;
    copyString(localPtr->command,newNode->command);
    copyString(localPtr->inOutArg,newNode->inOutArg);
    copyString(localPtr->strArg1,newNode->strArg1);
    localPtr->intArg2 = newNode->intArg2;
    localPtr->intArg3 = newNode->intArg3;
    localPtr->opEndTime = newNode->opEndTime;
    localPtr->nextNode = (OpCodeType *)0x0;
  }
  else {
    pOVar1 = addNode(localPtr->nextNode,newNode);
    localPtr->nextNode = pOVar1;
  }
  return localPtr;
}



int calcOpTime(ConfigDataType *config,OpCodeType *opCode)

{
  int iVar1;
  
  iVar1 = compareString(opCode->command,"dev");
  if (iVar1 == 0) {
    iVar1 = config->ioCycleRate * opCode->intArg2;
  }
  else {
    iVar1 = config->procCycleRate * opCode->intArg2;
  }
  return iVar1;
}



OpCodeType * clearMetaDataList(OpCodeType *localPtr)

{
  if (localPtr != (OpCodeType *)0x0) {
    clearMetaDataList(localPtr->nextNode);
    free(localPtr);
  }
  return (OpCodeType *)0x0;
}



void copyOpCode(OpCodeType *destination,OpCodeType *source)

{
  destination->pid = source->pid;
  copyString(destination->command,source->command);
  copyString(destination->inOutArg,source->inOutArg);
  copyString(destination->strArg1,source->strArg1);
  destination->intArg2 = source->intArg2;
  destination->intArg3 = source->intArg3;
  destination->opEndTime = source->opEndTime;
  destination->nextNode = source->nextNode;
  return;
}



OpCodeType * createInitOpCode(void)

{
  OpCodeType *pOVar1;
  OpCodeType *localPtr;
  
  pOVar1 = (OpCodeType *)malloc(0x38);
  pOVar1->pid = -1;
  copyString(pOVar1->command,"unusd");
  pOVar1->inOutArg[0] = '\0';
  pOVar1->strArg1[0] = '\0';
  pOVar1->intArg2 = -1;
  pOVar1->intArg3 = -1;
  pOVar1->opEndTime = 0.0;
  pOVar1->nextNode = (OpCodeType *)0x0;
  return pOVar1;
}



void displayMetaData(OpCodeType *localPtr)

{
  int iVar1;
  OpCodeType *local_10;
  
  puts("Meta-Data File Display");
  puts("----------------------\n");
  for (local_10 = localPtr; local_10 != (OpCodeType *)0x0; local_10 = local_10->nextNode) {
    printf("Op Code: ");
    printf("/pid: %d",(ulong)(uint)local_10->pid);
    printf("/cmd: %s",local_10->command);
    iVar1 = compareString(local_10->command,"dev");
    if (iVar1 == 0) {
      printf("/io: %s",local_10->inOutArg);
    }
    else {
      printf("/io: NA");
    }
    printf("\n\t /arg1: %s",local_10->strArg1);
    printf("/arg 2: %d",(ulong)(uint)local_10->intArg2);
    printf("/arg 3: %d",(ulong)(uint)local_10->intArg3);
    printf((char *)local_10->opEndTime,"/op end time: %8.6f");
    puts("\n");
  }
  return;
}



int getCommand(char *cmd,char *inputStr,int index)

{
  int local_2c;
  int lengthOfCommand;
  
  local_2c = index;
  while (local_2c < 3) {
    cmd[local_2c] = inputStr[local_2c];
    local_2c = local_2c + 1;
    cmd[local_2c] = '\0';
  }
  return local_2c;
}



_Bool getMetaData(char *fileName,OpCodeType **opCodeDataHead,char *endStateMsg)

{
  _Bool _Var1;
  int iVar2;
  FILE *inStream;
  OpCodeType *inData;
  OpCodeType *pOVar3;
  char dataBuffer [128];
  char READ_ONLY_FLAG [2];
  OpCodeType *newNodePtr;
  FILE *fileAccessPtr;
  OpCodeType *localHeadPtr;
  _Bool returnState;
  int endCount;
  int startCount;
  int accessResult;
  
  READ_ONLY_FLAG = 0x72;
  returnState = true;
  localHeadPtr = (OpCodeType *)0x0;
  *opCodeDataHead = (OpCodeType *)0x0;
  copyString(endStateMsg,"Metadata file upload successful");
  inStream = fopen(fileName,READ_ONLY_FLAG);
  if (inStream == (FILE *)0x0) {
    copyString(endStateMsg,"Metadata file access error");
    returnState = false;
  }
  else {
    _Var1 = getStringToDelimiter((FILE *)inStream,':',dataBuffer);
    if ((_Var1 == true) &&
       (iVar2 = compareString(dataBuffer,"Start Program Meta-Data Code"), iVar2 == 0)) {
      inData = (OpCodeType *)malloc(0x38);
      accessResult = getOpCommand((FILE *)inStream,inData);
      startCount = updateStartCount(0,inData->strArg1);
      endCount = updateEndCount(0,inData->strArg1);
      if (accessResult == COMPLETE_OPCMD_FOUND_MSG) {
        while (accessResult == 7) {
          localHeadPtr = addNode(localHeadPtr,inData);
          accessResult = getOpCommand((FILE *)inStream,inData);
          startCount = updateStartCount(startCount,inData->strArg1);
          endCount = updateEndCount(endCount,inData->strArg1);
        }
        if (accessResult == 8) {
          if (startCount != endCount) {
            fclose(inStream);
            pOVar3 = clearMetaDataList(localHeadPtr);
            *opCodeDataHead = pOVar3;
            free(inData);
            copyString(endStateMsg,"Unbalanced start and end arguments in metadata");
            return false;
          }
          localHeadPtr = addNode(localHeadPtr,inData);
          accessResult = 0;
          _Var1 = getStringToDelimiter((FILE *)inStream,'.',dataBuffer);
          if ((_Var1 != true) ||
             (iVar2 = compareString(dataBuffer,"End Program Meta-Data Code"), iVar2 != 0)) {
            accessResult = 2;
            copyString(endStateMsg,"Metadata corrupted descriptor error");
          }
        }
        else {
          copyString(endStateMsg,"Corrupted metadata op code");
          returnState = false;
        }
        if (accessResult != 0) {
          localHeadPtr = clearMetaDataList(localHeadPtr);
        }
        fclose(inStream);
        free(inData);
        *opCodeDataHead = localHeadPtr;
      }
      else {
        fclose(inStream);
        pOVar3 = clearMetaDataList((OpCodeType *)0x0);
        *opCodeDataHead = pOVar3;
        free(inData);
        copyString(endStateMsg,"Metadata incomplete first op command found");
        returnState = false;
      }
    }
    else {
      fclose(inStream);
      copyString(endStateMsg,"Corrupt metadata leader line error");
      returnState = false;
    }
  }
  return returnState;
}



OpCodeMessages getOpCommand(FILE *filePtr,OpCodeType *inData)

{
  _Bool _Var1;
  int iVar2;
  OpCodeMessages OVar3;
  undefined auStack200 [16];
  undefined auStack184 [16];
  OpCodeType *local_a8;
  FILE *local_a0;
  char strBuffer [64];
  int numBuffer;
  char_0_ *argStrBuffer;
  undefined8 local_40;
  char_0_ *cmdBuffer;
  undefined8 local_30;
  int MAX_ARG_STR_LENGTH;
  int MAX_CMD_LENGTH;
  _Bool arg3FailureFlag;
  _Bool arg2FailureFlag;
  int runningStringIndex;
  
  local_a0 = filePtr;
  local_a8 = inData;
  MAX_CMD_LENGTH = 5;
  MAX_ARG_STR_LENGTH = 0xf;
  numBuffer = 0;
  local_30 = 4;
  cmdBuffer = auStack184;
  local_40 = 0xe;
  argStrBuffer = auStack200;
  runningStringIndex = 0;
  arg2FailureFlag = false;
  arg3FailureFlag = false;
  _Var1 = getStringToDelimiter(filePtr,';',strBuffer);
  if (_Var1 == false) {
    return OPCMD_ACCESS_ERR;
  }
  runningStringIndex = getCommand(cmdBuffer,strBuffer,runningStringIndex);
  copyString(local_a8->command,cmdBuffer);
  _Var1 = verifyValidCommand(cmdBuffer);
  if (_Var1 != true) {
    return CORRUPT_OPCMD_ERR;
  }
  local_a8->pid = 0;
  local_a8->inOutArg[0] = '\0';
  local_a8->intArg2 = 0;
  local_a8->intArg3 = 0;
  local_a8->opEndTime = 0.0;
  local_a8->nextNode = (OpCodeType *)0x0;
  iVar2 = compareString(cmdBuffer,"dev");
  if (iVar2 == 0) {
    runningStringIndex = getStringArg(argStrBuffer,strBuffer,runningStringIndex);
    copyString(local_a8->inOutArg,argStrBuffer);
    iVar2 = compareString(argStrBuffer,"in");
    if ((iVar2 != 0) && (iVar2 = compareString(argStrBuffer,"out"), iVar2 != 0)) {
      return CORRUPT_OPCMD_ARG_ERR;
    }
  }
  runningStringIndex = getStringArg(argStrBuffer,strBuffer,runningStringIndex);
  copyString(local_a8->strArg1,argStrBuffer);
  _Var1 = verifyFirstStringArg(argStrBuffer);
  if (_Var1 != true) {
    return CORRUPT_OPCMD_ARG_ERR;
  }
  iVar2 = compareString(local_a8->command,"sys");
  if ((iVar2 == 0) && (iVar2 = compareString(local_a8->strArg1,"end"), iVar2 == 0)) {
    return LAST_OPCMD_FOUND_MSG;
  }
  iVar2 = compareString(local_a8->command,"app");
  if ((iVar2 == 0) && (iVar2 = compareString(local_a8->strArg1,"start"), iVar2 == 0)) {
    getNumberArg(&numBuffer,strBuffer,runningStringIndex);
    if (numBuffer < 0) {
      arg2FailureFlag = true;
    }
    local_a8->intArg2 = numBuffer;
  }
  else {
    iVar2 = compareString(local_a8->command,"cpu");
    if (iVar2 == 0) {
      getNumberArg(&numBuffer,strBuffer,runningStringIndex);
      if (numBuffer < 0) {
        arg2FailureFlag = true;
      }
      local_a8->intArg2 = numBuffer;
    }
    else {
      iVar2 = compareString(local_a8->command,"dev");
      if (iVar2 == 0) {
        getNumberArg(&numBuffer,strBuffer,runningStringIndex);
        if (numBuffer < 0) {
          arg2FailureFlag = true;
        }
        local_a8->intArg2 = numBuffer;
      }
      else {
        iVar2 = compareString(local_a8->command,"mem");
        if (iVar2 == 0) {
          runningStringIndex = getNumberArg(&numBuffer,strBuffer,runningStringIndex);
          if (numBuffer < 0) {
            arg2FailureFlag = true;
          }
          local_a8->intArg2 = numBuffer;
          getNumberArg(&numBuffer,strBuffer,runningStringIndex);
          if (numBuffer < 0) {
            arg3FailureFlag = true;
          }
          local_a8->intArg3 = numBuffer;
        }
      }
    }
  }
  if ((arg2FailureFlag == false) && (arg3FailureFlag == false)) {
    OVar3 = COMPLETE_OPCMD_FOUND_MSG;
  }
  else {
    OVar3 = CORRUPT_OPCMD_ARG_ERR;
  }
  return OVar3;
}



int getNumberArg(int *number,char *inputStr,int index)

{
  bool bVar1;
  _Bool _Var2;
  int local_2c;
  int multiplier;
  _Bool foundDigit;
  
  bVar1 = false;
  *number = 0;
  multiplier = 1;
  for (local_2c = index; (inputStr[local_2c] < '!' || (inputStr[local_2c] == ','));
      local_2c = local_2c + 1) {
  }
  for (; (_Var2 = isDigit(inputStr[local_2c]), _Var2 != false && (inputStr[local_2c] != '\0'));
      local_2c = local_2c + 1) {
    bVar1 = true;
    *number = (int)inputStr[local_2c] + *number * multiplier + -0x30;
    multiplier = 10;
  }
  if (!bVar1) {
    *number = -1;
  }
  return local_2c;
}



int getStringArg(char *strArg,char *inputStr,int index)

{
  int local_2c;
  int localIndex;
  
  localIndex = 0;
  for (local_2c = index; (inputStr[local_2c] < '!' || (inputStr[local_2c] == ','));
      local_2c = local_2c + 1) {
  }
  while ((inputStr[local_2c] != ',' && (inputStr[local_2c] != '\0'))) {
    strArg[localIndex] = inputStr[local_2c];
    local_2c = local_2c + 1;
    localIndex = localIndex + 1;
    strArg[localIndex] = '\0';
  }
  return local_2c;
}



_Bool isDigit(char testChar)

{
  _Bool _Var1;
  
  if ((testChar < '0') || ('9' < testChar)) {
    _Var1 = false;
  }
  else {
    _Var1 = true;
  }
  return _Var1;
}



int updateEndCount(int count,char *opString)

{
  int iVar1;
  
  iVar1 = compareString(opString,"end");
  if (iVar1 == 0) {
    count = count + 1;
  }
  return count;
}



int updateStartCount(int count,char *opString)

{
  int iVar1;
  
  iVar1 = compareString(opString,"start");
  if (iVar1 == 0) {
    count = count + 1;
  }
  return count;
}



_Bool verifyFirstStringArg(char *strArg)

{
  int iVar1;
  
  iVar1 = compareString(strArg,"access");
  if (((((iVar1 != 0) && (iVar1 = compareString(strArg,"allocate"), iVar1 != 0)) &&
       (iVar1 = compareString(strArg,"end"), iVar1 != 0)) &&
      ((((iVar1 = compareString(strArg,"ethernet"), iVar1 != 0 &&
         (iVar1 = compareString(strArg,"hard drive"), iVar1 != 0)) &&
        ((iVar1 = compareString(strArg,"keyboard"), iVar1 != 0 &&
         ((iVar1 = compareString(strArg,"monitor"), iVar1 != 0 &&
          (iVar1 = compareString(strArg,"printer"), iVar1 != 0)))))) &&
       (iVar1 = compareString(strArg,"process"), iVar1 != 0)))) &&
     ((((iVar1 = compareString(strArg,"serial"), iVar1 != 0 &&
        (iVar1 = compareString(strArg,"sound signal"), iVar1 != 0)) &&
       (iVar1 = compareString(strArg,"start"), iVar1 != 0)) &&
      ((iVar1 = compareString(strArg,"usb"), iVar1 != 0 &&
       (iVar1 = compareString(strArg,"video signal"), iVar1 != 0)))))) {
    return false;
  }
  return true;
}



_Bool verifyValidCommand(char *testCmd)

{
  int iVar1;
  
  iVar1 = compareString(testCmd,"sys");
  if ((((iVar1 != 0) && (iVar1 = compareString(testCmd,"app"), iVar1 != 0)) &&
      (iVar1 = compareString(testCmd,"cpu"), iVar1 != 0)) &&
     ((iVar1 = compareString(testCmd,"mem"), iVar1 != 0 &&
      (iVar1 = compareString(testCmd,"dev"), iVar1 != 0)))) {
    return false;
  }
  return true;
}



ConfigDataType * clearConfigData(ConfigDataType *configData)

{
  if (configData != (ConfigDataType *)0x0) {
    free(configData);
  }
  return (ConfigDataType *)0x0;
}



// WARNING: Could not reconcile some variable overlaps

void configCodeToString(int code,char *outString)

{
  char displayStrings [8] [10];
  
  displayStrings[0]._0_8_ = 0x4e2d464a53;
  displayStrings[0]._8_2_ = 0;
  displayStrings[1]._0_8_ = 0x502d46545253;
  displayStrings[1]._8_2_ = 0;
  displayStrings[2]._0_8_ = 0x502d53464346;
  displayStrings[2]._8_2_ = 0;
  displayStrings[3]._0_8_ = 0x502d5252;
  displayStrings[3]._8_2_ = 0;
  displayStrings[4]._0_8_ = 0x4e2d53464346;
  displayStrings[4]._8_2_ = 0;
  displayStrings[5]._0_8_ = 0x726f74696e6f4d;
  displayStrings[5]._8_2_ = 0;
  displayStrings[6]._0_8_ = 0x656c6946;
  displayStrings[6]._8_2_ = 0;
  displayStrings[7]._0_8_ = 0x68746f42;
  displayStrings[7]._8_2_ = 0;
  copyString(outString,(char *)displayStrings[code]);
  return;
}



void copyConfigData(ConfigDataType *dest,ConfigDataType *src)

{
  dest->version = src->version;
  copyString(dest->metaDataFileName,src->metaDataFileName);
  dest->cpuSchedCode = src->cpuSchedCode;
  dest->quantumCycles = src->quantumCycles;
  dest->memDisplay = src->memDisplay;
  dest->memAvailable = src->memAvailable;
  dest->procCycleRate = src->procCycleRate;
  dest->ioCycleRate = src->ioCycleRate;
  dest->logToCode = src->logToCode;
  copyString(dest->logToFileName,src->logToFileName);
  return;
}



void displayConfigData(ConfigDataType *configData)

{
  char displayString [64];
  
  puts("Config File Display");
  puts("-------------------");
  printf((char *)configData->version,"Version                : %3.2f\n");
  printf("Program file name      : %s\n",configData->metaDataFileName);
  configCodeToString(configData->cpuSchedCode,displayString);
  printf("CPU schedule selection : %s\n",displayString);
  printf("Quantum time           : %d\n",(ulong)(uint)configData->quantumCycles);
  printf("Memory Display         : ");
  if (configData->memDisplay == false) {
    puts("Off");
  }
  else {
    puts("On");
  }
  printf("Memory Available       : %d\n",(ulong)(uint)configData->memAvailable);
  printf("Process cycle rate     : %d\n",(ulong)(uint)configData->procCycleRate);
  printf("I/O cycle rate         : %d\n",(ulong)(uint)configData->ioCycleRate);
  configCodeToString(configData->logToCode,displayString);
  printf("Log to selection       : %s\n",displayString);
  printf("Log file name          : %s\n\n",configData->logToFileName);
  return;
}



void displayConfigError(int code)

{
  long lVar1;
  undefined8 *puVar2;
  char *pcVar3;
  char displayStrings [7] [40];
  
  puVar2 = (undefined8 *)"No Error";
  pcVar3 = (char *)displayStrings;
  for (lVar1 = 0x23; lVar1 != 0; lVar1 = lVar1 + -1) {
    *(undefined8 *)pcVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    pcVar3 = pcVar3 + 8;
  }
  printf("\nFATAL ERROR: %s, Program aborted\n",displayStrings[code]);
  return;
}



// WARNING: Could not reconcile some variable overlaps

_Bool getConfigData(char *fileName,ConfigDataType **configData,char *endStateMsg)

{
  _Bool _Var1;
  int iVar2;
  ConfigCodeMessages lineCode;
  ConfigDataCodes CVar3;
  FILE *inStream;
  ConfigDataType *__ptr;
  char testMsg_1 [32];
  char testMsg [37];
  double doubleData;
  int intData;
  char lowerCaseDataBuffer [128];
  char dataBuffer [128];
  char READ_ONLY_FLAG [2];
  int dataLineCode;
  ConfigDataType *tempData;
  FILE *fileAccessPtr;
  int NUM_DATA_LINES;
  int lineCtr;
  
  READ_ONLY_FLAG = 0x72;
  lineCtr = 0;
  testMsg._0_8_ = 0x72756769666e6f43;
  testMsg._8_8_ = 0x6966206e6f697461;
  testMsg._16_8_ = 0x616f6c707520656c;
  testMsg._24_8_ = 0x7365636375732064;
  testMsg._32_4_ = 0x6c756673;
  testMsg[36] = '\0';
  copyString(endStateMsg,testMsg);
  *configData = (ConfigDataType *)0x0;
  inStream = fopen(fileName,READ_ONLY_FLAG);
  if (inStream == (FILE *)0x0) {
    testMsg_1._0_8_ = 0x72756769666e6f43;
    testMsg_1._8_8_ = 0x6966206e6f697461;
    testMsg_1._16_8_ = 0x736563636120656c;
    testMsg_1._24_8_ = 0x726f7272652073;
    copyString(endStateMsg,testMsg_1);
  }
  else {
    _Var1 = getStringToDelimiter((FILE *)inStream,':',dataBuffer);
    if ((_Var1 == true) &&
       (iVar2 = compareString(dataBuffer,"Start Simulator Configuration File"), iVar2 == 0)) {
      __ptr = (ConfigDataType *)malloc(0xe8);
      while( true ) {
        if (9 < lineCtr) {
          _Var1 = getStringToDelimiter((FILE *)inStream,'.',dataBuffer);
          if ((_Var1 == true) &&
             (iVar2 = compareString(dataBuffer,"End Simulator Configuration File"), iVar2 == 0)) {
            if ((__ptr->memDisplay == false) || (__ptr->logToCode == 6)) {
              _Var1 = false;
            }
            else {
              _Var1 = true;
            }
            __ptr->memDisplay = _Var1;
            *configData = __ptr;
            fclose(inStream);
            return true;
          }
          free(__ptr);
          fclose(inStream);
          copyString(endStateMsg,"Configuration end line capture error");
          return false;
        }
        _Var1 = getStringToDelimiter((FILE *)inStream,':',dataBuffer);
        if (_Var1 != true) {
          free(__ptr);
          fclose(inStream);
          copyString(endStateMsg,"Configuration data leader line capture error");
          return false;
        }
        stripTrailingSpaces(dataBuffer);
        lineCode = getDataLineCode(dataBuffer);
        if (lineCode == CFG_CORRUPT_PROMPT_ERR) break;
        if (lineCode == CFG_VERSION_CODE) {
          __isoc99_fscanf(inStream,&DAT_00406735,&doubleData);
        }
        else if ((((lineCode == CFG_MD_FILE_NAME_CODE) || (lineCode == CFG_LOG_FILE_NAME_CODE)) ||
                 (lineCode == CFG_CPU_SCHED_CODE)) ||
                ((lineCode == CFG_LOG_TO_CODE || (lineCode == CFG_MEM_DISPLAY_CODE)))) {
          __isoc99_fscanf(inStream,&DAT_00406739,dataBuffer);
          setStrToLowerCase(lowerCaseDataBuffer,dataBuffer);
        }
        else {
          __isoc99_fscanf(inStream,&DAT_0040673c,&intData);
        }
        _Var1 = valueInRange(lineCode,intData,doubleData,lowerCaseDataBuffer);
        if (_Var1 == false) {
          free(__ptr);
          fclose(inStream);
          copyString(endStateMsg,"Configuration item out of range");
          return false;
        }
        switch(lineCode) {
        case CFG_VERSION_CODE:
          __ptr->version = doubleData;
          break;
        case CFG_MD_FILE_NAME_CODE:
          copyString(__ptr->metaDataFileName,dataBuffer);
          break;
        case CFG_CPU_SCHED_CODE:
          CVar3 = getCpuSchedCode(lowerCaseDataBuffer);
          __ptr->cpuSchedCode = CVar3;
          break;
        case CFG_QUANT_CYCLES_CODE:
          __ptr->quantumCycles = intData;
          break;
        case CFG_MEM_DISPLAY_CODE:
          iVar2 = compareString(lowerCaseDataBuffer,"on");
          __ptr->memDisplay = iVar2 == 0;
          break;
        case CFG_MEM_AVAILABLE_CODE:
          __ptr->memAvailable = intData;
          break;
        case CFG_PROC_CYCLES_CODE:
          __ptr->procCycleRate = intData;
          break;
        case CFG_IO_CYCLES_CODE:
          __ptr->ioCycleRate = intData;
          break;
        case CFG_LOG_TO_CODE:
          CVar3 = getLogToCode(lowerCaseDataBuffer);
          __ptr->logToCode = CVar3;
          break;
        case CFG_LOG_FILE_NAME_CODE:
          copyString(__ptr->logToFileName,dataBuffer);
        }
        lineCtr = lineCtr + 1;
      }
      free(__ptr);
      fclose(inStream);
      copyString(endStateMsg,"Corrupted configuration prompt");
      return false;
    }
    fclose(inStream);
    copyString(endStateMsg,"Corrupt configuration leader line error");
  }
  return false;
}



ConfigDataCodes getCpuSchedCode(char *lowerCaseCodeStr)

{
  int iVar1;
  ConfigDataCodes returnVal;
  
  returnVal = CPU_SCHED_FCFS_N_CODE;
  iVar1 = compareString(lowerCaseCodeStr,"sjf-n");
  if (iVar1 == 0) {
    returnVal = CPU_SCHED_SJF_N_CODE;
  }
  iVar1 = compareString(lowerCaseCodeStr,"srtf-p");
  if (iVar1 == 0) {
    returnVal = CPU_SCHED_SRTF_P_CODE;
  }
  iVar1 = compareString(lowerCaseCodeStr,"fcfs-p");
  if (iVar1 == 0) {
    returnVal = CPU_SCHED_FCFS_P_CODE;
  }
  iVar1 = compareString(lowerCaseCodeStr,"rr-p");
  if (iVar1 == 0) {
    returnVal = CPU_SCHED_RR_P_CODE;
  }
  return returnVal;
}



ConfigCodeMessages getDataLineCode(char *dataBuffer)

{
  int iVar1;
  ConfigCodeMessages CVar2;
  
  iVar1 = compareString(dataBuffer,"Version/Phase");
  if (iVar1 == 0) {
    CVar2 = CFG_VERSION_CODE;
  }
  else {
    iVar1 = compareString(dataBuffer,"File Path");
    if (iVar1 == 0) {
      CVar2 = CFG_MD_FILE_NAME_CODE;
    }
    else {
      iVar1 = compareString(dataBuffer,"CPU Scheduling Code");
      if (iVar1 == 0) {
        CVar2 = CFG_CPU_SCHED_CODE;
      }
      else {
        iVar1 = compareString(dataBuffer,"Quantum Time (cycles)");
        if (iVar1 == 0) {
          CVar2 = CFG_QUANT_CYCLES_CODE;
        }
        else {
          iVar1 = compareString(dataBuffer,"Memory Display (On/Off)");
          if (iVar1 == 0) {
            CVar2 = CFG_MEM_DISPLAY_CODE;
          }
          else {
            iVar1 = compareString(dataBuffer,"Memory Available (KB)");
            if (iVar1 == 0) {
              CVar2 = CFG_MEM_AVAILABLE_CODE;
            }
            else {
              iVar1 = compareString(dataBuffer,"Processor Cycle Time (msec)");
              if (iVar1 == 0) {
                CVar2 = CFG_PROC_CYCLES_CODE;
              }
              else {
                iVar1 = compareString(dataBuffer,"I/O Cycle Time (msec)");
                if (iVar1 == 0) {
                  CVar2 = CFG_IO_CYCLES_CODE;
                }
                else {
                  iVar1 = compareString(dataBuffer,"Log To");
                  if (iVar1 == 0) {
                    CVar2 = CFG_LOG_TO_CODE;
                  }
                  else {
                    iVar1 = compareString(dataBuffer,"Log File Path");
                    if (iVar1 == 0) {
                      CVar2 = CFG_LOG_FILE_NAME_CODE;
                    }
                    else {
                      CVar2 = CFG_CORRUPT_PROMPT_ERR;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return CVar2;
}



ConfigDataCodes getLogToCode(char *lowerCaseLogToStr)

{
  int iVar1;
  ConfigDataCodes returnVal;
  
  returnVal = LOGTO_MONITOR_CODE;
  iVar1 = compareString(lowerCaseLogToStr,"both");
  if (iVar1 == 0) {
    returnVal = LOGTO_BOTH_CODE;
  }
  iVar1 = compareString(lowerCaseLogToStr,"file");
  if (iVar1 == 0) {
    returnVal = LOGTO_FILE_CODE;
  }
  return returnVal;
}



void stripTrailingSpaces(char *str)

{
  int index;
  
  index = getStringLength(str);
  while (index = index + -1, str[index] == ' ') {
    str[index] = '\0';
  }
  return;
}



_Bool valueInRange(int lineCode,int intVal,double doubleVal,char *lowerCaseStringVal)

{
  int iVar1;
  _Bool result;
  
  result = true;
  switch(lineCode) {
  case 4:
    if ((doubleVal < 0.0) || (10.0 < doubleVal)) {
      result = false;
    }
    break;
  case 6:
    iVar1 = compareString(lowerCaseStringVal,"fcfs-n");
    if ((((iVar1 != 0) && (iVar1 = compareString(lowerCaseStringVal,"sjf-n"), iVar1 != 0)) &&
        (iVar1 = compareString(lowerCaseStringVal,"srtf-p"), iVar1 != 0)) &&
       ((iVar1 = compareString(lowerCaseStringVal,"fcfs-p"), iVar1 != 0 &&
        (iVar1 = compareString(lowerCaseStringVal,"rr-p"), iVar1 != 0)))) {
      result = false;
    }
    break;
  case 7:
    if ((intVal < 0) || (100 < intVal)) {
      result = false;
    }
    break;
  case 8:
    iVar1 = compareString(lowerCaseStringVal,"on");
    if ((iVar1 != 0) && (iVar1 = compareString(lowerCaseStringVal,"off"), iVar1 != 0)) {
      result = false;
    }
    break;
  case 9:
    if ((intVal < 0x400) || (0x19000 < intVal)) {
      result = false;
    }
    break;
  case 10:
    if ((intVal < 1) || (100 < intVal)) {
      result = false;
    }
    break;
  case 0xb:
    if ((intVal < 1) || (1000 < intVal)) {
      result = false;
    }
    break;
  case 0xc:
    iVar1 = compareString(lowerCaseStringVal,"both");
    if (((iVar1 != 0) && (iVar1 = compareString(lowerCaseStringVal,"monitor"), iVar1 != 0)) &&
       (iVar1 = compareString(lowerCaseStringVal,"file"), iVar1 != 0)) {
      result = false;
    }
  }
  return result;
}



int compareString(char *oneStr,char *otherStr)

{
  int iVar1;
  int iVar2;
  int diff;
  int index;
  
  for (index = 0; ((oneStr[index] != '\0' && (otherStr[index] != '\0')) && (index < 0x80));
      index = index + 1) {
    if ((int)oneStr[index] - (int)otherStr[index] != 0) {
      return (int)oneStr[index] - (int)otherStr[index];
    }
  }
  iVar1 = getStringLength(oneStr);
  iVar2 = getStringLength(otherStr);
  return iVar1 - iVar2;
}



void concatenateString(char *destStr,char *sourceStr)

{
  int sourceIndex;
  int destIndex;
  
  destIndex = getStringLength(destStr);
  sourceIndex = 0;
  while ((sourceStr[sourceIndex] != '\0' && (destIndex < 0x80))) {
    destStr[destIndex] = sourceStr[sourceIndex];
    destIndex = destIndex + 1;
    sourceIndex = sourceIndex + 1;
    destStr[destIndex] = '\0';
  }
  return;
}



void copyString(char *destStr,char *sourceStr)

{
  int index;
  
  index = 0;
  while ((sourceStr[index] != '\0' && (index < 0x80))) {
    destStr[index] = sourceStr[index];
    index = index + 1;
    destStr[index] = '\0';
  }
  return;
}



int findSubString(char *testStr,char *searchSubStr)

{
  int iVar1;
  int testStrLen;
  int internalIndex;
  int searchIndex;
  int masterIndex;
  
  iVar1 = getStringLength(testStr);
  masterIndex = 0;
  do {
    if (iVar1 <= masterIndex) {
      return -1;
    }
    internalIndex = masterIndex;
    searchIndex = 0;
    while ((internalIndex <= iVar1 && (testStr[internalIndex] == searchSubStr[searchIndex]))) {
      internalIndex = internalIndex + 1;
      searchIndex = searchIndex + 1;
      if (searchSubStr[searchIndex] == '\0') {
        return masterIndex;
      }
    }
    masterIndex = masterIndex + 1;
  } while( true );
}



_Bool getStringConstrained
                (FILE *inStream,_Bool clearLeadingNonPrintable,_Bool clearLeadingSpace,
                _Bool stopAtNonPrintable,char delimiter,char *capturedString)

{
  _Bool _Var1;
  int index;
  int intChar;
  
  index = 0;
  *capturedString = '\0';
  intChar = fgetc((FILE *)inStream);
  while ((intChar != -1 &&
         (((clearLeadingNonPrintable != false && (intChar < 0x20)) ||
          ((clearLeadingSpace != false && (intChar == 0x20))))))) {
    intChar = fgetc((FILE *)inStream);
  }
  if (intChar == -1) {
    _Var1 = false;
  }
  else {
    while ((((intChar != -1 && (index < 0x7f)) &&
            (((stopAtNonPrintable != false && (0x1f < intChar)) || (stopAtNonPrintable != true))))
           && (delimiter != intChar))) {
      capturedString[index] = (char)intChar;
      index = index + 1;
      capturedString[index] = '\0';
      intChar = fgetc((FILE *)inStream);
    }
    _Var1 = true;
  }
  return _Var1;
}



int getStringLength(char *testStr)

{
  int index;
  
  for (index = 0; (index < 0x40 && (testStr[index] != '\0')); index = index + 1) {
  }
  return index;
}



_Bool getStringToDelimiter(FILE *inStream,char delimiter,char *capturedString)

{
  _Bool _Var1;
  
  _Var1 = getStringConstrained(inStream,true,true,true,delimiter,capturedString);
  return _Var1;
}



_Bool getStringToLineEnd(FILE *inStream,char *capturedString)

{
  _Bool _Var1;
  
  _Var1 = getStringConstrained(inStream,true,true,true,'\x7f',capturedString);
  return _Var1;
}



void getSubString(char *destStr,char *sourceStr,int startIndex,int endIndex)

{
  int iVar1;
  char *destStr_00;
  char *tempSourceStr;
  int sourceStrLen;
  int sourceIndex;
  int destIndex;
  
  iVar1 = getStringLength(sourceStr);
  destIndex = 0;
  if (((startIndex < 0) || (endIndex < startIndex)) || (iVar1 <= endIndex)) {
    *destStr = '\0';
  }
  else {
    destStr_00 = (char *)malloc((long)(iVar1 + 1));
    copyString(destStr_00,sourceStr);
    sourceIndex = startIndex;
    while (sourceIndex <= endIndex) {
      destStr[destIndex] = destStr_00[sourceIndex];
      destIndex = destIndex + 1;
      sourceIndex = sourceIndex + 1;
      destStr[destIndex] = '\0';
    }
    free(destStr_00);
  }
  return;
}



void setStrToLowerCase(char *destStr,char *sourceStr)

{
  char cVar1;
  int iVar2;
  char *sourceStr_00;
  char *tempStr;
  int strLen;
  int index;
  
  index = 0;
  iVar2 = getStringLength(sourceStr);
  sourceStr_00 = (char *)malloc((long)(iVar2 + 1));
  while ((sourceStr[index] != '\0' && (index < 0x80))) {
    cVar1 = toLowerCase(sourceStr[index]);
    sourceStr_00[index] = cVar1;
    index = index + 1;
    sourceStr_00[index] = '\0';
  }
  copyString(destStr,sourceStr_00);
  free(sourceStr_00);
  return;
}



char toLowerCase(char testChar)

{
  if (('@' < testChar) && (testChar < '[')) {
    testChar = testChar + ' ';
  }
  return testChar;
}



// WARNING: Could not reconcile some variable overlaps

double accessTimer(int controlCode,char *timeStr)

{
  timeval endData;
  timeval lapData;
  timeval startData;
  double fpTime;
  
  fpTime = 0.0;
  accessTimer::lapSec = 0;
  accessTimer::lapUSec = 0;
  processTime(0.0,0.0,0.0,0.0,timeStr);
  if ((controlCode == 1) && (accessTimer::running != false)) {
    gettimeofday((timeval *)&lapData,(__timezone_ptr_t)0x0);
    accessTimer::lapSec = (int)lapData.tv_sec;
    accessTimer::lapUSec = (int)lapData.tv_usec;
    fpTime = processTime((double)accessTimer::startSec,(double)(int)lapData.tv_sec,
                         (double)accessTimer::startUSec,(double)(int)lapData.tv_usec,timeStr);
  }
  else if ((controlCode == 2) && (accessTimer::running != false)) {
    gettimeofday((timeval *)&endData,(__timezone_ptr_t)0x0);
    accessTimer::running = false;
    accessTimer::endSec = (int)endData.tv_sec;
    accessTimer::endUSec = (int)endData.tv_usec;
    fpTime = processTime((double)accessTimer::startSec,(double)(int)endData.tv_sec,
                         (double)accessTimer::startUSec,(double)(int)endData.tv_usec,timeStr);
  }
  else {
    gettimeofday((timeval *)&startData,(__timezone_ptr_t)0x0);
    accessTimer::running = true;
    accessTimer::startSec = (int)startData.tv_sec;
    accessTimer::startUSec = (int)startData.tv_usec;
  }
  return fpTime;
}



double processTime(double startSec,double endSec,double startUSec,double endUSec,char *timeStr)

{
  char *__s;
  double fpTime;
  double uSecDiff;
  double secDiff;
  
  secDiff = endSec - startSec;
  uSecDiff = endUSec - startUSec;
  if (uSecDiff < 0.0) {
    uSecDiff = uSecDiff + 1000000.0;
    secDiff = secDiff - 1.0;
  }
  __s = (char *)(uSecDiff / 1000000.0 + secDiff);
  sprintf(__s,timeStr,"%9.6f");
  return (double)__s;
}



// WARNING: Could not reconcile some variable overlaps

void runTimer(int milliSeconds)

{
  timeval endTime;
  timeval startTime;
  int secDiff;
  int mSecDiff;
  int endUSec;
  int startUSec;
  int startSec;
  int timeDiff;
  int uSecDiff;
  int endSec;
  
  gettimeofday((timeval *)&startTime,(__timezone_ptr_t)0x0);
  timeDiff = 0;
  while (timeDiff < milliSeconds) {
    gettimeofday((timeval *)&endTime,(__timezone_ptr_t)0x0);
    endSec = (int)endTime.tv_sec;
    uSecDiff = (int)endTime.tv_usec - (int)startTime.tv_usec;
    if (uSecDiff < 0) {
      uSecDiff = uSecDiff + 1000000;
      endSec = endSec + -1;
    }
    timeDiff = uSecDiff / 1000 + (endSec - (int)startTime.tv_sec) * 1000;
  }
  return;
}



void __libc_csu_init(EVP_PKEY_CTX *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  lVar1 = 0;
  _init(param_1);
  do {
    (*(code *)(&__frame_dummy_init_array_entry)[lVar1])((ulong)param_1 & 0xffffffff,param_2,param_3)
    ;
    lVar1 = lVar1 + 1;
  } while (lVar1 != 1);
  return;
}



void __libc_csu_fini(void)

{
  return;
}



void _fini(void)

{
  return;
}


