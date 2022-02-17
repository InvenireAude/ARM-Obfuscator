#include <iostream>

#include <tools/common.h>

#include <armob/config.h>

#include <elf/elf.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>
#include <elf/elf64/elf64printer.h>

#include <elf/utils/Helper.h>

#include <asm/GenericInstruction.h>
#include <asm/arm/arm64/DecodedInstruction.h>
#include <asm/arm/arm64/spec/Encoding.h>
#include <asm/arm/arm64/spec/EncodingBook.h>
#include <armob/DiscoveredSymbols.h>
#include <armob/helper/SymbolDiscoverer.h>
#include <armob/helper/SymbolBuilder.h>
#include <armob/helper/Disassembler.h>

#include <elf/Expander.h>

#include <asm/arm/arm64/spec/enums.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " <input_file> <output_file>" << std::endl;
}

using namespace ASM::ARM::ARM64;
using namespace ASM::ARM::ARM64::Spec;

int main(int argc, char *argv[]){

  try{

    if(argc < 4){
      throw Tools::Exception()<<"Bad parameters.";
    }

    std::unique_ptr<ELF::Artefact> ptrArtefact(new ArtefactFromFile(argv[1]));
    
    //ELF::Printer::Print(std::cout, ptrArtefact.get());

   static uint8_t CNopOpCode[4] = { 0x1f, 0x20, 0x03, 0xd5 };
   static uint8_t CAddOpCode[4] = { 0x33, 0x00, 0x09, 0x0b };
   static uint8_t CIncOpCode[4] = { 0x00, 0x04, 0x00, 0x11 };


  ELF::Elf64::Header* pOrignalHeader = ptrArtefact->getHeader64();


   if(ptrArtefact->getIdentification()->getClass() == ELFCLASS64){

        std::unique_ptr<ELF::Artefact> ptrArtefactCopy(new ArtefactCopy(ptrArtefact.get()));
        
        ELF::Elf64::Header* pHeader = ptrArtefactCopy->getHeader64();

        std::unique_ptr<ARMOB::DiscoveredSymbols> ptrSymbols(new ARMOB::DiscoveredSymbols());
        ARMOB::Helper::SymbolDiscoverer d(ptrArtefactCopy.get(), ptrSymbols.get());

        d.discover();
        d.build();
        d.resolve();
        
        ARMOB::Helper::SymbolBuilder b(ptrArtefactCopy.get(), ptrSymbols.get());


        ARMOB::Symbol* pFunSymbol = ptrSymbols->getSymbol(argv[3]);

        pFunSymbol->withFirst([&b](auto& itInstruction){

            for(int i=0; i<5; i++){
              b.createBlankInstruction(itInstruction, Spec::E_NOP_HI_hints);
            }
        
        });

       pFunSymbol->forAll([&b](auto& itInstruction){

            if( itInstruction->template getEncoded<ASM::Item::ET_ARMv8, Spec::Encoding*>()->iEncodingId == 
                      Spec::E_LDR_32_ldst_pos){
                        for(int i=0; i<20; i++){

                        itInstruction = b.createBlankInstruction(itInstruction, Spec::E_ADD_32_addsub_imm);

                        ASM::ARM::ARM64::DecodedInstruction d(*itInstruction);
                      
                        d.setOperands<O_Rd, O_Rn, O_imm12>( (i+1) % 5, i % 5, i);

                    }
                }
        
        });

        // pFunSymbol->forAllSkipNew([&b](auto& itInstruction){
        //   b.createBlankInstruction(itInstruction, Spec::E_NOP_HI_hints);
        // });

        pFunSymbol->updateSize();

        size_t iTextCodeSize = 0;

        for(auto& item: ptrSymbols->getInstructions()){
              iTextCodeSize += item.getGenericDetail()->getOpCodeLength();
        }

        size_t iOldTextSize = pHeader->lookup(".text")->get_size();
        
        Expander e(pHeader);

        if(iOldTextSize < iTextCodeSize){
          e.expand(iTextCodeSize - iOldTextSize);
          e.updateDataSegmentSymbols();
        }        

        size_t iCurrentAddress = pHeader->lookup(".text")->get_addr();

        std::cout<<"**************************************"<<std::endl;

      for(auto& item: ptrSymbols->getInstructions()){
            std::cout<<"Update address: "<<(void*)item.getGenericDetail()->getCurrentAddresses().iOpCode<<" to "<<(void*)iCurrentAddress<<std::endl;
            item.getGenericDetail()->getCurrentAddresses().iOpCode = iCurrentAddress;
            iCurrentAddress += item.getGenericDetail()->getOpCodeLength();
        }


      for(auto& item: ptrSymbols->getInstructions()){
             
            if(item.getGenericDetail()->getCurrentAddresses().iReference){
                ASM::ARM::ARM64::DecodedInstruction d(item);
                d.updateOpcodeReference(e.getDataSegmentShift());
            }
            
        }

        uint8_t* pTextStart = pHeader->lookup(".text")->getData<uint8_t>();
        uint8_t* pCursor = pTextStart;
        
        for(auto& item: ptrSymbols->getInstructions()){
            
            memcpy(pCursor, item.getGenericDetail()->getOpcode(), item.getGenericDetail()->getOpCodeLength());
            std::cout<<"Update opcode: "<<(void*)item.getGenericDetail()->getCurrentAddresses().iOpCode<<std::endl;

            pCursor += item.getGenericDetail()->getOpCodeLength();

        }

        pHeader->lookup(".text")->set_size(pCursor - pTextStart);

        pHeader->getSymbolTable()->lookup(argv[3])->set_size(ptrSymbols->getSymbol(argv[3])->getSize());

        ARMOB::Helper::Disassembler dis(ptrSymbols.get());

        // TODO .plt refrence adpr address ......
        (*pHeader->getSegments().begin())->set_filesz(
            pHeader->lookup(".eh_frame")->get_addr()+
            pHeader->lookup(".eh_frame")->get_size()+1
        );

      (*pHeader->getSegments().begin())->set_memsz(
            pHeader->lookup(".eh_frame")->get_addr()+
            pHeader->lookup(".eh_frame")->get_size()+1
        );

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

