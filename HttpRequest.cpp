#include <string>
#include <vector>
// TODO make header files and use proper includes

enum HttpMethod {
  GET,
  POST
};

class HttpRequest: public HttpMessage {
public:
  HttpRequest() {}

  virtual void decodeFirstLine(std::vector<char> line) {
    /*
      Sample Http Request

      GET /index.html HTTP/1.1\r\n   <----   decode this
      User-Agent: Wget/1.15 (linux-gnu)\r\n
      Accept: * / * \r\n   <---- no space between * and / but added space to avoid messing up comment block
      Host: localhost:4000\r\n
      Connection: Keep-Alive\r\n
      \r\n


      GET /index.html HTTP/1.1\r\n
     */

    //must begin with method
    bool foundFirstSpace = false;
    bool foundSecondSpace = false;
    std::string method, url, version;
    for (int i = 0; i < line.size(); i++) {

      if (line[i] == ' ') {
	if (!foundFirstSpace)
	  foundFirstSpace = true;
	else
	  foundSecondSpace = true;

	continue;
      }
      if (foundSecondSpace)
	version += line[i];
      else if (foundFirstSpace)
	url += line[i];
      else
	method += line[i];
    }
    setMethod(method);
    setUrl(url);
    setVersion(version);
  }
  
  void setUrl(std::string url) {
    m_url = url;
    if (url.size() >= 4 && url.substr(0,4) == "http")
      m_isAbsoluteUrl = true;
    else
      m_isAbsoluteUrl = false;
  }
  std::string getUrl() {
    return m_url;
  }

  void setMethod(HttpMethod method) {
    m_method = method;
  }
  HttpMethod getMethod() {
    return m_method;
  }
private:
  std::string m_url;
  bool m_isAbsoluteUrl;
  HttpMethod m_method;
  
};
