#include <sstream>
#include <fstream>
#include <regex>

#include "httpprocess.h"
#include "httprequest.h"
#include "httpresponse.h"

const std::string RESOURCE_DIR = "../resources";

HttpResponse HttpProcess::Process(const HttpRequest& request) {
    std::string method = request.getmethod();
    std::string path = request.getpath(); 
    if (path == "/websocket") {
        
    }
    // get http information and choose action.
    else if (method == "GET") {
        return HandleGet(request);
    }

    if (path == "/login" && method == "POST") {
        return HandleLogin(request);
    }
    return HandleNone(request);
}

 HttpResponse HttpProcess::HandleGet(const HttpRequest& request) {
    std::string path = request.getpath();
    path = RESOURCE_DIR + path + ".html";

    HttpResponse response;
    response.setversion(request.getversion());
    response.setheader("Connection", request.getheader("Connection"));
    response.setheader("Content-Type", response.GetMimeType(path));


   	std::ifstream file(path);
   	if (file.is_open()) {
       	std::ostringstream buffer;
       	buffer << file.rdbuf();
        std::string response_body = buffer.str();
       	file.close();
        response.setstatus(200);
        response.setbody(response_body);
   	} else {
        response.setstatus(404);
	}
    return response;
}

HttpResponse HttpProcess::HandleLogin(const HttpRequest& request) {
    HttpResponse response;
    response.setversion(request.getversion());
    response.setheader("Connection", request.getheader("Connection"));

    ParseUser(request.getbody());
	// ConnectionPool init in server
	/* MYSQL* conn = ConnectionPool::getinstance().GetConnection(); */
	
	/* std::string username = url_data_["username"]; */
	/* std::string userpwd; */
	/* std::string query = "SELECT * FROM user WHERE username = '" + username + "'"; */

	/* Database database(conn); */
	/* Database::Result rows_result = database.Query(query); */

	/* if(rows_result.empty()){ */
	/* 	MakeErrorResponse(500, version_); */
	/* } */

	/* Database::Row row = database.Query(query).front(); */

	if(user_data_["password"] == "123321"){
        std::string body = "/wzq";
        response.setbody(body);
        response.setstatus(200);
	}
	else {
        response.setstatus(401);
    }

    return response;
	// return connection to connectionpool
	//database.Close();
}

void HttpProcess::ParseUser(const std::string& body) {
	user_data_.clear();

	std::regex re("([^&=]+)=([^&=]+)");
	auto words_begin = std::sregex_iterator(body.begin(), body.end(), re);
	auto words_end = std::sregex_iterator();

	// 遍历所有匹配的 key=value 对
	for (auto it = words_begin; it != words_end; ++it) {
		std::string key = it->str(1);  // 解码 key
	    std::string value = it->str(2);  // 解码 value
		user_data_[key] = value;
	}
}

HttpResponse HttpProcess::HandleNone(const HttpRequest& request) {
    HttpResponse response;
    response.setversion(request.getversion());
    response.setheader("Connection", request.getheader("Connection"));

    response.setstatus(404);
    return response;
}
