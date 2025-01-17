#include <memory>

#include "ROOTReader.h"
#include "SIOReader.h"

std::unique_ptr<podio::IReader> getReader(const std::string& FileName){                                                                                                                      
                                                                                                                                                                                             
  if(FileName.substr(FileName.length()-4)=="root"){                                                                                                                                          
    return std::make_unique<podio::ROOTReader>();                                                                                                                                            
  }                                                                                                                                                                                          
  else{                                                                                                                                                                                      
    return std::make_unique<podio::SIOReader>();
  }                                                                                                                                                                                         
}
