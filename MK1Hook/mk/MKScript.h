#pragma once
#include "..\utils.h"
#include "..\unreal\TArray.h"

struct mko_function_info_mk12 {
    char pad[40];
    TArray<int> args;

};
// from mkoasm
#pragma pack(push, 1)
struct mko_function_header_mk12 {
    int64 field0;
    char* functionName; // offset to string table in mko
    mko_function_info_mk12* functionInfo;
    int field24;
    int field28;
    int field32;
    int field36;
    int field40;
    int field44;
    int field48;
    int field52;
};
#pragma pack(pop)

struct mko_variable_header_mk12 {
    int stack_offset;
    int data;
    unsigned int nameHash;
    int size;
    int stride;
    int pad;
};

struct MKScriptData {
    char pad[0xA0];
    TArray<char> script_string;
};




class MKScript {
public:
    char pad[0x18];
    MKScriptData* scriptData;
    char _pad[152];
    TArray<mko_function_header_mk12> functions;

    int GetFunctionID(unsigned int hash);
    int64 GetVariable(unsigned int hash);

};
VALIDATE_OFFSET(MKScript, scriptData, 0x18);
VALIDATE_OFFSET(MKScript, functions, 0xB8);
VALIDATE_SIZE(mko_function_header_mk12, 56);

MKScript* GetScript(const char* name);

class MKScriptCharacterAction {
public:
};


MKScriptCharacterAction* Create_CharacterScriptAction(MKScript* script, unsigned int function);

MKScriptCharacterAction* Alloc_ScriptCharacterAction(int size);