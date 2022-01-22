/*
 * File: Printer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Printer.h"

#include <elf/utils/Helper.h>

#include <elf/elf32/elf32printer.h>
#include <elf/elf64/elf64printer.h>

#include "Artefact.h"
#include "Identification.h"

namespace ELF {

using namespace Utils;

/*************************************************************************/
Printer::Printer(std::ostream& os):
	os(os){	
}
/*************************************************************************/
void Printer::Print(std::ostream& os, Artefact* pArtefact){

    Identification *pIdentification = pArtefact->getIdentification();

    switch (pIdentification->getClass()){
    case ELFCLASS32:
            Print(os, pArtefact->getHeader32());
        break;
    case ELFCLASS64:
            Print(os, pArtefact->getHeader64());
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
void Printer::Print(std::ostream& os, Elf64::Header* pHeader){

    std::unique_ptr<Elf64::Printer> ptrPrinter(new Elf64::Printer(os, pHeader));
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
