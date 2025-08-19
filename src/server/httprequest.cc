
#include<sstream>


#include"httprequest.h"

void HttpRequest::Parse(const std::string& message) {
   	if(message.size() == 0)
    	return;

   	std::istringstream request_stream(message);

    // process the request line
   	std::string line;
    std::getline(request_stream, line);
    std::istringstream line_stream(line);
    line_stream >> method_ >> path_ >> version_;

    // process the request header
    headers_.clear();
    while(std::getline(request_stream, line) && line != "\r"){
        std::istringstream header_stream(line);
        std::string key, value;
        if(std::getline(header_stream, key, ':') && std::getline(header_stream, value)){
            headers_[key] = value.substr(value.find_first_not_of(" "));
            if(key == "Upgrade"){
                path_ = "/websocket";
            }
        } 
    }

    //process the request body
    if(method_ == "POST" || method_ == "PUT"){
        auto content_length_it = headers_.find("Content-Length");
        if(content_length_it != headers_.end()){
            size_t content_length = std::stoul(content_length_it->second);
            body_.resize(content_length);
            request_stream.read(&body_[0], content_length);
        }
    }
};

