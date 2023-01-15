#include "globals.h"
#include <boost/json.hpp>
#include "sql.h"
#include "response.h"

void actor_cgi(Response& res)
{
    auto actor = (*cgi)("actor");

    Cursor c("SELECT * FROM actors WHERE email = :actor");
    c.bind(":actor", actor);
    if (c.step() != SQLITE_ROW)
    {
        res.setStatus(404);
        return;
    }

    auto server = getProp("server");
    res << boost::json::object{
        {"@context",
         boost::json::array{"https://www.w3.org/ns/activitystreams",
                "https://w3id.org/security/v1"}              },
        {"id",           server + "?cmd=actor&actor=" + actor},
        {"type",         "Person"                            },
        {"discoverable", true                                },
    };
}
