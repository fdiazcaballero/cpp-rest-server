//test
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include "result.h"
#include <regex>
#include "boost/program_options.hpp" 

using namespace web;
using namespace web::http;
using namespace utility;
using namespace web::http::experimental::listener;
using namespace web::http::client;
namespace po = boost::program_options;

http_listener listener;

void handle_get(http_request request);


//initialize the http listener
void initialize(const string_t &address) {

    uri_builder uri(address);

    uri.append_path(U("filter"));


    auto addr = uri.to_uri().to_string();

    listener = http_listener(addr);

    listener.support(web::http::methods::GET, handle_get);

    listener
            .open()
            .then([]() { std::cout << utility::string_t(U("Listening for requests")) << std::endl; })
            .wait();


    return;

}

//shutdown the http listener
void shutdown() {

    listener.close().wait();
    return;

}


bool validate(string_t const &username, string_t const &password)
{
    uri_builder uri("http://check_credentials_url.com");

    // build the query parameters
    auto query = uri
            .append_query("u", username)
            .append_query("p", password)
            .to_string();

  //  call to service
    http_client client(query);
    
    http_response httpResponse = client.request(methods::GET).get();

    return httpResponse.status_code() == status_codes::OK;
	
}

//process the get request 
void handle_get(http_request request) {

    std::smatch result;

    if (std::regex_match(request.request_uri().query(), result, std::regex("^url=.*?(www.*)$"))) {

        if (result.size() < 2)
            request.reply(status_codes::NotImplemented, U("invalid data in uri"));
        else {
            Result p = Result(result[1],"category_test");
            request.reply(status_codes::OK, p.ToJSON());
        }
    }
    else
        request.reply(status_codes::NotImplemented, U("invalid uri"));

}


int main(int argc, char *argv[]) {
    //set default values
    utility::string_t port = U(":9000");
    utility::string_t host = U("http://localhost");


    //get options values
    po::options_description desc("Options");
    desc.add_options()
            ("help", "Help")
            ("port,p", po::value<string_t>(), "set the listener port ")
            ("host,h", po::value<string_t>(), "set the listener uri ");

    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, argv, desc),
                  vm); // can throw

        /** --help option  */
        if (vm.count("help")) {
            std::cout << "Rest webserver help: \n"
            << " > USAGE webserver \n"
            << "      -h[--host] set webserver host - default to 9000 \n"
            << "      -p[--port] set webserver port - default to http://localhost"
            << std::endl << std::endl;

            return 1;
        }

        /** --port option */
        if (vm.count("port")) {
            port = ":";
            port.append(vm["port"].as<string_t>());
        }

        /** --host option  */
        if (vm.count("host")) {
            host = vm["host"].as<string_t>();
        }
    }
    catch (po::error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }
 

    //append the port to the host address
    host.append(port);
    //start the webserver
    initialize(host);

    std::cout << "Press ENTER to Exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    //close the webserver
    shutdown();

    return 0;
}
