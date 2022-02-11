#include <iostream>

#include <tools/common.h>

#include <armob/config.h>

#include <elf/elf.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>
#include <elf/elf64/elf64printer.h>

#include <elf/utils/Helper.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " <input_file>" << std::endl;
}

int main(int argc, char *argv[]){

  try{

    if(argc != 2){
      throw Tools::Exception()<<"Bad parameters.";
    }

    std::unique_ptr<ELF::Artefact> ptrArtefact(new ArtefactFromFile(argv[1]));
    
    ELF::Printer::Print(std::cout, ptrArtefact.get());

      

  }catch (Tools::Exception&e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}
