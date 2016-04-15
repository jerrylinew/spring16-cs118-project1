#include <string>
#include <vector>

class HttpRequest: public HttpMessage {
public:
  HttpRequest() {}

  virtual void decodeFirstLine(std::vector<char> line) {
    /*
      Sample Http Request

      GET /index.html HTTP/1.1\r\n
      User-Agent: Wget/1.15 (linux-gnu)\r\n
      Accept: * / * \r\n   <---- no space between * and / but added space to avoid messing up comment block
      Host: localhost:4000\r\n
      Connection: Keep-Alive\r\n
      \r\n
     */
    
    
    
  }
  
  void setUrl(std::string url) {
    m_url = url;
    if (url.size() >= 4 && url.substr(0,4) == "http")
      m_isAbsoluteUrl = true;
    else
      m_isAbsoluterUrl = false;
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
