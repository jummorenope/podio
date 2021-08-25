#include <iostream>
#include <iomanip>
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"
#include "podio/SIOReader.h"
#include "podio/CollectionBase.h"
#include "podio/tools.h"

int main(int argc, char* argv[]){
  
  if(argc!=2){
    std::cout<<"ERROR FileName not received"<<std::endl;
    return 0;
  }
  std::string FileName{argv[1]};
  
  //Declaring the reader object and openning the file
  auto reader = getReader(FileName);
  reader->openFile(FileName);
  int evt=reader->getEntries();
  
  //Pinting important info of the file
  std::cout<<"FileName: "<<FileName<<std::endl;
  std::cout<<"Number of events: "<<evt<<std::endl;
  std::cout<<std::endl;
  
  //Getting Table containing the info about the collections
  const auto collIDTable = reader->getCollectionIDTable();
  const auto collNames = collIDTable->names();
  //Iterating over all events to get size for each event
  for(int i=0; i<evt; i++){
    std::cout<<std::left<<std::setw(30)<<"Name"<<std::left<<std::setw(40)<<"Type"<<"Colection Size"<<std::endl;
    std::cout<<"-------------------------------------------------------------------------------------"<<std::endl;

    reader->readEvent();
    //Iterating over the collections to get each kind of data type
    for (const auto& name : collNames) {
      
      const auto coll = reader->readCollection(name);
      auto size = coll->size();
      const auto type = coll->getValueTypeName();
      //Printing Collection Names
      std::cout<<std::left<<std::setw(30)<<name<<std::left<<std::setw(40)<<type<<size<<"\n";
    }
    reader->endOfEvent();

    std::cout<<std::endl;
  }
  return 0;
}