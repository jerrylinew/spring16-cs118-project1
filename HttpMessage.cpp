#include <string>
#include <map>


const std::string LINE_DELIMITER = "\r\n";
const std::string WORD_DELIMITER = " ";
const std::string HEADER_DELIMITER = ":";

enum HttpVersion {
  "1.0",
  "1.1"
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
    
    std::vector<char> key, value;
    bool foundDelimiter = false;
    for (int i = 0; i < line.size(); i++) {
      if (i+1 < line.size() && line[i] == '\r' && line[i+1] == '\n')
	break;
	  
      if (line[i] == ':') {
	foundDelimiter = true;
	if (i+1 < line.size() && line[i+1] == ' ')
	  i = i+1;
      }
	  
      if (foundDelimiter)
	key.push_back(line[i]);
      else
	value.push_back(line[i]);
    }
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
  std::map<string, string> m_header;
  std::vector<char> m_payload;
};
