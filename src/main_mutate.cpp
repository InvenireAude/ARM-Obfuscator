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
#include <asm/arm/arm64/spec/Encoding.h>
#include <asm/arm/arm64/spec/EncodingBook.h>
#include <armob/DiscoveredSymbols.h>
#include <armob/helper/SymbolDiscoverer.h>
#include <armob/helper/Disassembler.h>

#include <elf/Expander.h>

#include <asm/arm/arm64/spec/enums.h>

using namespace ELF;

void info(char *s){
  std::cout << s << " Version " << armob_VERSION_MAJOR << "."
            << armob_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << s << " <input_file> <output_file>" << std::endl;
}


//TODO make it DiscoveredSymbols method ??
// Return decoded instruction class
// Who owns who Decoder/GenericInstruciton ??
// decoder.setOperands<O1,O2,O3>(v1,v2,v3) ??

ASM::GenericInstruction* createBlankInstruction(const ARMOB::DiscoveredSymbols* pSymbols, ASM::ARM::ARM64::Spec::EncodingId iEncodingId){

  const ASM::ARM::ARM64::Spec::Encoding*  pEncoding =  ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.get(iEncodingId);
  std::cout<<"create blank: "<<ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.getName(pEncoding)<<std::endl;
  return new (pSymbols->getInstructionFactory()->allocate()) ASM::GenericInstruction((const uint8_t*)&(pEncoding->opCode), 4, 0);
}


int main(int argc, char *argv[]){

  try{

    if(argc < 3){
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
        
        for(auto& s : ptrSymbols->getSymbols(ARMOB::Symbol::ST_Code)){
          if(s.second->getName().compare("fun") == 0){
            ASM::GenericInstruction* pInstruction = s.second->getStart();
     
            for(int i=0; i<0x50; i++)
              ptrSymbols->getInstructions().insertAfter(pInstruction, 
                new (ptrSymbols->getInstructionFactory()->allocate()) ASM::GenericInstruction(CNopOpCode, 4, 0));

              ptrSymbols->getInstructions().insertAfter(pInstruction, 
                new (ptrSymbols->getInstructionFactory()->allocate()) ASM::GenericInstruction(CAddOpCode, 4, 0));

            while(pInstruction && pInstruction->getOpcodeW() != 0x11000400){
                pInstruction=pInstruction->getNext();              
            }

            for(int i=0; i<0x50; i++){
                ASM::GenericInstruction* pNew =  createBlankInstruction(ptrSymbols.get(), ASM::ARM::ARM64::Spec::E_ADD_32_addsub_imm);

                ASM::ARM::ARM64::Decoder d(pNew, ASM::ARM::ARM64::Spec::E_ADD_32_addsub_imm);
                
                d.setOperand(ASM::ARM::ARM64::Spec::O_imm12, i);
                d.setOperand(ASM::ARM::ARM64::Spec::O_Rd,  i%5);
                d.setOperand(ASM::ARM::ARM64::Spec::O_Rn,  i%5);

                std::cout<<"create: "<<(void*)pInstruction<<"?"<<(void*)pNew<<std::endl;
                
                ptrSymbols->getInstructions().insertAfter(pInstruction, pNew);  
                pInstruction = pNew;              
            }

            s.second->updateSize();
          }

        }

        size_t iTextCodeSize = 0;
        ASM::GenericInstructionList& lstInstructions(ptrSymbols->getInstructions());

        for(ASM::GenericInstruction* pInstruction = lstInstructions.getHead();
            pInstruction != nullptr;
            pInstruction = pInstruction->getNext()){
              iTextCodeSize += pInstruction->getOpCodeLength();
        }

        size_t iOldTextSize = pHeader->lookup(".text")->get_size();
        
        Expander e(pHeader);

        if(iOldTextSize < iTextCodeSize){
          e.expand(iTextCodeSize - iOldTextSize);
          e.updateDataSegmentSymbols();
        }        

        size_t iCurrentAddress = pHeader->lookup(".text")->get_addr();

        std::cout<<"**************************************"<<(void*)lstInstructions.getHead()<<std::endl;

        for(ASM::GenericInstruction* pInstruction = lstInstructions.getHead();
            pInstruction != nullptr;
            pInstruction = pInstruction->getNext()){
            std::cout<<"Update address: "<<(void*)pInstruction->getCurrentAddresses().iOpCode<<" to "<<(void*)iCurrentAddress<<std::endl;
            pInstruction->getCurrentAddresses().iOpCode = iCurrentAddress;
            iCurrentAddress += pInstruction->getOpCodeLength();
        }


        for(ASM::GenericInstruction* pInstruction = lstInstructions.getHead();
            pInstruction != nullptr;
            pInstruction = pInstruction->getNext()){
             
            if(pInstruction->getCurrentAddresses().iReference){
                ASM::ARM::ARM64::Decoder d(pInstruction);
                d.updateOpcodeReference(e.getDataSegmentShift());
            }
            
        }

        uint8_t* pTextStart = pHeader->lookup(".text")->getData<uint8_t>();
        uint8_t* pCursor = pTextStart;
        
        for(ASM::GenericInstruction* pInstruction = lstInstructions.getHead();
            pInstruction != nullptr;
            pInstruction = pInstruction->getNext()){
            
            memcpy(pCursor, pInstruction->getOpcode(), pInstruction->getOpCodeLength());
            std::cout<<"Update opcode: "<<(void*)pInstruction->getCurrentAddresses().iOpCode<<std::endl;

            pCursor += pInstruction->getOpCodeLength();

        }

        pHeader->lookup(".text")->set_size(pCursor - pTextStart);
        // pHeader->lookup(".text")->set_size(pOrignalHeader->lookup(".text")->get_size());

        pHeader->getSymbolTable()->lookup("fun")->set_size(ptrSymbols->getSymbol("fun")->getSize());

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

