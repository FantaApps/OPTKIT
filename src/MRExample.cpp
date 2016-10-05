/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   10/05/16 - Creation
 *
**/

using namespace std; 

#include <algorithm>
#include <limits>
#include <string>
  
#include  "stdint.h"  // <--- to prevent uint64_t errors! 
 
#include "Pipes.hh"
#include "TemplateFactory.hh"
#include "StringUtils.hh"
 
using namespace std;

class WordCountMapper : public HadoopPipes::Mapper {
public:
    // constructor: does nothing
    WordCountMapper( HadoopPipes::TaskContext& context ) {
    }

    // map function: receives a line, outputs (word,"1")
    // to reducer.
    void map( HadoopPipes::MapContext& context ) {
        //--- get line of text ---
        string line = context.getInputValue();

        //--- split it into words ---
        vector< string > words =
            HadoopUtils::splitString( line, " " );

        //--- emit each word tuple (word, "1" ) ---
        for ( unsigned int i=0; i < words.size(); i++ ) {
            context.emit( words[i], HadoopUtils::toString( 1 ) );
        }
    }
};

class WordCountReducer : public HadoopPipes::Reducer {
public:
    // constructor: does nothing
    WordCountReducer(HadoopPipes::TaskContext& context) {
    }

    // reduce function
    void reduce( HadoopPipes::ReduceContext& context ) {
        int count = 0;

        //--- get all tuples with the same key, and count their numbers ---
        while ( context.nextValue() ) {
            count += HadoopUtils::toInt( context.getInputValue() );
        }

        //--- emit (word, count) ---
        context.emit(context.getInputKey(), HadoopUtils::toString( count ));
    }
};

/**
 * Main function of OPTKIT
**/
int32_t main(int32_t argc , const char *argv[])
{
    return HadoopPipes::runTask(HadoopPipes::TemplateFactory<WordCountMapper, WordCountReducer>()); 
}

