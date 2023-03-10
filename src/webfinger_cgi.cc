#include "globals.h"
#include <boost/algorithm/string.hpp>
#include <boost/json.hpp>
#include "sql.h"
#include "response.h"

void webfinger_cgi(Response& res)
{
    auto acct = (*cgi)("resource");
    if (boost::starts_with(acct, "acct:"))
        boost::erase_head(acct, 5);

    Cursor c("SELECT * FROM actors WHERE email = :email");
    c.bind(":email", acct);
    int i = c.step();

    if (i != SQLITE_ROW)
    {
        res.setStatus(404);
        return;
    }

    auto env = cgi->getEnvironment();
    auto server = getProp("server");

    boost::json::object properties;
    if (c.has("name"))
        properties["name"] = c.get("name");

    boost::json::array links{
        boost::json::object{{"rel", "self"},
                            {"type", "application/activity+json"},
                            {"href", server + "?cmd=actor&actor=" + acct}}
    };

    if (c.has("homepage"))
        links.emplace_back(boost::json::object{
            {"rel",  "http://webfinger.net/rel/profile-page"},
            {"type", "text/html"                            },
            {"href", c.get("homepage")                      }
        });

    res << boost::json::object{
        {"subject",    "acct:" + acct},
        {"properties", properties    },
        {"links",      links         }
    };
}
