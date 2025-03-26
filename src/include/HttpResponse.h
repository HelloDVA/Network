#include<string>
#include<map>

class HttpResponse{
	public:
		HttpResponse();
		~HttpResponse();
		void MakeResponse(int status_code, std::string path, std::string version);
		void MakeErrorResponse(std::string version);
		std::string ToString() const;
	private:
		int status_code_;
		std::string path_;
		std::string version_;
		std::string body_;
		std::string RESOURCE_DIR;

		std::string status_message_;
		std::string content_type_;
		std::map<std::string, std::string> headers_;
		static const std::map<int, std::string> status_messages_;

};

