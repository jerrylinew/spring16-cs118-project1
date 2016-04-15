#include <string>
#include <vector>
#include <map>


const std::string LINE_DELIMITER = "\r\n";
const char WORD_DELIMITER = ' ';
const char HEADER_DELIMITER = ':';

enum HttpVersion {
  v1_0,
  v1_1
};

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

  HttpVersion getVersion() {
    return m_version;
  }

  void decodeHeaderLine(std::vector<char> line) {
    /*
      Sample Header Line
      Connection: close\r\n
     */
    
    std::string key, value;
    bool foundDelimiter = false;
    for (int i = 0; i < line.size(); i++) {
      if (i+1 < line.size() && line[i] == LINE_DELIMITER[0] && line[i+1] == LINE_DELIMITER[1])
	break;
	  
      if (line[i] == HEADER_DELIMITER) {
	foundDelimiter = true;
	continue;
      }
	  
      if (foundDelimiter)
	key += line[i];
      else
	value += line[i];
    }

    //TODO: strip away beginning spaces for key and value
    
    setHeader(key, value);
  }

  void setPayLoad(std::vector<char> blob) {
    m_payload = blob;
  }

  std::vector<char> getPayload() {
    return m_payload;
  }
    
private:
  HttpVersion m_version;
  std::map<std::string, std::string> m_header;
  std::vector<char> m_payload;
};
