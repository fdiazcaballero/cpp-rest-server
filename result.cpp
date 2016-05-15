
#include "result.h"
using namespace utility;

Result::Result(std::string status, std::string data, int test) : Status(status), Data(data), Test(test)
{
}

Result::~Result(void)
{
}

json::value Result::ToJSON() const
{
    json::value res = json::value::object();
    res["Status"] = json::value::string(conversions::to_string_t(Status));
    res["Data"] = json::value::string(conversions::to_string_t(Data));
    res["Test"] = json::value::number(Test);
    return res;
}
