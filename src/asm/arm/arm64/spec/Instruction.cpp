/*
 * File: Instruction.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Instruction.h"

#include <initializer_list>
#include <iomanip>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {


const Instruction::DefinitionTable Instruction::TheDefinitions = {
 #include "auto_encodings.h.in" 
};

 const Instruction::NameByIdMap Instruction::TheNameById = {
#include "auto_encoding_names.h.in"
 };

const Instruction::MnemonicByIdMap Instruction::TheMnemonicById = {
#include "auto_encoding_mnemomic.h.in"
 };

const Instruction Instruction::TheInstance;
/*************************************************************************/
Instruction::Instruction(){

    for(const auto& d:TheDefinitions){
        hmEncodingById[d.iEncodingId] = &d;
    }

    for(const auto& d:TheDefinitions){
        if(d.iAliasInstructionId != I_None){
            for(const auto& da:TheDefinitions){
                if(da.iInstructionId == d.iAliasInstructionId &&
                   (d.opCode & da.opCodeMask) == da.opCode){
                    std::cout<<"Adding alias: "<<getName(&d)<<" to "<<getName(&da)<<std::endl;
                    hmAliasById[da.iEncodingId].push_back(&d);
                }
            }
        }
    }
}
/*************************************************************************/
Instruction::~Instruction() throw(){
}
/*************************************************************************/
static inline EncodingId  _getMatchOpCode(uint32_t opCode){
#include "auto_dec_tree.c.in"
    throw Tools::Exception()<<"No encoding for "<<(void*)(long)opCode<<" found.";
}
/*************************************************************************/
const Instruction::Encoding* Instruction::match(uint32_t opCode)const{

    EncodingId iEncodingId = _getMatchOpCode(opCode);

	EncodingByIdMap::const_iterator it = hmEncodingById.find(iEncodingId);

    if(it == hmEncodingById.end()){
        throw Tools::Exception()<<"No encoding for "<<(void*)(long)opCode<<" found.";
    }

    const Instruction::Encoding* pEncoding(it->second);

    AliasByIdMap::const_iterator it2 = hmAliasById.find(pEncoding->iEncodingId);

    const Instruction::Encoding* pResult = pEncoding;
    int iCount = 0;
    if(it2 != hmAliasById.end()
       && pEncoding->iInstructionId != I_UBFM
       && pEncoding->iInstructionId != I_BFM){ // We do not like this case, alias perf condition not imlemented.
        for(const auto a : it2->second){
            if( (opCode & a->opCodeMask) == a->opCode){
                pResult = a;
                iCount++;
            }
        }
    }

    if(iCount >= 2){
        std::cerr<<"WARNING!!! to many aliases for: "<<(void*)(long)opCode<<" = "<<iCount<<std::endl;
        return pEncoding;
    }

    return pResult;
}
/*************************************************************************/
const char* Instruction::getName(EncodingId iEncodingId)const{

    NameByIdMap::const_iterator it = TheNameById.find(iEncodingId);

    if(it == TheNameById.end()){
        return "???";
    }

    return it->second;
};
/*************************************************************************/
const char* Instruction::getMnemonic(EncodingId iEncodingId)const{

    MnemonicByIdMap::const_iterator it = TheMnemonicById.find(iEncodingId);

    if(it == TheMnemonicById.end()){
        return "???";
    }

    return it->second;
};
/*************************************************************************/
}
}
}
}
