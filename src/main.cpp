#include <iostream>

#include <armob/config.h>

#include <elf/elf.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>
#include <elf/elf64/elf64printer.h>

#include <elf/utils/Helper.h>

#include <asm/GenericInstruction.h>
#include <asm/arm/arm64/Decoder.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " number" << std::endl;
}

int main(int argc, char *argv[]){

  try{
    std::unique_ptr<ELF::Artefact> ptrArtefact(Artefact::CreateFromFile(argv[1]));
    
    ELF::Printer::Print(std::cout, ptrArtefact.get());

    argc -= 2;

    while(argc > 0){
	  
      if(ptrArtefact->getIdentification()->getClass() == ELFCLASS64){

        const ELF::Elf64::Header* pHeader = ptrArtefact->getHeader64();
        const ELF::Elf64::Symbol* pSymbol = pHeader->getSymbolTable()->lookup(argv[2]);
        
        ELF::Elf64::Printer printer(std::cout, pHeader);
        printer.printSymbol(0, pSymbol);
	      std::cout<<Utils::Helper::BinarytoHex(pSymbol->getData<uint8_t>(), pSymbol->get_size());
	      std::cout<<std::endl;

        ELF::Elf64::S::Addr iAddress = pSymbol->get_value();

        const uint8_t *pData = pSymbol->getData<uint8_t>();
        size_t  iSize  = pSymbol->get_size();

        if(iSize == 0)
          iSize = 44; //???

        const int iStep = 4;

        for(size_t  iOffset = 0; iOffset < iSize; iOffset += iStep){
          
          ASM::GenericInstruction ins(pData + iOffset, iStep, iAddress + iOffset);

          ASM::ARM::ARM64::Decoder d(&ins);
          d.print(std::cout);
          std::cout<<std::endl;
        }

      }
      argc--;
    }

  }catch (Tools::Exception &e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}
