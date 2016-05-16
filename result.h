
#include <cpprest/json.h>
using namespace web;

class Result
{
public:
    std::string Status;
    std::string Category;

    Result(std::string status, std::string category);

    json::value ToJSON() const;

    ~Result(void);
};

