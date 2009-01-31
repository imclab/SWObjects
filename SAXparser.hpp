/* SAXparser.hpp: SAXparser interface object for SWObjects.
 * I needed to abstract the different parsers, so why not use a popular
 * interface?

 * $Id: SWObjects.hpp,v 1.26 2008-12-04 23:00:15 eric Exp $
 */

#pragma once
#include "SWObjects.hpp"

namespace w3c_sw {

    class SWSAXparser {
    protected:
	static std::string qName(const char* prefix, const char* localName) {
	    return (prefix && prefix[0] ? std::string((const char*)prefix) + '~' : std::string("")) + (const char*)localName;
	}
	static std::string prefix(std::string qname) {
	    size_t f = qname.find(':');
	    if (f == std::string::npos)
		return std::string("");
	    return qname.substr(0, f);
	}
	class Attributes {
	public:
	    Attributes () {  }
	    virtual ~Attributes () {  }
	    virtual size_t getLength() = 0;
	    virtual std::string getLocalName(size_t i) = 0;
	    virtual std::string getURI(size_t i) = 0;
	    virtual std::string getQName(size_t i) = 0;
	    virtual std::string getValue(std::string uri, std::string localName) = 0;
	};
    public:
	SWSAXparser () {  }
	virtual ~SWSAXparser () {  }
	virtual void parse(const char* file) = 0;
	void startElement (std::string uri,
			   std::string localName,
			   std::string qName,
			   Attributes* attrs) {
	    std::cout << "<" << qName << " _:ns=\"" << uri << "|" << localName << "\"";
	    size_t attrCount = attrs->getLength();
	    for (size_t i = 0; i < attrCount; ++i) {
		std::cout << std::endl << "    " << attrs->getQName(i) << "=\"" << attrs->getValue(attrs->getURI(i), attrs->getLocalName(i)) << "\"";
	    }
	    std::cout << ">" << std::endl;
	}
	void endElement (std::string uri,
			 std::string localName,
			 std::string qName) {
	    std::cout << "</" << qName << " _:ns=\"" << uri << "|" << localName << "\">" << std::endl;;
	}
	void characters (const char ch[],
			 int start,
			 int length) {
	    std::cout << std::string(ch, start, length);
	}

	void error(const char * msg, ...) {
	    va_list args;
	    va_start(args, msg);
	    error( msg, args );
	    va_end(args);
	    throw("SWSAXparser exception");
	}

	void error(const char* msg, va_list args) {
	    vprintf(msg, args);
	    throw("SWSAXparser exception");
	}

	void warning(const char * msg, ...) {
	    va_list args;
	    va_start(args, msg);
	    warning( msg, args );
	    va_end(args);
	}

	void warnting(const char* msg, va_list args) {
	    vprintf(msg, args);
	}

    };

}

