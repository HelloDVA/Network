#include"HttpResponse.h"
#include"Log.h"
#include<iostream>
#include<fstream>
#include<sstream>

const std::map<int, std::string> HttpResponse::status_messages_ = {
	{200, "OK"},
	{404, "Not Found"},
	{500, "Internal Server Error"}
};

HttpResponse::HttpResponse(){
	RESOURCE_DIR = "../resources/me"; 
}

HttpResponse::~HttpResponse(){}

void HttpResponse::MakeResponse(int status_code, std::string path, std::string version){
    path_ = RESOURCE_DIR + path;
	status_code_ = status_code;

	//test
	std::cout << "resource path:" << path_ << std::endl;

    // according to the path to make the body
    std::ifstream file(path_);
    if (file.is_open()) {
        std::ostringstream buffer;
        buffer << file.rdbuf();
        body_ = buffer.str();
        file.close();
    }
	else{
		MakeErrorResponse(version_);		
	}
    status_message_ = status_messages_.at(status_code_);
    content_type_ = "text/html";
    headers_["Connection"] = "close";
}

void HttpResponse::MakeErrorResponse(std::string version){
    path_ = RESOURCE_DIR + "/404.html";
    version_ = version;
	status_code_ = 404;

    // according to the path to make the body
    std::ifstream file(path_);
    if (file.is_open()) {
        std::ostringstream buffer;
        buffer << file.rdbuf();
        body_ = buffer.str();
        file.close();
    }
	else{
    Log::getlog() -> WriteLog(LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, "open error page error");
	}
    status_message_ = status_messages_.at(status_code_);
    content_type_ = "text/html";
    headers_["Connection"] = "close";
}


std::string HttpResponse::ToString() const{
    std::string response;
    response += version_ + " " + std::to_string(status_code_) + " " + status_message_ + "\r\n";
    response += "Content-Type: " + content_type_ + "\r\n";
    for (const auto& header : headers_) {
        response += header.first + ": " + header.second + "\r\n";
    }
    response += "\r\n";
    response += body_;
    return response;
}
