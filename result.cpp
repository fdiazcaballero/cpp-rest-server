
#include "result.h"
using namespace utility;

Result::Result(std::string status, std::string category) : Status(status), Category(category)
{
}

Result::~Result(void)
{
}

json::value Result::ToJSON() const
{
    json::value res = json::value::object();
    res["Status"] = json::value::string(conversions::to_string_t(Status));
    res["Category"] = json::value::string(conversions::to_string_t(Category));
    return res;
}
