/* test_RDFaParser.cpp - test RDFaParser.hpp
 *
 * $Id: test_RDFaParser.cpp,v 1.5 2008-12-04 22:37:09 eric Exp $
 */

/* test graph-matching.
 *
 */

#define BOOST_TEST_MODULE RDFaParser

#include <map>
#include <vector>
#include "SWObjects.hpp"
#include "TurtleSParser/TurtleSParser.hpp"
#include "RDFaParser.hpp"

#if XML_PARSER == SWOb_LIBXML2
  #include "../interface/SAXparser_libxml.hpp"
  w3c_sw::SAXparser_libxml P;
#elif XML_PARSER == SWOb_EXPAT1
  #include "../interface/SAXparser_expat.hpp"
  w3c_sw::SAXparser_expat P;
#elif XML_PARSER == SWOb_MSXML3
  #include "../interface/SAXparser_msxml3.hpp"
  w3c_sw::SAXparser_msxml3 P;
#else
  #warning DAWG tests require an XML parser
#endif

#if HTTP_CLIENT == SWOb_ASIO
  #include "../interface/WEBagent_boostASIO.hpp"
  w3c_sw::WEBagent_boostASIO WebClient;
#else /* ! HTTP_CLIENT == SWOb_ASIO */
  #warning unable to test RDFa over HTTP
#endif /* ! HTTP_CLIENT == SWOb_ASIO */

/* Keep all inclusions of boost *after* the inclusion of SWObjects.hpp
 * (or define BOOST_*_DYN_LINK manually).
 */
#include <boost/test/unit_test.hpp>

using namespace w3c_sw;

POSFactory F;
TurtleSDriver turtleParser("", &F);
RDFaParser GRDFaParser("", &F, &P);

BOOST_AUTO_TEST_CASE( APC ) {
    DefaultGraphPattern tested;
    IStreamContext html("RDFaParser/APC.html");
    GRDFaParser.setBase("APC.html");
    GRDFaParser.parse(&tested, html);

    DefaultGraphPattern expected;
    turtleParser.setGraph(&expected);
    turtleParser.setBase("APC.html");
    IStreamContext reference("RDFaParser/APC.ttl", IStreamContext::FILE);
    turtleParser.parse(reference);
    turtleParser.clear(""); // clear out namespaces and base URI.
    BOOST_CHECK_EQUAL(tested, expected);
}

BOOST_AUTO_TEST_CASE( gabab ) {
    DefaultGraphPattern tested;
    const char* gabab = "http://hcls.deri.org/atag-data/gabab_example.html";
    IStreamContext html("RDFaParser/gabab.html", IStreamContext::FILE);
    GRDFaParser.setBase(gabab);
    try {
	GRDFaParser.parse(&tested, html);
    } catch (std::string e) {
	throw(std::string("exception while parsing RDFaParser/gabab.html: ").append(e));
    }

    DefaultGraphPattern expected;
    turtleParser.setGraph(&expected);
    turtleParser.setBase(gabab);
    IStreamContext reference("RDFaParser/gabab.ttl", IStreamContext::FILE);
    turtleParser.parse(reference);
    turtleParser.clear(""); // clear out namespaces and base URI.
    BOOST_CHECK_EQUAL(tested, expected);
}

/* invoke with e.g. -DHTTP_RDFa_test=http://mouni.local/RDFa-0.html */
#if HTTP_CLIENT != SWOb_DISABLED && defined(HTTP_RDFa_test)
BOOST_AUTO_TEST_CASE( by_http ) {
    DefaultGraphPattern tested;
    std::string s(WebClient.get(HTTP_RDFa_test));
    BOOST_CHECK_EQUAL(WebClient.getMediaType().substr(0, 9), "text/html");
    GRDFaParser.parse(&tested, s.begin(), s.end(), HTTP_RDFa_test);

    DefaultGraphPattern expected;
    turtleParser.setGraph(&expected);
    turtleParser.setBase(F.getURI(HTTP_RDFa_test));
    turtleParser.parse_file("RDFa-0.ttl");
    turtleParser.clear(""); // clear out namespaces and base URI.
    BOOST_CHECK_EQUAL(tested, expected);
}
#endif /* HTTP_CLIENT != SWOb_DISABLED */

