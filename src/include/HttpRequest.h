#include<string>
#include<memory>
#include<map>

class Buffer;

class HttpRequest{
	 private:
		std::string method_;
		std::string path_;
		std::string version_;

		std::map<std::string, std::string> header_;

		std::string body_;

	
	public:
		HttpRequest();
		~HttpRequest();
		                                               
		bool Parse(std::unique_ptr<Buffer> buffer);		

		std::string getversion();

};
