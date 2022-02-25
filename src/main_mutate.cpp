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

#include <armob/WorkContext.h>
#include <armob/DiscoveredSymbols.h>
#include <armob/DiscoveredDetails.h>

#include <armob/helper/Discoverer.h>
#include <armob/helper/Builder.h>
#include <armob/helper/Disassembler.h>
#include <armob/helper/InstructionFactory.h>

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
using namespace ARMOB;

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

        WorkContext ctx(ptrArtefact.get());
        Helper::Discoverer discoverer(&ctx);

        discoverer.discover();

        DiscoveredDetails *pTextDetails = ctx.getDetails(WorkContext::CTextSection);

        Helper::InstructionFactory factory(pTextDetails);

        Symbol* pFunSymbol = ctx.getSymbols()->getSymbol(argv[3]);


      //   pFunSymbol->withFirst([&factory](auto& itInstruction){

      //       auto itNext(itInstruction);
      //       ++itNext;
      //       factory.createJump(itInstruction, Spec::E_BL_only_branch_imm, itNext);
        
      //   });

      //   pFunSymbol->withFirst([&factory](auto& itInstruction){
          
      //       ++itInstruction;
      //       for(int i=0; i<5; i++){
      //         factory.create(itInstruction, Spec::E_NOP_HI_hints);
      //       }
        
      //   });

      //  pFunSymbol->forAll([&factory](auto& itInstruction){

      //       if( itInstruction->template getEncoded<ASM::Item::ET_ARMv8, Spec::Encoding*>()->iEncodingId == 
      //                 Spec::E_LDR_32_ldst_pos){
      //                   for(int i=0; i<20; i++){

      //                   itInstruction = factory.create(itInstruction, Spec::E_ADD_32_addsub_imm);

      //                   ASM::ARM::ARM64::DecodedInstruction d(*itInstruction);
                      
      //                   d.setOperands(O_Rd, (i+1) % 5, O_Rn, i % 5, O_imm12, 3 * i);

      //               }
      //           }
        
      //   });

        // pFunSymbol->forAllSkipNew([&b](auto& itInstruction){
        //   b.createBlankInstruction(itInstruction, Spec::E_NOP_HI_hints);
        // });


/********************

       long iCounter = 0;

       typedef std::pair<ASM::ItemList::iterator, ASM::ItemList::iterator> ChunkType;
       typedef std::list< ChunkType >  ChunkList; 
       ChunkList lstChunks;

       ASM::ItemList::iterator it = pFunSymbol->getStart();
       ASM::ItemList::iterator itChunkStart(it);

       while(true){


          if(!it || it == pFunSymbol->getEnd()){
            
            if(it && it != itChunkStart){
              lstChunks.push_back(ChunkType(itChunkStart, it));
            }

            break;
          }

          if(++iCounter % 5 == 0){

            ASM::ItemList::iterator itTmp = it;
            ++itTmp;
            it = factory.create(it, Spec::E_CMP_SUBS_64S_addsub_imm);

            ASM::ARM::ARM64::DecodedInstruction d(*it);          
            d.setOperand(Spec::O_Rn, 19);
            it = factory.createJump(it, Spec::E_B_only_condbranch, itTmp); 
            ASM::ARM::ARM64::DecodedInstruction d2(*it);          
            d2.setOperand(Spec::O_cond, 1);
            lstChunks.push_back(ChunkType(itChunkStart, it));
            it++;
            itChunkStart = it;
          }else{
            ++it;
          }
       }

********************/

       long iCounter = 0;

       typedef std::pair<ASM::ItemList::iterator, ASM::ItemList::iterator> ChunkType;
       typedef std::list< ChunkType >  ChunkList; 
       ChunkList lstChunks;

       ASM::ItemList::iterator it = pFunSymbol->getStart();
       ASM::ItemList::iterator itChunkStart(it);

       while(true){

          if(!it || it == pFunSymbol->getEnd()){
            
            if(it && it != itChunkStart){
              lstChunks.push_back(ChunkType(itChunkStart, it));
            }

            break;
          }

          if(++iCounter % 5 == 0){

            ASM::ItemList::iterator itTmp = it;
            ++itTmp;

            static const int CRegisterNo = 2;

            it = factory.create(it, Spec::E_ADR_only_pcreladdr);                    
            ASM::ARM::ARM64::DecodedInstruction(*it)
              .setOperand(Spec::O_Rd, CRegisterNo);          

            it = factory.create(it, Spec::E_ADD_64_addsub_imm);                    
              ASM::ARM::ARM64::DecodedInstruction(*it)
              .setOperand(Spec::O_Rd, CRegisterNo)
              .setOperand(Spec::O_Rn, CRegisterNo);

            it->getGenericDetail()->setReference(itTmp->getGenericDetail());
            it->setUpdateReference([](ASM::Item* pItem){

                uint64_t iFromAddress  = pItem->getPrev()->getGenericDetail()->getCurrentAddresses().iOpCode;
                uint64_t iTargetAddress  = pItem->getGenericDetail()->getReference()->getCurrentAddresses().iOpCode;
    
                int64_t iJump = iTargetAddress - iFromAddress;

                ASM::ARM::ARM64::DecodedInstruction(*pItem->getPrev())
                  .setOperand(Spec::O_immhi_immlo, iJump - 5);

                ASM::ARM::ARM64::DecodedInstruction(*pItem)
                  .setOperand(Spec::O_imm12, 5);

            });

            it = factory.create(it, Spec::E_BR_64_branch_reg); 
            ASM::ARM::ARM64::DecodedInstruction(*it).setOperand(Spec::O_Rn, CRegisterNo);

            lstChunks.push_back(ChunkType(itChunkStart, it));
            it++;
            itChunkStart = it;
          }else{
            ++it;
          }
       }


        std::cout<<std::endl<<"Chunks:"<<lstChunks.size()<<std::endl;

        for(auto& p: lstChunks){
            
            auto it = p.first;
            
            std::cout<<std::endl<<"Chunk"<<std::endl;

            do{
              ASM::ARM::ARM64::DecodedInstruction d(*it);
              d.print(std::cout);
              std::cout<<std::endl;   
            }while(it++ != p.second);

        };

        ASM::ItemList& lstInstructions(ctx.getDetails(ARMOB::WorkContext::CTextSection)->getInstructions());

        for(auto& p: lstChunks){
          
          if(p.first != lstChunks.front().first && p.first != lstChunks.back().first){
             
            std::cout<<std::endl<<"Chunk2"<<std::endl;

            lstInstructions.insertAfter(lstChunks.begin()->second, p.first, p.second);
            // break;
          }

        }

        Helper::Builder builder(&ctx);
        builder.build();

        ctx.save(argv[2]);    
        
        if(argc == 4){
          std::cout<<std::endl<<"Function: "<<argv[3]<<std::endl;
          Helper::Disassembler dis(ctx.getSymbols());
          dis.print(argv[3], std::cout);
        }

   }

  }catch (Tools::Exception&e){
    std::cerr << "Exception: " << e << std::endl;
    info(argv[0]);
  }


}

