#include "nova/guest/apt.h"

#include <boost/optional.hpp>
#include "nova/log.h"
#include <sstream>
#include <string>

using nova::JsonArray;
using nova::JsonArrayPtr;
using nova::JsonObject;
using nova::JsonObjectPtr;
using nova::Log;
using boost::optional;
using std::string;
using std::stringstream;

namespace nova { namespace guest {

AptMessageHandler::AptMessageHandler() {
}

JsonObjectPtr AptMessageHandler::handle_message(JsonObjectPtr input) {
    string method_name;
    input->get_string("method", method_name);
    JsonObjectPtr args = input->get_object("args");

    std::stringstream rtn;

    try {
        if (method_name == "install") {
            apt::install(args->get_string("package_name"),
                         args->get_int("time_out"));
            rtn << "{}";
        } else if (method_name == "remove") {
            apt::remove(args->get_string("package_name"),
                        args->get_int("time_out"));
            rtn << "{}";
        } else if (method_name == "version") {
            const char * package_name = args->get_string("package_name");
            optional<string> version = apt::version(package_name);
            rtn << "{'version':'" << (version ? version.get() : "null") << "'}";
        } else {
            JsonObjectPtr rtn;
            return rtn;
        }
    } catch(const AptException & ae) {
        rtn << "{ 'error':'" << ae.what() << "' }";
    }

    JsonObjectPtr rtn_obj(new JsonObject(rtn.str().c_str()));
    return rtn_obj;
}

} }  // end namespace nova::guest