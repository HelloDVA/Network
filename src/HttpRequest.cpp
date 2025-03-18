#include"HttpRequest.h"
#include"Buffer.h"
#include"Log.h"
#include<sstream>
#include<iostream>


HttpRequest::HttpRequest(){}

HttpRequest::~HttpRequest(){}

bool HttpRequest::Parse(std::unique_ptr<Buffer> buffer){
    // verify the buffer size
   if(buffer -> Size() == 0)
        return false;
	
    std::istringstream request_stream(buffer -> getbuffer());

    std::string line;
    if(!std::getline(request_stream, line)){
        Log::getlog()->WriteLog(LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, "Failed to parse the request line");
        return false;
    }

    // process the request line
    std::istringstream line_stream(line);
    line_stream >> method_ >> path_ >> version_;

    // process the request header
    while(std::getline(request_stream, line) && line != "\r"){
        std::istringstream header_stream(line);
        std::string key, value;
        if(std::getline(header_stream, key, ':') && std::getline(header_stream, value)){
            header_[key] = value.substr(value.find_first_not_of(" "));
        } 
    }

    //process the request body
    if(method_ == "POST" || method_ == "PUT"){
        auto content_length_it = header_.find("Content-Length");
        if(content_length_it != header_.end()){
            size_t content_length = std::stoul(content_length_it->second);
            body_.resize(content_length);
//            request_stream.read(body_.data(), content_length);
        }
    } 
    return true;
}

std::string HttpRequest::getversion(){
	return version_;
}
