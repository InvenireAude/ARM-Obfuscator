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

    std::unique_ptr<ELF::Artefact> ptrArtefactCopy(new ArtefactCopy(ptrArtefact.get()));
    
    ELF::Elf64::Header* pHeader = ptrArtefactCopy->getHeader64();

    pHeader->insertSpaceAfter(pHeader->lookup(".text")->get_offset()+pHeader->lookup(".text")->get_size()-1, 32);

    ptrArtefactCopy->save(argv[2]);    

  }catch (Tools::Exception&e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}
