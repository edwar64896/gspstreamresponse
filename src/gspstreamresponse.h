#ifndef GSP_STREAM_RESPONSE
#define GSP_STREAM_RESPONSE

#include "Arduino.h"
#include "gspgrouped.h"
#include "nonstd.h"

#define GSP_SR_MODE_REPLACE 1
#define GSP_SR_MODE_CALLBACK 2
#define GSP_SR_MODE_CALLBACK_NONSTD 3


class gspStreamResponse: public gspGrouped {

    public:

        static gspStreamResponse * makeOne(
                            const char* _szInput /*Parser input - this is the string we look for*/, 
                            uint8_t _nChars /*number of characters to pull from the Stream stream after the parser input has passed */,
                            nonstd::function<void (char *)> _callback /*callback to invoke upon successful parse*/
        ) {
            gspStreamResponse * instance = new gspStreamResponse(_szInput,_nChars,_callback);
            gspGrouped::register_instance(instance);
            return instance;
        }

//        gspStreamResponse(  
//            const char* szInput /*Parser input - this is the string we look for*/, 
//            uint8_t nChars /*number of characters to pull from the Stream stream after the parser input has passed */,
//            void (* callback)(char *) /*callback to invoke upon successful parse*/
//        );

        gspStreamResponse(  
            const char* szInput /*Parser input - this is the string we look for*/, 
            uint8_t nChars /*number of characters to pull from the Stream stream after the parser input has passed */,
            nonstd::function<void (char *)> _callback /*callback to invoke upon successful parse*/
        );

        gspStreamResponse(  
            const char* szInput /*Parser input - this is the string we look for*/, 
            uint8_t nChars /*number of characters to pull from the Stream stream after the parser input has passed */,
            char** /*reference to fill with result*/
        );

        gspStreamResponse();
        ~gspStreamResponse();

        bool check();
        void reset();
        char * getLastResponse();

        void update();

        static void checkAll() {
            gspGrouped::checkAll(gspStreamResponse::firstInstance);
        }

    protected:

        void setFirstInstance(gspGrouped * fi) {gspStreamResponse::firstInstance = fi;}
        gspGrouped * getFirstInstance() {return gspStreamResponse::firstInstance;}
        static gspGrouped * firstInstance;
        nonstd::function<void (char *)> cbProcessorNonstd;

    private:

        int operationmode=0;

        //void (*cbProcessor)(char *) = nullptr;

        const char* szHeader=nullptr;
        char* szResponse=new char[20];
        uint8_t iCharsToGrab=0;
        uint8_t cursor=0;
        void getChars(uint8_t nChars);
        char * _lastResponse;
        int parseWin=0;

        char ** _replaceMe;

};

#endif
