#include "globals.h"
#include <boost/algorithm/string.hpp>
#include <boost/json.hpp>
#include "sql.h"

int webfinger_cgi()
{
    auto acct = (*cgi)("resource");
    if (boost::starts_with(acct, "acct:"))
        boost::erase_head(acct, 5);

    Cursor c("SELECT * FROM actors WHERE email = :email");
    c.bind(":email", acct);
    int i = c.step();

    if (i != SQLITE_ROW)
    {
        std::cout << "Status: 404\n\n";
        return 0;
    }

    boost::json::object properties;
    if (c.has("name"))
        properties["name"] = c.get("name");

    boost::json::array links;

    std::cout << '\n'
              << boost::json::object{
                     {"subject",    "acct:" + acct},
                     {"properties", properties    },
                     {"links",      links         }
    };

    return 1;
}
