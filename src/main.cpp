#include <iostream>

#include <armob/config.h>

#include <elf/elf.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " number" << std::endl;
}

int main(int argc, char *argv[])
{

  try{
    std::unique_ptr<ELF::Image> ptrImage(new Image(argv[1]));
    
    ELF::Printer::Print(std::cout, ptrImage.get());

  }catch (Tools::Exception &e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}
