#include <string>

class HttpRequest {
public:
  HttpRequest() {
    
  }
  void setUrl(string url) {
    m_url = url;
  }

  void setMethod() {

  }
  
private:
  string m_url;
  
};
