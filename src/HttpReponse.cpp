#include"HttpResponse.h"

static const std::map<int, std::string> status_messages = {
    {200, "OK"},
    {404, "Not Found"},
    {500, "Internal Server Error"}
};

HttpResponse::HttpResponse(){}

HttpResponse::~HttpResponse(){}

void HttpResponse::MakeResponse(int status_code, std::string version, std::string body){
    status_code_ = status_code;

    status_message_ = status_messages.at(status_code);

    content_type_ = "text/html";

    headers_["Connection"] = "close";

    body_ = body;
}

std::string HttpResponse::ToString() const{ 
    std::string response;
    // response line
    response += version_ + std::to_string(status_code_) + " " + status_message_ + "\r\n";
    // response headers
    response += "Content-Type: " + content_type_ + "\r\n";
    for (const auto& header : headers_) {
        response += header.first + ": " + header.second + "\r\n";
    }
    response += "\r\n";
    //response body
    response += body_;
    return response;
}