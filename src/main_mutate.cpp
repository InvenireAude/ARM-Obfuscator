#include <iostream>

#include <tools/common.h>

#include <armob/config.h>

#include <elf/elf.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>
#include <elf/elf64/elf64printer.h>

#include <elf/utils/Helper.h>

#include <asm/GenericInstruction.h>
#include <asm/arm/arm64/Decoder.h>
#include <armob/DiscoveredSymbols.h>
#include <armob/helper/SymbolDiscoverer.h>
#include <armob/helper/Disassembler.h>

#include <elf/Expander.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " <input_file> <output_file>" << std::endl;
}



int main(int argc, char *argv[]){

  try{

    if(argc != 3){
      throw Tools::Exception()<<"Bad parameters.";
    }

    std::unique_ptr<ELF::Artefact> ptrArtefact(new ArtefactFromFile(argv[1]));
    
    //ELF::Printer::Print(std::cout, ptrArtefact.get());

   if(ptrArtefact->getIdentification()->getClass() == ELFCLASS64){



        std::unique_ptr<ELF::Artefact> ptrArtefactCopy(new ArtefactCopy(ptrArtefact.get()));
        
        ELF::Elf64::Header* pHeader = ptrArtefactCopy->getHeader64();

        std::unique_ptr<ARMOB::DiscoveredSymbols> ptrSymbols(new ARMOB::DiscoveredSymbols());
        ARMOB::Helper::SymbolDiscoverer d(ptrArtefactCopy.get(), ptrSymbols.get());

        d.discover();
        d.build();
        d.resolve();
        

        for(auto& s : ptrSymbols->getSymbols(ARMOB::Symbol::ST_Code)){
          ASM::GenericInstruction* pInstruction = s.second->getStart();
         // pInstruction->
        }

        Expander e(pHeader);

        e.expand(0x11111);
        e.updateDataSegmentSymbols();
        
        ARMOB::Helper::Disassembler dis(ptrSymbols.get());
        if(argc == 4){
          dis.print(argv[3], std::cout);
        }


    pHeader->write();
    ptrArtefactCopy->save(argv[2]);    
   }

  }catch (Tools::Exception&e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}

