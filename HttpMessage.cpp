#include <string>
#include <map>

class HttpMessage {
public:
  HttpMessage() {}
  
  virtual void decodeFirstLine(std::vector<char> line) = 0;

  void setHeader(std::string key, std::string value) {
    m_header[key] = value;
  }
  std::string getHeader(std::string key) {
    if (m_header.find(key) == m_header.end())
      return "";
    return m_header[key];
  }
  
private:

  std::map<string, string> m_header;
  
};
