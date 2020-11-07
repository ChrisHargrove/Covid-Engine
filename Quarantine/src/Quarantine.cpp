#include <Covid.h>

class Quarantine: public Covid::Application
{
public:
    Quarantine() 
    {
    }

    ~Quarantine()
    {
    }

private:

};

//Defines that we are going to use this application as our entry point.
ENTRY_POINT(Quarantine);