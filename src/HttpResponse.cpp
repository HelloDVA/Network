#include"HttpResponse.h"
#include<iostream>
#include<fstream>
#include<sstream>

const std::map<int, std::string> HttpResponse::status_messages_ = {
	{200, "OK"},
	{404, "Not Found"},
	{500, "Internal Server Error"}
};

HttpResponse::HttpResponse(){}

HttpResponse::~HttpResponse(){}

void HttpResponse::MakeResponse(std::string path, std::string version){
    path_ = "/resources" + path;
    version_ = version;

    // according to the path to make the body
    std::ifstream file(path_);
    if (file.is_open()) {
        std::ostringstream buffer;
        buffer << file.rdbuf();
        body_ = buffer.str();
        file.close();
        status_code_ = 200;
    }
    else{
        std::ifstream error_file("404.html");
        std::ostringstream buffer;
        buffer << file.rdbuf();
        body_ = buffer.str();
        file.close();
        status_code_ = 404;
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
	std::cout << body_;
    return response;
}
