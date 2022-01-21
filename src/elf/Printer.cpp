/*
 * File: Printer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Printer.h"

#include <elf/utils/Helper.h>

#include <elf/elf32/elf32.h>

#include "Image.h"
#include "Identification.h"

namespace ELF {

namespace Elf32 {
    typedef Template::Printer<Elf32::S>  Printer;
};

using namespace Utils;

/*************************************************************************/
Printer::Printer(std::ostream& os):
	os(os){	
}
/*************************************************************************/
void Printer::Print(std::ostream& os, Image* pImage){

    Identification *pIdentification = pImage->getIdentification();

    switch (pIdentification->getClass()){
    case ELFCLASS32:{
            
            std::unique_ptr< Template::Header<Elf32::S> > ptrHeader(
                new Template::Header<Elf32::S>(pImage)
            );

            std::unique_ptr<Elf32::Printer> ptrPrinter(new Elf32::Printer(os, ptrHeader.get()));
            ptrPrinter->printHeader();

        }
        break;
    
    default:
         throw Tools::Exception()<<"Unsupported image class in the printer:"<<
             Map::Class.getString(pIdentification->getClass());
        break;
    }
}
/*************************************************************************/
// void Printer::Print(std::ostream& os, Template::Header<Elf32::S>* pHeader){

//     std::unique_ptr<Elf32::Printer> ptrPrinter(new Template::Printer<Elf32::S>(os, pHeader));
//     ptrPrinter->printHeader();

// }
/*************************************************************************/
void Printer::printIdentification(Identification* pIdentification){
    
    os<<"\t Class:    \t"<<Map::Class.getString(pIdentification->getClass())<<std::endl;
    os<<"\t Version:  \t"<<Map::Version.getString(pIdentification->getVersion())<<std::endl;
    os<<"\t Encoding: \t"<<Map::Data.getString(pIdentification->getDataEncoding())<<std::endl;
    
}
/*************************************************************************/
}
