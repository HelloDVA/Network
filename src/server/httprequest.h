#include<string>
#include<memory>
#include<map>

class HttpRequest{
	private:
		std::string method_;
		std::string path_;
		std::string version_;
		std::map<std::string, std::string> headers_;
		std::string body_;

	public:
		HttpRequest() = default;
		~HttpRequest() = default;
		void Parse(const std::string& message);		
		std::string getversion() const { return version_;}
		std::string getpath() const { return path_; }
		std::string getmethod() const {return method_; }
		std::string getbody() const { return body_; }
		std::string getheader(std::string key) const { return headers_.at((key)); }
};
