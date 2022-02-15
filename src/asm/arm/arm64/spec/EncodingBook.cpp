/*
 * File: Instruction.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "EncodingBook.h"

#include <initializer_list>
#include <iomanip>

#include "Field.h"
#include "Operand.h"
#include "OperandFactory.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {


const EncodingBook::DefinitionTable EncodingBook::TheDefinitions = {
 #include "auto_encodings.h.in" 
};

 const EncodingBook::NameByIdMap EncodingBook::TheNameById = {
 #include "auto_encoding_names.h.in"
 };

const EncodingBook::MnemonicByIdMap EncodingBook::TheMnemonicById = {
#include "auto_encoding_mnemomic.h.in"
 };

const EncodingBook EncodingBook::TheInstance;
/*************************************************************************/
EncodingBook::EncodingBook(){

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

    for(const auto& d:TheDefinitions){
        OperandList& lstOperands(hmOperandListByIdMap[d.iEncodingId]);

        for(int i=0; i<Encoding::CMaxFields && d.operands[i] != O_None; i++){
            try{
                lstOperands.emplace_back(OperandFactory::CreateOperand(&d, d.operands[i]));
            }catch(Tools::Exception& e){
                std::cerr<<"Cannote create operand for :"<<getName(&d)<<", operand: "<<i;
                std::cerr<<",\t exception: "<<e<<std::endl;
            }
        }
    }
}
/*************************************************************************/
EncodingBook::~EncodingBook() throw(){
}
/*************************************************************************/
static inline EncodingId  _getMatchOpCode(uint32_t opCode){
#include "auto_dec_tree.c.in"
    throw Tools::Exception()<<"No encoding for "<<(void*)(long)opCode<<" found.";
}
/*************************************************************************/
const Encoding* EncodingBook::match(uint32_t opCode)const{

    EncodingId iEncodingId = _getMatchOpCode(opCode);

	EncodingByIdMap::const_iterator it = hmEncodingById.find(iEncodingId);

    if(it == hmEncodingById.end()){
        throw Tools::Exception()<<"No encoding for "<<(void*)(long)opCode<<" found.";
    }

    const Encoding* pEncoding(it->second);

    AliasByIdMap::const_iterator it2 = hmAliasById.find(pEncoding->iEncodingId);

    const Encoding* pResult = pEncoding;
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
const char* EncodingBook::getName(EncodingId iEncodingId)const{

    NameByIdMap::const_iterator it = TheNameById.find(iEncodingId);

    if(it == TheNameById.end()){
        return "???";
    }

    return it->second;
};
/*************************************************************************/
const Encoding* EncodingBook::get(EncodingId iEncodingId)const{

    EncodingByIdMap::const_iterator it = hmEncodingById.find(iEncodingId);

    if(it == hmEncodingById.end()){
        throw Tools::Exception()<<"No encoding for id: "<<(int)iEncodingId;
    }

    return it->second;
};
/*************************************************************************/
const char* EncodingBook::getMnemonic(EncodingId iEncodingId)const{

    MnemonicByIdMap::const_iterator it = TheMnemonicById.find(iEncodingId);

    if(it == TheMnemonicById.end()){
        return "???";
    }

    return it->second;
};
/*************************************************************************/
const EncodingBook::OperandList& EncodingBook::getEncodingOperands(EncodingId iEncodingId)const{

    OperandListByIdMap::const_iterator it = hmOperandListByIdMap.find(iEncodingId);

    if(it == hmOperandListByIdMap.end()){
        throw Tools::Exception()<<"No operand list for: "<<getName(iEncodingId);
    }

    return it->second;
}
/*************************************************************************/
}
}
}
}
