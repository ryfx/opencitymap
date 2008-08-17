
#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

#include "mapModel.h"

#define STORE_FILE_FORMAT "yyyyMMdd_hhmm"


/**
  * class DataInterface
  */

class DataInterface
{
    public:
        

        /**
        * @return MapModel *
        */
        virtual MapModel * load( QString fileName ) = 0;


        /**
        * @param  model
        */
        virtual void store( MapModel  *model ) = 0;
        
        
};

#endif // DATAINTERFACE_H
