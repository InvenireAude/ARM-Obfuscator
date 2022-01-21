/*
 * File: Printer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Printer.h"
#include "elf32/Printer.h"

#include <elf/utils/Helper.h>

#include "Image.h"
#include "Identification.h"

namespace ELF {

using namespace Utils;

/*************************************************************************/
Printer::Printer(std::ostream& os):
	os(os){	
}
/*************************************************************************/
void Printer::Print(std::ostream& os, Image* pImage){

    Identification *pIdentification = pImage->getIdentification();

    switch (pIdentification->getClass()){
    case ELFCLASS32:
            Print(os, pImage->getHeader32());
        break;
    
    default:
         throw Tools::Exception()<<"Unsupported image class in the printer:"<<
             Map::Class.getString(pIdentification->getClass());
        break;
    }
}
/*************************************************************************/
void Printer::Print(std::ostream& os, Elf32::Header* pHeader){

    std::unique_ptr<Elf32::Printer> ptrPrinter(new Elf32::Printer(os, pHeader));
    ptrPrinter->printHeader();

}
/*************************************************************************/
void Printer::printIdentification(Identification* pIdentification){
    
    os<<"\t Class:    \t"<<Map::Class.getString(pIdentification->getClass())<<std::endl;
    os<<"\t Version:  \t"<<Map::Version.getString(pIdentification->getVersion())<<std::endl;
    os<<"\t Encoding: \t"<<Map::Data.getString(pIdentification->getDataEncoding())<<std::endl;
    
}
/*************************************************************************/
}
