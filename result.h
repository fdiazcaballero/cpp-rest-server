
#include <cpprest/json.h>
using namespace web;

class Result
{
public:
    std::string Status;
    std::string Data;
    int Test;

    Result(std::string status, std::string data, int test);

    json::value ToJSON() const;

    ~Result(void);
};

