#include "SIO/SIOCalHitHandler.h"

#include "SIO/LCSIO.h"

#include "EVENT/MCParticle.h"
#include "EVENT/CalorimeterHit.h"
#include "IOIMPL/CalorimeterHitIOImpl.h"

#include "SIO_functions.h"
#include "SIO_block.h"

namespace SIO{
    
  unsigned int SIOCalHitHandler::read(SIO_stream* stream, 
				      LCIOObject** objP,
				      unsigned int flag,
				      unsigned int vers ){
    unsigned int status ; 
	
    // create a new object :
    CalorimeterHitIOImpl* hit  = new CalorimeterHitIOImpl ;
    *objP = hit ;
	
	
    SIO_DATA( stream ,  &(hit->_en) , 1  ) ;
    SIO_DATA( stream ,  hit->_pos  , 3 ) ;
	
    // if we want to point at calo hits we need to add a ptag:
    //  SIO_PTAG( stream , dynamic_cast<const CalorimeterHit*>(hit) ) ;
    SIO_PNTR( stream , &(hit->_mcp) ) ;
	
    return ( SIO_BLOCK_SUCCESS ) ;
	
  }
    
    
  unsigned int SIOCalHitHandler::write(SIO_stream* stream, 
				       const LCIOObject* obj,
				       unsigned int flag ){
	
    unsigned int status ; 
	
    // this is where we gave up type safety in order to
    // simplify the API and the implementation
    // by having a common collection of objects
	
    const CalorimeterHit* hit = dynamic_cast<const CalorimeterHit*>(obj)  ;
	
    LCSIO_WRITE( stream, hit->getEnergy()  ) ;
	
    // as SIO doesn't provide a write function with const arguments
    // we have to cast away the constness hope for the best 
    float* pos = const_cast<float*> ( hit->getPosition() ) ; 
    SIO_DATA( stream,  pos , 3 ) ;
	
    const MCParticle* part = hit->getMCParticle() ;
    //  SIO_PTAG( stream , dynamic_cast<const CalorimeterHit*>(hit) ) ;
    SIO_PNTR( stream , &part ) ;
	
    return ( SIO_BLOCK_SUCCESS ) ;
	
  }

}; // namespace
