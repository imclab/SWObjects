/* SWObjects: components for capturing and manipulating compile trees of RDF
   languages. This should capture all of SPARQL and most of N3 (no graphs as
   parts of an RDF triple).

 * $Id: SWObjects.cpp,v 1.17 2008-12-02 04:57:12 eric Exp $
 */

#include "SWObjects.hpp"
#include "ResultSet.hpp"
#include <string.h>
#include <vector>
#include <set>
#include "SPARQLSerializer.hpp"
#include "SWObjectDuplicator.hpp"
#include "../interface/WEBagent.hpp"

#ifdef _MSC_VER
  #define SET_Variable_CONSTIT_NE(L, R) set_Variable_constit_ne(L, R)
  bool set_Variable_constit_ne (std::set<const w3c_sw::Variable*>::const_iterator l, 
				std::set<const w3c_sw::Variable*>::const_iterator r)
  { return l != r; }
  #define SET_POS_CONSTIT_NE(L, R) set_POS_constit_ne(L, R)
  bool set_POS_constit_ne (std::set<const w3c_sw::TTerm*>::const_iterator l, 
			   std::set<const w3c_sw::TTerm*>::const_iterator r)
  { return l != r; }
#else /* !_MSC_VER */
  #define SET_Variable_CONSTIT_NE(L, R) L != R
  #define SET_POS_CONSTIT_NE(L, R) L != R
#endif /* !_MSC_VER */

namespace w3c_sw {

    const char* NS_xml = "http://www.w3.org/XML/1998/namespace"		;
    const char* NS_xsd = "http://www.w3.org/2001/XMLSchema#"		;
    const char* NS_rdf = "http://www.w3.org/1999/02/22-rdf-syntax-ns#"  ;
    const char* NS_rdfs= "http://www.w3.org/2000/01/rdf-schema#"	;
    const char* NS_srx = "http://www.w3.org/2005/sparql-results#"	;
    const char* NS_dc  = "http://purl.org/dc/terms/"			;
    const char* NS_sadl= "http://www.w3.org/2005/03/saddle/#"		;

void Base::express (Expressor* p_expressor) const {
    p_expressor->base(this, typeid(*this).name());
}

#if defined(SWIG)
    %immutable;
#endif /* defined(SWIG) */
char const * yit = "yacker:implicit-terminal";
#if defined(SWIG)
    %mutable;
#endif /* defined(SWIG) */
std::map<StringException*, std::string> StringException::strs;

} // namespace w3c_sw

/* END yacker-specific test harness */

namespace libwww {
/* copied from libwww's HTParse.c
 * transliterated to c++ using std::string (for reduced performance) - EGP
 */

HTURI::HTURI (std::string name) : DummyHTURI()
{
    schemeP =  hostP =  absoluteP =  relativeP =  fragmentP = false;
    
    size_t p;
    size_t after_scheme = 0;

    /* Look for fragment identifier */
    if ((p = name.find('#')) != std::string::npos) {
	std::string t = name.substr(p+1, name.size()-p-1);
	fragment = t;
	fragmentP = true;
	name.erase(p);
    }
    
    
    if ((p = name.find(' ')) != std::string::npos) name.erase(p++);
    
    for(p=0; p<name.size(); p++) {

	/* 
	** Look for any whitespace. This is very bad for pipelining as it
	** makes the request invalid
	*/
	if (isspace(name[p])) {
	    name.erase(p, 1);
	    p = p-1;
	}
	if (name[p]=='/' || name[p]=='#' || name[p]=='?')
	    break;
	if (name[p]==':') {
		scheme = name.substr(after_scheme, p); /* Scheme has been specified */
		schemeP = true;
		name.erase(0, p+1);
		p = 0-1;

/* The combination of gcc, the "-O" flag and the HP platform is
   unhealthy. The following three lines is a quick & dirty fix, but is
   not recommended. Rather, turn off "-O". */

/*		after_scheme = p;*/
/*		while (*after_scheme == 0)*/
/*		    after_scheme++;*/

		after_scheme = p+1;

		if (scheme=="URL") {
		    scheme.clear();  /* Ignore IETF's URL: pre-prefix */
		    schemeP = false;
		} else break;
	}
    }

    p = after_scheme;
    if (name[p]=='/'){
	if (name[p+1]=='/') {
	    host = name.substr(p+2, name.size());/* host has been specified 	*/
	    hostP = true;
	    name.erase(0, p+2);			/* Terminate scheme 		*/
	    p=host.find('/');	/* look for end of host name if any */
	    if(p != std::string::npos) {
	        host.erase(p);			/* Terminate host */
	        absolute = name.substr(p+1, name.size());/* Root has been found */
		absoluteP = true;
	    }
	} else {
	    absolute = name.substr(p+1, name.size());	/* Root found but no host */
	    absoluteP = true;
	}	    
    } else if (after_scheme < name.size()) {
        relative = name.substr(after_scheme, name.size());
	relativeP = true;
    } else {
	relative.clear(); /* zero for "" */
	relativeP = false;
    }
}
std::string HTParse (std::string name, const std::string* rel, e_PARSE_opts wanted)
{
    // std::cerr << "HTParse(" << name << ", " << (rel ? *rel : std::string("NULL")) << ", " << wanted << ")";
    std::string result;
    //    std::string return_value = 0;
    size_t p;
    std::string scheme;
    std::string relStr(rel ? *rel : "junk");

    if (name.size() == 0) return rel ? *rel : "";
    //if (!relatedName)        /* HWL 23/8/94: dont dump due to NULL */
    //    relatedName = "";
    
    /* Make working copies of input strings to cut up: */
    //len = strlen(aName)+strlen(relatedName)+10;
    //if ((result=(std::string ) HT_MALLOC(len)) == NULL) /* Lots of space: more than enough */
    //	HT_OUTOFMEM("parse space");
    //StrAllocCopy(name, aName);
    //StrAllocCopy(rel, relatedName);
    
    HTURI given(name);

    DummyHTURI* related = rel ? new HTURI(relStr) : new DummyHTURI();
    //result[0]=0;		/* Clear string  */
    scheme = given.hasScheme() ? given.getScheme() : related->getScheme();

    if (wanted & PARSE_scheme)
        if (scheme.size() != 0) {
	    result += scheme;
	    if(wanted & PARSE_punctuation) result += ":";
	}
	
    if (given.hasScheme() && related->hasScheme())/* If different, inherit nothing. */
        if (given.getScheme() != related->getScheme()) {
	    related->clearHost();
	    related->clearAbsolute();
	    related->clearRelative();
	    related->clearFragment();
	}
	
    if (wanted & PARSE_host)
        if(given.hasHost() || related->hasHost()) {
	    if(wanted & PARSE_punctuation) result += "//";
	    result += given.hasHost() ? given.getHost() : related->getHost();
	}
	
    if (given.hasHost() && related->hasHost())  /* If different hosts, inherit no path. */
        if (given.getHost() != related->getHost()) {
	    related->clearAbsolute();
	    related->clearRelative();
	    related->clearFragment();
	}
	
    if (wanted & PARSE_path) {
        if(given.hasAbsolute()) {			/* All is given */
	    if(wanted & PARSE_punctuation) result += "/";
	    result += given.getAbsolute();
	} else if(related->hasAbsolute()) {	/* Adopt path not name */
	    result += "/";
	    result += related->getAbsolute();
	    if (given.hasRelative()) {
		p = result.find('?');	/* Search part? */
		if (p == std::string::npos) p=result.size()-1;
		p = result.rfind('/', p);	/* last / */
		result.erase(p+1);			/* Remove filename */
		result += given.getRelative();		/* Add given one */
	    }
	} else if(given.hasRelative()) {
	    if(related->hasRelative() && result.empty()) {
		std::string r = related->getRelative();
		size_t endOfPath = r.find_last_of("/");
		if (endOfPath != std::string::npos)
		    result += r.substr(0, endOfPath+1);
	    }
	    result += given.getRelative();		/* what we've got */
	} else if(related->hasRelative()) {
	    result += related->getRelative();
	} else {  /* No inheritance */
	    result += "/";
	}
    }
		
    if (wanted & PARSE_view)
	if(given.hasFragment() || related->hasFragment()) {
	    if(given.hasAbsolute() && given.hasFragment()) {   /*Fixes for relURLs...*/
		if(wanted & PARSE_punctuation) result += "#";
		result += given.getFragment(); 
	    } else if (given.hasFragment()) {
		if(wanted & PARSE_punctuation) result += "#"; // differs from HTParse.c:202-206
		result += given.getFragment(); 
	    }
	}

    delete related;
    // std::cerr << " => " << result;
    // if (rel)
    // 	std::cerr << " (rel: " << *rel << ")";
    // std::cerr << "\n";
    return result;		/* exactly the right length */
}

} // namespace libwww

namespace w3c_sw {

MediaTypeMap StreamContextMediaTypes::MediaTypes;

template<class T>
StreamContext<T>::StreamContext (std::string nameStr, T* def, e_opts opts,
				 const char* p_mediaType, SWWEBagent* webAgent,
				 std::ostream** debugStream)
    : nameStr(nameStr), malloced(true), p(NULL)
{
    if (opts & STRING) {
	p = new std::stringstream(nameStr);
    } else if (!(opts & FILE) && webAgent != NULL && !nameStr.compare(0, 5, "http:")) {
	if (debugStream != NULL && *debugStream != NULL)
	    **debugStream << "reading web resource " << nameStr << std::endl;
	std::string s(webAgent->get(nameStr.c_str()));
	mediaType = webAgent->getMediaType().c_str();
	p = new std::stringstream(s); // would be nice to use webAgent stream, or have a callback.
    } else if ((opts & STDIO) && nameStr == "-") {
	p = def;
	malloced = false;
    } else {
	/* Remove file://[^/]+ . */
	if (nameStr.substr(0, 7) == "file://") {
	    size_t slash = nameStr.find_first_of('/', 7);
	    nameStr = nameStr.substr(slash);
	}
	p = NULL;
	malloced = false;
    }
    if (!mediaType) {
	if (p_mediaType == NULL)
	    guessMediaType();
	else
	    mediaType = p_mediaType;
    }
}

IStreamContext::IStreamContext (std::string name, e_opts opts,
				const char* p_mediaType, SWWEBagent* webAgent,
				std::ostream** debugStream)
    : StreamContext<std::istream>(name, &std::cin, opts, 
				  p_mediaType, webAgent, debugStream) {
    if (p == NULL) {
	if (debugStream != NULL && *debugStream != NULL)
	    **debugStream << "+ Stream constructed to read file " << nameStr << ".\n";
	std::ifstream* istr = new std::ifstream(nameStr.c_str());
	malloced = true;
	p = istr;
	if (!istr->is_open())
	    throw std::string("unable to open file \"").append(nameStr).append("\"");
    }
}

OStreamContext::OStreamContext (std::string name, e_opts opts,
				const char* p_mediaType, SWWEBagent* webAgent,
				std::ostream** debugStream)
    : StreamContext<std::ostream>(name, &std::cout, opts, 
				  p_mediaType, webAgent, debugStream) {
    if (p == NULL) {
	if (debugStream != NULL && *debugStream != NULL)
	    **debugStream << "+ Stream constructed to write file " << nameStr << ".\n";
	std::ofstream* ostr = new std::ofstream(nameStr.c_str());
	malloced = true;
	p = ostr;
	if (!ostr->is_open())
	    throw std::string("unable to open file \"").append(nameStr).append("\" for writing.");
    }
}

/* Make sure this compilation unit includes ctor for StreamContext<std::{i,o}stream> */
void __makeSureStreamContextsAreLinked () {
    IStreamContext i("/dev/null"); i = i;
    OStreamContext o("/dev/null"); o = o;
}

std::string NamespaceMap::unmap (std::string mapped) {
    return std::string("<") + mapped + ">";
    // return std::string("[[") + mapped + "]]";
}

void URI::express (Expressor* p_expressor) const {
    p_expressor->uri(this, terminal);
}
void Variable::express (Expressor* p_expressor) const {
    p_expressor->variable(this, terminal);
}
void BNode::express (Expressor* p_expressor) const {
    p_expressor->bnode(this, terminal);
}
void RDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, terminal, datatype, m_LANGTAG);
}
void IntegerRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, m_value);
}
void DecimalRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, m_value);
}
void FloatRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, m_value);
}
void DoubleRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, m_value);
}
void DateTimeRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, terminal, TTerm::URI_xsd_dateTime, NULL);
    // w3c_sw_NEED_IMPL("DateTimeRDFLiteral non-existent in expressor");
}
void BooleanRDFLiteral::express (Expressor* p_expressor) const {
    p_expressor->rdfLiteral(this, m_value);
}
void NULLtterm::express (Expressor* p_expressor) const {
    p_expressor->nulltterm(this);
}
void TriplePattern::express (Expressor* p_expressor) const {
    p_expressor->triplePattern(this, m_s, m_p, m_o);
}
void Filter::express (Expressor* p_expressor) const {
    p_expressor->filter(this, m_TableOperation, &m_Expressions);
}
void NamedGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->namedGraphPattern(this, m_name, allOpts, &m_TriplePatterns);
}
void DefaultGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->defaultGraphPattern(this, allOpts, &m_TriplePatterns);
}
void TableDisjunction::express (Expressor* p_expressor) const {
    p_expressor->tableDisjunction(this, &m_TableOperations);
}
void TableConjunction::express (Expressor* p_expressor) const {
    p_expressor->tableConjunction(this, &m_TableOperations);
}
void OptionalGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->optionalGraphPattern(this, m_TableOperation, &m_Expressions);
}
void MinusGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->minusGraphPattern(this, m_TableOperation);
}
void GraphGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->graphGraphPattern(this, m_VarOrIRIref, m_TableOperation);
}
void ServiceGraphPattern::express (Expressor* p_expressor) const {
    p_expressor->serviceGraphPattern(this, m_VarOrIRIref, m_TableOperation, atomFactory, lexicalCompare);
}
void ExpressionAlias::express (Expressor* p_expressor) const {
    p_expressor->expressionAlias(this, expr, label);
}
void ExpressionAliasList::express (Expressor* p_expressor) const {
    p_expressor->expressionAliasList(this, &m_Expressions);
}
void TTermList::express (Expressor* p_expressor) const {
    p_expressor->posList(this, &m_TTerms);
}
void StarVarSet::express (Expressor* p_expressor) const {
    p_expressor->starVarSet(this);
}
void DefaultGraphClause::express (Expressor* p_expressor) const {
    p_expressor->defaultGraphClause(this, m_IRIref);
}
void NamedGraphClause::express (Expressor* p_expressor) const {
    p_expressor->namedGraphClause(this, m_IRIref);
}
void SolutionModifier::express (Expressor* p_expressor) const {
    p_expressor->solutionModifier(this, groupBy, having, m_OrderConditions, m_limit, m_offset);
}
void Binding::express (Expressor* p_expressor) const {
    p_expressor->binding(this, this);
}
void BindingClause::express (Expressor* p_expressor) const {
    p_expressor->bindingClause(this, m_Vars, this);
}
void WhereClause::express (Expressor* p_expressor) const {
    p_expressor->whereClause(this, m_GroupGraphPattern, m_BindingClause);
}
void OperationSet::express (Expressor* p_expressor) const {
    p_expressor->operationSet(this, &operations);
}
void Select::express (Expressor* p_expressor) const {
    p_expressor->select(this, m_distinctness, m_VarSet, m_DatasetClauses, m_WhereClause,m_SolutionModifier);
}
void SubSelect::express (Expressor* p_expressor) const {
    p_expressor->subSelect(this, m_Select);
}
void Construct::express (Expressor* p_expressor) const {
    p_expressor->construct(this, m_ConstructTemplate, m_DatasetClauses, m_WhereClause,m_SolutionModifier);
}
void Describe::express (Expressor* p_expressor) const {
    p_expressor->describe(this, m_VarSet, m_DatasetClauses, m_WhereClause,m_SolutionModifier);
}
void Ask::express (Expressor* p_expressor) const {
    p_expressor->ask(this, m_DatasetClauses,m_WhereClause);
}
void Replace::express (Expressor* p_expressor) const {
    p_expressor->replace(this, m_WhereClause,m_GraphTemplate);
}
void Insert::express (Expressor* p_expressor) const {
    p_expressor->insert(this, m_GraphTemplate,m_WhereClause);
}
void Delete::express (Expressor* p_expressor) const {
    p_expressor->del(this, m_GraphTemplate,m_WhereClause);
}
void Load::express (Expressor* p_expressor) const {
    p_expressor->load(this, m_IRIrefs,m_into);
}
void Clear::express (Expressor* p_expressor) const {
    p_expressor->clear(this, m__QGraphIRI_E_Opt);
}
void Create::express (Expressor* p_expressor) const {
    p_expressor->create(this, m_Silence,m_GraphIRI);
}
void Drop::express (Expressor* p_expressor) const {
    p_expressor->drop(this, m_Silence,m_GraphIRI);
}
void TTermExpression::express (Expressor* p_expressor) const {
    p_expressor->posExpression(this, m_TTerm);
}
void ArgList::express (Expressor* p_expressor) const {
    p_expressor->argList(this, expressions);
}
void FunctionCall::express (Expressor* p_expressor) const {
    p_expressor->functionCall(this, m_IRIref,m_ArgList);
}
void FunctionCallExpression::express (Expressor* p_expressor) const {
    p_expressor->functionCallExpression(this, m_FunctionCall);
}
/* Expressions */
void BooleanNegation::express (Expressor* p_expressor) const {
    p_expressor->booleanNegation(this, m_Expression);
}
void ArithmeticNegation::express (Expressor* p_expressor) const {
    p_expressor->arithmeticNegation(this, m_Expression);
}
void ArithmeticInverse::express (Expressor* p_expressor) const {
    p_expressor->arithmeticInverse(this, m_Expression);
}
void BooleanConjunction::express (Expressor* p_expressor) const {
    p_expressor->booleanConjunction(this, &m_Expressions);
}
void BooleanDisjunction::express (Expressor* p_expressor) const {
    p_expressor->booleanDisjunction(this, &m_Expressions);
}
void ArithmeticSum::express (Expressor* p_expressor) const {
    p_expressor->arithmeticSum(this, &m_Expressions);
}
void ArithmeticProduct::express (Expressor* p_expressor) const {
    p_expressor->arithmeticProduct(this, &m_Expressions);
}
void BooleanEQ::express (Expressor* p_expressor) const {
    p_expressor->booleanEQ(this, left,right);
}
void BooleanNE::express (Expressor* p_expressor) const {
    p_expressor->booleanNE(this, left,right);
}
void BooleanLT::express (Expressor* p_expressor) const {
    p_expressor->booleanLT(this, left,right);
}
void BooleanGT::express (Expressor* p_expressor) const {
    p_expressor->booleanGT(this, left,right);
}
void BooleanLE::express (Expressor* p_expressor) const {
    p_expressor->booleanLE(this, left,right);
}
void BooleanGE::express (Expressor* p_expressor) const {
    p_expressor->booleanGE(this, left,right);
}
void ComparatorExpression::express (Expressor* p_expressor) const {
    p_expressor->comparatorExpression(this, m_GeneralComparator);
}
void NumberExpression::express (Expressor* p_expressor) const {
    p_expressor->numberExpression(this, m_NumericRDFLiteral);
}

#define URICONST(lname) URI("http://www.w3.org/2001/XMLSchema#" #lname)
#define FUNCCONST(lname) URI("http://www.w3.org/TR/rdf-sparql-query/#" #lname)

    /** URI constants, shared between all AtomFactories: */
    const URI AtomFactory::_URIConstants[] = {
	// { "http://www.w3.org/2001/XMLSchema#integer", URI("http://www.w3.org/2001/XMLSchema#integer") }
	URICONST(integer),
	URICONST(decimal),
	URICONST(float),
	URICONST(double),
	URICONST(string),
	URICONST(boolean),
	URICONST(nonPositiveInteger),
	URICONST(negativeInteger),
	URICONST(long),
	URICONST(int),
	URICONST(short),
	URICONST(byte),
	URICONST(nonNegativeInteger),
	URICONST(unsignedLong),
	URICONST(unsignedInt),
	URICONST(unsignedShort),
	URICONST(unsignedByte),
	URICONST(positiveInteger),
	URICONST(dateTime),

	FUNCCONST(func-str),
	FUNCCONST(func-lang),
	FUNCCONST(func-langMatches),
	FUNCCONST(func-datatype),
	FUNCCONST(func-bound),
	FUNCCONST(func-sameTerm),
	FUNCCONST(func-isIRI),
	FUNCCONST(func-isURI),
	FUNCCONST(func-isBlank),
	FUNCCONST(func-isLiteral),
	FUNCCONST(func-count),
	FUNCCONST(func-sum),
	FUNCCONST(func-min),
	FUNCCONST(func-max),
	FUNCCONST(func-avg),
	FUNCCONST(func-group_group),
	FUNCCONST(func-group_regex),
	FUNCCONST(func-concat),
	FUNCCONST(func-group_concat),
	FUNCCONST(func-if),
	FUNCCONST(func-strlang),
	FUNCCONST(func-strdt),
	FUNCCONST(func-sample),
	FUNCCONST(func-iri),
	FUNCCONST(func-uri),
	FUNCCONST(func-blank)
    };

    const URI* TTerm::URI_xsd_integer		 = AtomFactory::_URIConstants + 0;
    const URI* TTerm::URI_xsd_decimal		 = AtomFactory::_URIConstants + 1;
    const URI* TTerm::URI_xsd_float		 = AtomFactory::_URIConstants + 2;
    const URI* TTerm::URI_xsd_double		 = AtomFactory::_URIConstants + 3;
    const URI* TTerm::URI_xsd_string		 = AtomFactory::_URIConstants + 4;
    const URI* TTerm::URI_xsd_boolean		 = AtomFactory::_URIConstants + 5;
    const URI* TTerm::URI_xsd_nonPositiveInteger = AtomFactory::_URIConstants + 6;
    const URI* TTerm::URI_xsd_negativeInteger	 = AtomFactory::_URIConstants + 7;
    const URI* TTerm::URI_xsd_long		 = AtomFactory::_URIConstants + 8;
    const URI* TTerm::URI_xsd_int		 = AtomFactory::_URIConstants + 9;
    const URI* TTerm::URI_xsd_short		 = AtomFactory::_URIConstants + 10;
    const URI* TTerm::URI_xsd_byte		 = AtomFactory::_URIConstants + 11;
    const URI* TTerm::URI_xsd_nonNegativeInteger = AtomFactory::_URIConstants + 12;
    const URI* TTerm::URI_xsd_unsignedLong	 = AtomFactory::_URIConstants + 13;
    const URI* TTerm::URI_xsd_unsignedInt	 = AtomFactory::_URIConstants + 14;
    const URI* TTerm::URI_xsd_unsignedShort	 = AtomFactory::_URIConstants + 15;
    const URI* TTerm::URI_xsd_unsignedByte	 = AtomFactory::_URIConstants + 16;
    const URI* TTerm::URI_xsd_positiveInteger	 = AtomFactory::_URIConstants + 17;
    const URI* TTerm::URI_xsd_dateTime		 = AtomFactory::_URIConstants + 18;

    const URI* TTerm::FUNC_str			 = AtomFactory::_URIConstants + 19;
    const URI* TTerm::FUNC_lang			 = AtomFactory::_URIConstants + 20;
    const URI* TTerm::FUNC_langMatches		 = AtomFactory::_URIConstants + 21;
    const URI* TTerm::FUNC_datatype		 = AtomFactory::_URIConstants + 22;
    const URI* TTerm::FUNC_bound		 = AtomFactory::_URIConstants + 23;
    const URI* TTerm::FUNC_sameTerm		 = AtomFactory::_URIConstants + 24;
    const URI* TTerm::FUNC_isIRI		 = AtomFactory::_URIConstants + 25;
    const URI* TTerm::FUNC_isURI		 = AtomFactory::_URIConstants + 26;
    const URI* TTerm::FUNC_isBlank		 = AtomFactory::_URIConstants + 27;
    const URI* TTerm::FUNC_isLiteral		 = AtomFactory::_URIConstants + 28;
    const URI* TTerm::FUNC_count		 = AtomFactory::_URIConstants + 29;
    const URI* TTerm::FUNC_sum			 = AtomFactory::_URIConstants + 30;
    const URI* TTerm::FUNC_min			 = AtomFactory::_URIConstants + 31;
    const URI* TTerm::FUNC_max			 = AtomFactory::_URIConstants + 32;
    const URI* TTerm::FUNC_avg			 = AtomFactory::_URIConstants + 33;
    const URI* TTerm::FUNC_group		 = AtomFactory::_URIConstants + 34;
    const URI* TTerm::FUNC_regex		 = AtomFactory::_URIConstants + 35;
    const URI* TTerm::FUNC_concat		 = AtomFactory::_URIConstants + 36;
    const URI* TTerm::FUNC_group_concat		 = AtomFactory::_URIConstants + 37;
    const URI* TTerm::FUNC_if			 = AtomFactory::_URIConstants + 38;
    const URI* TTerm::FUNC_strlang		 = AtomFactory::_URIConstants + 39;
    const URI* TTerm::FUNC_strdt		 = AtomFactory::_URIConstants + 40;
    const URI* TTerm::FUNC_sample		 = AtomFactory::_URIConstants + 41;
    const URI* TTerm::FUNC_iri			 = AtomFactory::_URIConstants + 42;
    const URI* TTerm::FUNC_uri			 = AtomFactory::_URIConstants + 43;
    const URI* TTerm::FUNC_blank		 = AtomFactory::_URIConstants + 44;

    const BooleanRDFLiteral AtomFactory::_BooleanConstants[2] = {
	BooleanRDFLiteral("true",  TTerm::URI_xsd_boolean, true),
	BooleanRDFLiteral("false", TTerm::URI_xsd_boolean, false)
    };

    const BooleanRDFLiteral* TTerm::BOOL_true	 = AtomFactory::_BooleanConstants + 0;
    const BooleanRDFLiteral* TTerm::BOOL_false	 = AtomFactory::_BooleanConstants + 1;

#if !defined(SWIG) // SWIG 2.0.0 appears to barf on initializers for statics.
    AtomFactory::URIMap AtomFactory::uris_static (_URIConstants, 
						  _URIConstants + sizeof(_URIConstants)/sizeof(_URIConstants[0]));
    AtomFactory::RDFLiteralMap AtomFactory::rdfLiterals_static (_BooleanConstants, 
								_BooleanConstants + sizeof(_BooleanConstants)/sizeof(_BooleanConstants[0]));
#endif /* !defined(SWIG) */

    const NULLtterm AtomFactory::_NULLtterm;

    const NULLtterm* TTerm::Unbound		 = &AtomFactory::_NULLtterm;

    /* <AtomFactory> */
    AtomFactory::AtomFactory () {

#if REGEX_LIB == SWOb_BOOST
	using std::numeric_limits;
  #define _VAL1(T, P) validators.insert(ValidatorElt("http://www.w3.org/2001/XMLSchema#" T, Validator(P)))
  #define _VALL(T, P, L, U) validators.insert(ValidatorElt("http://www.w3.org/2001/XMLSchema#" T, Validator(P, (long)L, (long)U)))
  #define _VALD(T, P, L, U) validators.insert(ValidatorElt("http://www.w3.org/2001/XMLSchema#" T, Validator(P, (long double)L, (long double)U)))
  #define _MIND RANGE_unlimited /* -numeric_limits<long double>::max() */
  #define _MAXD RANGE_unlimited /* numeric_limits<long double>::max() */
  #define _MINL RANGE_unlimited /* numeric_limits<long>::min() */
  #define _MAXL RANGE_unlimited /* numeric_limits<long>::max() */

	const char* longPattern =    "^[-+]?[0-9]+$";
	const char* decimalPattern = "^[+\\-]?[0-9]+(\\.[0-9]+)?$";
	const char* floatPattern =   "^[+\\-]?[0-9]+(\\.[0-9]+)?([eE][-+]?[0-9]+)?$";
	_VAL1("integer", 	    longPattern);
	_VAL1("decimal", 	    decimalPattern);
	_VALD("float", 		    floatPattern, _MIND, _MAXD); // -149E16777216, 104E16777216);
	_VALL("double", 	    floatPattern, _MIND, _MAXD); // -1075E2251799813685248, 970E2251799813685248);
	_VAL1("string", 	    ".*");
	_VAL1("boolean", 	    "^(true|false|1|0)$");
	_VAL1("dateTime", "^("
	      "([\\-+]?)"	// optional sign @@ perhaps not supported by time(2)
	      "(\\d{4,})"	// 2004
	      "-(\\d{2})"	//     -12
	      "-(\\d{2})"	//        -31
	      "T(\\d{2})"	//           T19
	      ":(\\d{2})"	//              :01
	      "(?::(\\d{2}))?"	//                 :00
	      "(?:Z|"		//                    Z
	       "(?:([+\\-])"	//                    -
	        "(\\d{2})"	//                     05
	        ":(\\d{2})"	//                       :00
	        "))" ")$");		// 2004-12-31T19:01:00-05:00

	    //derived numerics

	_VAL1("nonPositiveInteger", "^\\+?0+|-[0-9]+$");
	_VALL("negativeInteger",    "^-[0-9]+$", RANGE_unlimited, -1);
	_VALL("long", 		    longPattern, _MINL, _MAXL); // -9223372036854775808, 9223372036854775807);
	_VALL("int", 		    longPattern, _MINL, _MAXL); // -2147483648, 2147483647);
	_VALL("short", 		    longPattern, -32768, 32767);
	_VALL("byte",		    longPattern, -128, 127);
	_VALL("nonNegativeInteger", longPattern, 0, RANGE_unlimited);
	_VALL("unsignedLong", 	    longPattern, 0, _MAXL); // 18446744073709551615);
	_VALL("unsignedInt", 	    longPattern, 0, _MAXL); // 4294967295);
	_VALL("unsignedShort", 	    longPattern, 0, 65535);
	_VALL("unsignedByte", 	    longPattern, 0, 255);
	_VALL("positiveInteger",    longPattern, 1, RANGE_unlimited);

  #undef _VAL1
  #undef _VALL
  #undef _VALD
  #undef _MINL
  #undef _MAXL
  #undef _MIND
  #undef _MAXD
#endif /* REGEX_LIB == SWOb_BOOST */
    }
    AtomFactory::~AtomFactory () {

	std::map<std::string, const TriplePattern*>::iterator iTriples;
	for (iTriples = triples.begin(); iTriples != triples.end(); iTriples++)
	    delete iTriples->second;
	triples.clear();

	std::map<std::string, const Variable*>::iterator iVariables;
	for (iVariables = variables.begin(); iVariables != variables.end(); iVariables++)
	    delete iVariables->second;
	variables.clear();

	std::map<std::string, const URI*>::iterator iURIs;
	for (iURIs = uris.begin(); iURIs != uris.end(); iURIs++)
	    delete iURIs->second;
	uris.clear();

	std::set<const BNode*>::iterator iBNodes;
	for (iBNodes = bnodes.begin(); iBNodes != bnodes.end(); ++iBNodes)
	    delete *iBNodes;
	bnodes.clear();

	std::map<std::string, const RDFLiteral*>::iterator iRDFLiterals;
	for (iRDFLiterals = rdfLiterals.begin(); iRDFLiterals != rdfLiterals.end(); iRDFLiterals++)
	    delete iRDFLiterals->second;
	rdfLiterals.clear();
    }

    const Variable* AtomFactory::getVariable (std::string name) {
	std::string key(name);
	VariableMap::const_iterator vi = variables.find(key);
	if (vi == variables.end()) {
	    Variable* ret = new Variable(name);
	    variables[key] = ret;
	    return ret;
	} else
	    return vi->second;
    }

    const BNode* AtomFactory::createBNode () {
	BNode* ret = new BNode();
	std::stringstream name;
	name << ret; // addr
	bnodes.insert(ret);
	return ret;
    }

    const BNode* AtomFactory::getBNode (std::string name, TTerm::String2BNode& nodeMap) {
	std::string key(name);
	TTerm::String2BNode::const_iterator vi = nodeMap.find(key);
	if (vi == nodeMap.end()) {
	    BNode* ret = new BNode(name);
	    nodeMap[key] = ret;
	    bnodes.insert(ret);
	    return ret;
	} else
	    return vi->second;
    }

    const URI* AtomFactory::getURI (std::string name) {
	std::string key(name);
	URIMap::const_iterator vi = uris_static.find(key);
	if (vi == uris_static.end()) {
	    vi = uris.find(key);
	    if (vi == uris.end()) {
		URI* ret = new URI(name);
		uris[key] = ret;
		return ret;
	    }
	}
	return vi->second;
    }

    const TTerm* AtomFactory::getTTerm (std::string posStr, TTerm::String2BNode& nodeMap) {
	if (posStr[0] == '<' && posStr[posStr.size()-1] == '>')
	    return getURI(posStr.substr(1, posStr.size()-2));
	if (posStr[0] == '_' && posStr[1] == ':')
	    return getBNode(posStr.substr(2, posStr.size()-2), nodeMap);
	if ((posStr[0] == '"' && posStr[posStr.size()-1] == '"') ||
	    (posStr[0] == '\'' && posStr[posStr.size()-1] == '\''))
	    return getRDFLiteral(posStr.substr(1, posStr.size()-2), NULL, NULL);
	if (posStr[0] == '?')
	    return getVariable(posStr.substr(1, posStr.size()-1));
	if (posStr[0] == '-' || (posStr[0] >= '0' && posStr[0] <= '9')) {
	    std::istringstream is(posStr);
	    int i;
	    is >> i;
	    return getNumericRDFLiteral(posStr, i);
	}
	throw(std::runtime_error("unable to getTTerm("+posStr+")"));
    }

     void AtomFactory::validate (std::string value, std::string datatype) {
#if REGEX_LIB == SWOb_BOOST
	 ValidatorSet::const_iterator it = validators.find(datatype);
	 if (it == validators.end())
	     return;
	 const Validator& v = it->second;
	 boost::match_results<std::string::const_iterator> what;
	 if (!regex_search(value, what, v.pattern, boost::match_default)) {
	     if (debugStream && *debugStream)
		 **debugStream << "pattern \"" << v.pattern << "\" failed to match \"" << value << "\"." << std::endl;
	     throw TypeError(value, datatype);
	 }
	 if (v.intmin != RANGE_unlimited || v.intmax != RANGE_unlimited) {
	     std::istringstream is(value);
	     long i;
	     is >> i;
	     if ((v.intmin != RANGE_unlimited && i < -v.intmin) || 
		 (v.intmax != RANGE_unlimited && i > -v.intmax))
		 throw TypeError(value, datatype);
	 }
	 if (v.floatmin != RANGE_unlimited || v.floatmax != RANGE_unlimited) {
	     std::istringstream is(value);
	     double d;
	     is >> d;
	     if ((v.floatmin != RANGE_unlimited && d < -v.floatmin) || 
		 (v.floatmax != RANGE_unlimited && d > -v.floatmax))
		 throw TypeError(value, datatype);
	 }
#else /* REGEX_LIB == SWOb_BOOST */
	if (debugStream != NULL && *debugStream != NULL)
	    **debugStream << "unable to validate that \"" << value << "\" is a " << datatype << " without boost regular expression" << std::endl;
#endif /* REGEX_LIB != SWOb_BOOST */
    }

    const RDFLiteral* AtomFactory::getRDFLiteral (std::string p_String, const URI* p_URI, LANGTAG* p_LANGTAG, bool needsValidation) {
	std::istringstream is(p_String);

	if (p_URI != NULL && needsValidation == true)
	    validate(p_String, p_URI->getLexicalValue());
	if (p_URI == TTerm::URI_xsd_integer || 
	    p_URI == TTerm::URI_xsd_nonPositiveInteger || 
	    p_URI == TTerm::URI_xsd_negativeInteger || 
	    p_URI == TTerm::URI_xsd_long || 
	    p_URI == TTerm::URI_xsd_int || 
	    p_URI == TTerm::URI_xsd_short || 
	    p_URI == TTerm::URI_xsd_byte || 
	    p_URI == TTerm::URI_xsd_nonNegativeInteger || 
	    p_URI == TTerm::URI_xsd_unsignedLong || 
	    p_URI == TTerm::URI_xsd_unsignedInt || 
	    p_URI == TTerm::URI_xsd_unsignedShort || 
	    p_URI == TTerm::URI_xsd_unsignedByte || 
	    p_URI == TTerm::URI_xsd_positiveInteger) {
	    int i;
	    is >> i;
// 	    std::stringstream canonical;
// 	    canonical << std::dec << i;
// 	    return getNumericRDFLiteral(canonical.str().c_str(), i);
	    return getNumericRDFLiteral(p_String.c_str(), i);
	} else if (p_URI == TTerm::URI_xsd_decimal || 
		   p_URI == TTerm::URI_xsd_float) {
	    float f;
	    is >> f;
// 	    std::stringstream canonical;
// 	    canonical << std::fixed << f;
// 	    return getNumericRDFLiteral(canonical.str().c_str(), f);
	    return p_URI == TTerm::URI_xsd_float ? 
		getNumericRDFLiteral(p_String.c_str(), f, true) :
		getNumericRDFLiteral(p_String.c_str(), f);
	} else if (p_URI == TTerm::URI_xsd_double) {
	    double d;
	    is >> d;
// 	    std::stringstream canonical;
// 	    canonical << std::scientific << d;
// 	    return getNumericRDFLiteral(canonical.str().c_str(), d);
	    return getNumericRDFLiteral(p_String.c_str(), d);
	} else if (p_URI == TTerm::URI_xsd_dateTime) {
	    return getDateTimeRDFLiteral(p_String.c_str());
	} else if (p_URI == TTerm::URI_xsd_boolean) {
	    if (p_String == "0" || p_String == "false")
		return getBooleanRDFLiteral("false", 0);
	    bool b;
#ifdef LIBC_PARSES_BOOL
	    is >> b;
#else
	    b = true;
#endif
// 	    std::stringstream canonical;
// 	    canonical << std::boolalpha << b;
// 	    return getNumericRDFLiteral(canonical.str().c_str(), b);
	    return getBooleanRDFLiteral(p_String.c_str(), b);
	}

	std::stringstream buf;
	buf << '"' << p_String << '"';
	if (p_URI)
	    buf << "^^<" << p_URI->getLexicalValue() << ">";
	if (p_LANGTAG) {
	    std::string lang(p_LANGTAG->getLexicalValue());
	    std::locale loc("C");
	    for(std::string::iterator each= lang.begin(); each!= lang.end(); ++each)
		*each= std::tolower(*each, loc);
	    buf << "@" << lang;
	}
	std::string key(buf.str());
	RDFLiteralMap::const_iterator vi = rdfLiterals_static.find(key);
	if (vi == rdfLiterals_static.end()) {
	    vi = rdfLiterals.find(key);
	    if (vi == rdfLiterals.end()) {
		RDFLiteral* ret = new RDFLiteral(p_String, p_URI, p_LANGTAG);
		rdfLiterals[key] = ret;
		return ret;
	    }
	}
	delete p_LANGTAG; // will not be used to create an RDFLiteral.
	return vi->second;
    }

#define XSD "http://www.w3.org/2001/XMLSchema#"
#define LEN_XSD sizeof(XSD)
    const IntegerRDFLiteral* AtomFactory::getNumericRDFLiteral (std::string p_String, int p_value) {
	class MakeIntegerRDFLiteral : public MakeNumericRDFLiteral {
	private: int m_value;
	public: MakeIntegerRDFLiteral (int p_value) : m_value(p_value) {  }
	    virtual const NumericRDFLiteral* makeIt (std::string p_String, const URI* p_URI) {
		return new IntegerRDFLiteral(p_String, p_URI, m_value);
	    }
	};
	MakeIntegerRDFLiteral maker(p_value);
	IntegerRDFLiteral* ret = (IntegerRDFLiteral*)getNumericRDFLiteral(p_String, "integer", &maker);
	return ret;
    }

    const DecimalRDFLiteral* AtomFactory::getNumericRDFLiteral (std::string p_String, float p_value) {
	class MakeDecimalRDFLiteral : public MakeNumericRDFLiteral {
	private: float m_value;
	public: MakeDecimalRDFLiteral (float p_value) : m_value(p_value) {  }
	    virtual const NumericRDFLiteral* makeIt (std::string p_String, const URI* p_URI) {
		return new DecimalRDFLiteral(p_String, p_URI, m_value);
	    }
	};
	MakeDecimalRDFLiteral maker(p_value);
	DecimalRDFLiteral* ret = (DecimalRDFLiteral*)getNumericRDFLiteral(p_String, "decimal", &maker);
	return ret;
    }

    const FloatRDFLiteral* AtomFactory::getNumericRDFLiteral (std::string p_String, float p_value, bool /* floatness */) {
	class MakeFloatRDFLiteral : public MakeNumericRDFLiteral {
	private: float m_value;
	public: MakeFloatRDFLiteral (float p_value) : m_value(p_value) {  }
	    virtual const NumericRDFLiteral* makeIt (std::string p_String, const URI* p_URI) {
		return new FloatRDFLiteral(p_String, p_URI, m_value);
	    }
	};
	MakeFloatRDFLiteral maker(p_value);
	FloatRDFLiteral* ret = (FloatRDFLiteral*)getNumericRDFLiteral(p_String, "float", &maker);
	return ret;
    }

    const DoubleRDFLiteral* AtomFactory::getNumericRDFLiteral (std::string p_String, double p_value) {
	class MakeDoubleRDFLiteral : public MakeNumericRDFLiteral {
	private: double m_value;
	public: MakeDoubleRDFLiteral (double p_value) : m_value(p_value) {  }
	    virtual const NumericRDFLiteral* makeIt (std::string p_String, const URI* p_URI) {
		return new DoubleRDFLiteral(p_String, p_URI, m_value);
	    }
	};
	MakeDoubleRDFLiteral maker(p_value);
	DoubleRDFLiteral* ret = (DoubleRDFLiteral*)getNumericRDFLiteral(p_String, "double", &maker);
	return ret;
    }

    const DateTimeRDFLiteral* AtomFactory::getDateTimeRDFLiteral (std::string p_String) {
	std::stringstream buf;
	buf << "\"" << p_String << "\"^^<http://www.w3.org/2001/XMLSchema#dateTime>";
	std::string key(buf.str());
	RDFLiteralMap::const_iterator vi = rdfLiterals_static.find(key);
	if (vi == rdfLiterals_static.end()) {
	    vi = rdfLiterals.find(key);
	    if (vi == rdfLiterals.end()) {
		DateTimeRDFLiteral* ret = new DateTimeRDFLiteral(p_String, TTerm::URI_xsd_dateTime);
		rdfLiterals[key] = ret;
		return ret;
	    }
	}
	return (DateTimeRDFLiteral*)vi->second; // shameful downcast
    }

    const BooleanRDFLiteral* AtomFactory::getBooleanRDFLiteral (std::string p_String, bool p_value) {
	std::stringstream buf;
	buf << "\"" << (p_value ? "true" : "false") << "\"^^<http://www.w3.org/2001/XMLSchema#boolean>"; // p_String
	std::string key(buf.str());
	RDFLiteralMap::const_iterator vi = rdfLiterals_static.find(key);
	if (vi == rdfLiterals_static.end()) {
	    vi = rdfLiterals.find(key);
	    if (vi == rdfLiterals.end()) {
		BooleanRDFLiteral* ret = new BooleanRDFLiteral(p_String, TTerm::URI_xsd_boolean, p_value);
		rdfLiterals[key] = ret;
		return ret;
	    }
	}
	return (BooleanRDFLiteral*)vi->second; // shameful downcast
    }

    const NumericRDFLiteral* AtomFactory::getNumericRDFLiteral (std::string p_String, const char* type, MakeNumericRDFLiteral* maker) {

	std::string str;
	str += XSD;
	str += type;
	const URI* uri = getURI(str);

	std::stringstream buf;
	buf << '"' << p_String << '"';
	if (uri)
	    buf << "^^<" << uri->getLexicalValue() << ">";
	std::string key(buf.str());
	RDFLiteralMap::const_iterator vi = rdfLiterals_static.find(key);
	if (vi == rdfLiterals_static.end()) {
	    vi = rdfLiterals.find(key);
	    if (vi == rdfLiterals.end()) {
		const NumericRDFLiteral* ret = maker->makeIt(p_String, uri);
		rdfLiterals[key] = ret;
		return ret;
	    }
	}
	return (const NumericRDFLiteral*)vi->second; // shameful downcast
    }

    const TriplePattern* AtomFactory::getTriple (const TTerm* s, const TTerm* p, const TTerm* o, bool weaklyBound) {
	if (s == NULL || s == TTerm::Unbound || 
	    p == NULL || p == TTerm::Unbound || 
	    o == NULL || o == TTerm::Unbound)
	    throw
		std::string("getTriple(")
		+ (s == NULL ? "NULLptr" : s->toString()) + ", " 
		+ (p == NULL ? "NULLptr" : p->toString()) + ", " 
		+ (o == NULL ? "NULLptr" : o->toString()) + ")";

	std::stringstream key;
	key << s << p << o << weaklyBound;
	TriplePatternMap::const_iterator vi = triples.find(key.str());
	if (vi == triples.end()) {
	    TriplePattern* ret = new TriplePattern(s, p, o);
	    triples[key.str()] = ret;
	    return ret;
	} else {
	    const TriplePattern* ret = vi->second;
	    return ret;
	}
    }

#if REGEX_LIB == SWOb_BOOST
    /** parseNTPatterns - parse forms like   _:a <p2> 's2' .\n
     */
    void AtomFactory::parseNTPatterns (BasicGraphPattern* g, std::string spo, TTerm::String2BNode& nodeMap) {
	const boost::regex expression("\\G(?:"	// anchor at start
				      "[ \\t]*#([^\n]+)\n?"	// Comment
				      "|"			// or Triple
				      "[ \\t]*((?:<[^>]*>)|(?:_:[^ \\t]+)|(?:[?$][^ \\t]+)|(?:\"[^\"]+\")|(?:'[^']+'))"	// S
				      "[ \\t]*((?:<[^>]*>)|(?:_:[^ \\t]+)|(?:[?$][^ \\t]+)|(?:\"[^\"]+\")|(?:'[^']+'))"	// P
				      "[ \\t]*((?:<[^>]*>)|(?:_:[^ \\t]+)|(?:[?$][^ \\t]+)|(?:\"[^\"]+\")|(?:'[^']+'))"	// O
				      "[ \\t]*\\.[ \\t]*\\n?"								// EOL
				      "|"			// or Empty line
				      "\n"
				      "|"			// or Junk
				      "([^\n]+)\n?"
				      ")");
	std::string::const_iterator start, end; 
	start = spo.begin(); 
	end = spo.end(); 
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	while (regex_search(start, end, what, expression, flags)) {
	    if (what[5].first != what[5].second)
		throw std::string("unparsable input: ") + std::string(what[5].first, what[5].second);
	    else if (what[1].first != what[1].second)
		; // std::cerr << "comment(" << std::string(what[1].first, what[1].second) << ")\n";
	    else if (*what[0].first != '\n')
		g->addTriplePattern(getTriple(getTTerm(std::string(what[2].first, what[2].second), nodeMap), 
					      getTTerm(std::string(what[3].first, what[3].second), nodeMap), 
					      getTTerm(std::string(what[4].first, what[4].second), nodeMap), false));
	    start = what[0].second; 
	    // update flags: 
	    flags |= boost::match_prev_avail; 
	    flags |= boost::match_not_bob; 
	}
    }
#endif /* REGEX_LIB == SWOb_BOOST */

    const TTerm* AtomFactory::applyCommonNumeric (const Expression* arg, UnaryFunctor* func) {
	const TTerm* v = arg->eval(func->res, this, func->evaluator);
	TTerm::e_TYPE dt = v->getTypeOrder();
	if (dt == TTerm::TYPE_Err)
	    throw std::string(typeid(*v).name()) + " is not a known datatype.";
	switch (dt) {
	case TTerm::TYPE_Integer: {
	    int i = func->eval(static_cast<const NumericRDFLiteral*>(v)->getInt());
	    std::stringstream s;
	    s << i;
	    v = getNumericRDFLiteral(s.str(), i);
	     break;
	 }
	case TTerm::TYPE_Float:
	     case TTerm::TYPE_Decimal: {
		 float i = func->eval(static_cast<const NumericRDFLiteral*>(v)->getFloat());
		 std::stringstream s;
		 s << i;
		 v = getNumericRDFLiteral(s.str(), i);
		 break;
	     }
	     case TTerm::TYPE_Double: {
		 double i = func->eval(static_cast<const NumericRDFLiteral*>(v)->getDouble());
		 std::stringstream s;
		 s << i;
		 v = getNumericRDFLiteral(s.str(), i);
		 break;
	     }
	     default:
		 throw std::string(typeid(*v).name()) + " is not a numeric datatype: " + v->toString();
	}
	return v;
    }
    const TTerm* AtomFactory::applyCommonNumeric (std::vector<const Expression*> args, NaryFunctor* func) {
	std::vector<const Expression*>::const_iterator it = args.begin();
	const TTerm* l = (*it)->eval(func->res, this, func->evaluator);

	TTerm::e_TYPE dt = l->getTypeOrder();
	if (dt == TTerm::TYPE_Err)
	    throw std::string(typeid(*l).name()) + " is not a known datatype.";
	++it;
	while (it != args.end()) {
	    const TTerm* r = (*it)->eval(func->res, this, func->evaluator);
	    TTerm::e_TYPE dtr = r->getTypeOrder();
	    if (dtr == TTerm::TYPE_Err)
		throw std::string(typeid(*r).name()) + " is not a known datatype.";
	    if (dtr > dt)
		dt = dtr;
	    switch (dt) {
	    case TTerm::TYPE_Integer: {
		int i = func->eval(static_cast<const NumericRDFLiteral*>(l)->getInt(), 
				   static_cast<const NumericRDFLiteral*>(r)->getInt());
		std::stringstream s;
		s << i;
		l = getNumericRDFLiteral(s.str(), i);
		break;
	    }
	    case TTerm::TYPE_Float:
	    case TTerm::TYPE_Decimal: {
		float i = func->eval(static_cast<const NumericRDFLiteral*>(l)->getFloat(), 
				     static_cast<const NumericRDFLiteral*>(r)->getFloat());
		std::stringstream s;
		s << i;
		l = dt == TTerm::TYPE_Float ? getNumericRDFLiteral(s.str(), i, true) : getNumericRDFLiteral(s.str(), i);
		break;
	    }
	    case TTerm::TYPE_Double: {
		double i = func->eval(static_cast<const NumericRDFLiteral*>(l)->getDouble(), 
				      static_cast<const NumericRDFLiteral*>(r)->getDouble());
		std::stringstream s;
		s << i;
		l = getNumericRDFLiteral(s.str(), i);
		break;
	    }
	    default:
		throw std::string(typeid(*r).name()) + " is not a numeric datatype: " + r->toString();
	    }
	    ++it;
	}
	return l;
    }

    /* EBV (Better place for this?) */
    const TTerm* AtomFactory::ebv (const TTerm* tterm) {
	const BooleanRDFLiteral* b = dynamic_cast<const BooleanRDFLiteral*>(tterm);
	if (b != NULL)
	    return b->getValue() ? TTerm::BOOL_true : TTerm::BOOL_false;
	const IntegerRDFLiteral* i = dynamic_cast<const IntegerRDFLiteral*>(tterm);
	if (i != NULL)
	    return i->getValue() == 0 ? TTerm::BOOL_false : TTerm::BOOL_true;
	const DecimalRDFLiteral* f = dynamic_cast<const DecimalRDFLiteral*>(tterm);
	if (f != NULL)
	    return f->getValue() == 0.0 ? TTerm::BOOL_false : TTerm::BOOL_true;
	const FloatRDFLiteral* fl = dynamic_cast<const FloatRDFLiteral*>(tterm);
	if (fl != NULL)
	    return fl->getValue() == 0.0 ? TTerm::BOOL_false : TTerm::BOOL_true;
	const DoubleRDFLiteral* d = dynamic_cast<const DoubleRDFLiteral*>(tterm);
	if (d != NULL)
	    return d->getValue() == 0.0 ? TTerm::BOOL_false : TTerm::BOOL_true;
	const RDFLiteral* l = dynamic_cast<const RDFLiteral*>(tterm);
	const URI* dt = l == NULL ? NULL : l->getDatatype();
	if (l != NULL && 
	    (dt == NULL || dt == TTerm::URI_xsd_string))
	    return std::string(l->getLexicalValue()).empty() ? TTerm::BOOL_false : TTerm::BOOL_true;
	throw TypeError("beats me", "EBV");
    }

    /* </AtomFactory> */

    const TTerm* BNode::evalTTerm (const Result* r, BNodeEvaluator* evaluator) const {
	return evaluator->evaluate(this, r);
    }
    const TTerm* Variable::evalTTerm (const Result* r, BNodeEvaluator*) const {
	const TTerm* ret = r->get(this);
	return ret == NULL ? TTerm::Unbound : ret;
    }

    std::string Operation::toString () const {
	SPARQLSerializer s;
	express(&s);
	return s.str();
    }

    void TableJunction::addTableOperation (const TableOperation* tableOp, bool flatten) {
	if (flatten == true && typeid(*tableOp) == typeid(*this)) { // deactivated
	    TableJunction* j = (TableJunction*)tableOp; /* !!! LIES !!! */
	    for (std::vector<const TableOperation*>::const_iterator it = j->m_TableOperations.begin();
		 it != j->m_TableOperations.end(); ++it)
		m_TableOperations.push_back(*it);
	    j->m_TableOperations.clear();
	    delete j;
	} else
	    m_TableOperations.push_back(tableOp);
    }

    ResultSet* OperationSet::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) rs = new ResultSet(rs->getAtomFactory());
	for (std::vector<const Operation*>::const_iterator it = operations.begin();
	     it != operations.end(); ++it)
	    (*it)->execute(db, rs);
	return rs;
    }

    ResultSet* Select::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) rs = new ResultSet(rs->getAtomFactory());
	for (std::vector<const DatasetClause*>::const_iterator ds = m_DatasetClauses->begin();
	     ds != m_DatasetClauses->end(); ds++)
	    (*ds)->loadData(db);
	m_WhereClause->bindVariables(db, rs);
	if (m_SolutionModifier != NULL) {
	    m_SolutionModifier->order(rs); // @@ need to do two passes if order by can reference ?x AS ?y
	    m_VarSet->project(rs, m_SolutionModifier->groupBy, m_SolutionModifier->having);
	} else
	    m_VarSet->project(rs, NULL, NULL);
	if (m_SolutionModifier == NULL)
	    rs->trim(m_distinctness, -1, -1);
	else
	    rs->trim(m_distinctness, m_SolutionModifier->m_limit, m_SolutionModifier->m_offset);
	return rs;
    }

    struct MakeNewBNode : public BNodeEvaluator {
#if !defined(SWIG)
	struct _Pair {
	    const BNode* node;
	    const Result* r;
	    _Pair (const BNode* node, const Result* r) : node(node), r(r) {  }
	    bool operator< (const _Pair& ref) const {
		if (node != ref.node)
		    return node < ref.node;
		return r < ref.r;
	    }
	};
	AtomFactory* atomFactory;
	std::map<_Pair, const BNode*> map;
	virtual const TTerm* evaluate (const BNode* node, const Result* r) {
	    _Pair p(node, r);
	    if (map.find(p) == map.end())
		map[p] = atomFactory->createBNode();
	    return map[p];
	}
#endif /* defined(SWIG) */
    public:
	MakeNewBNode (AtomFactory* atomFactory) : atomFactory(atomFactory) {  }
    };

    ResultSet* Construct::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) rs = new ResultSet(rs->getAtomFactory());
	for (std::vector<const DatasetClause*>::const_iterator ds = m_DatasetClauses->begin();
	     ds != m_DatasetClauses->end(); ds++)
	    (*ds)->loadData(db);
	m_WhereClause->bindVariables(db, rs);
	MakeNewBNode makeNewBNode(rs->getAtomFactory());
	rs->resultType = ResultSet::RESULT_Graphs;
	RdfDB* workingDB = rs->getRdfDB() ? rs->getRdfDB() : db;
	m_ConstructTemplate->construct(workingDB->ensureGraph(DefaultGraph), rs, &makeNewBNode);
	//std::cerr << "CONSTRUCTED: " << g << std::endl;
	return rs;
    }

    ResultSet* Ask::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) rs = new ResultSet(rs->getAtomFactory());
	for (std::vector<const DatasetClause*>::const_iterator ds = m_DatasetClauses->begin();
	     ds != m_DatasetClauses->end(); ds++)
	    (*ds)->loadData(db);
	m_WhereClause->bindVariables(db, rs);
	rs->resultType = ResultSet::RESULT_Boolean;
	return rs;
    }

    ResultSet* Insert::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) rs = new ResultSet(rs->getAtomFactory());
	if (m_WhereClause != NULL)
	    m_WhereClause->bindVariables(db, rs);
	MakeNewBNode makeNewBNode(rs->getAtomFactory());
	rs->resultType = ResultSet::RESULT_Graphs;
	m_GraphTemplate->construct(rs->getRdfDB() ? rs->getRdfDB() : db, rs, &makeNewBNode, NULL);
	return rs;
    }

    ResultSet* Delete::execute (RdfDB* db, ResultSet* rs) const {
	if (!rs) {
	    rs = new ResultSet(rs->getAtomFactory());
	    *rs->getRdfDB() = *db;
	}
	if (m_WhereClause != NULL)
	    m_WhereClause->bindVariables(db, rs);
	TreatAsVar treatAsVar;
	rs->resultType = ResultSet::RESULT_Graphs;
	m_GraphTemplate->deletePattern(rs->getRdfDB() ? rs->getRdfDB() : db, rs, &treatAsVar, NULL);
	return rs;
    }

    void DatasetClause::loadGraph (RdfDB* db, const TTerm* name, BasicGraphPattern* target) const {
	std::string nameStr = name->getLexicalValue();
	IStreamContext iptr(nameStr, IStreamContext::NONE, NULL, db->webAgent, db->debugStream);
	if (db->loadData(target, iptr, nameStr, nameStr, m_atomFactory))
	    throw nameStr + ":0: error: unable to parse web document";
    }
    void DefaultGraphClause::loadData (RdfDB* db) const {
	loadGraph(db, m_IRIref, db->ensureGraph(DefaultGraph));
    }
    void NamedGraphClause::loadData (RdfDB* db) const {
	loadGraph(db, m_IRIref, db->ensureGraph(m_IRIref));
    }

    void WhereClause::bindVariables (RdfDB* db, ResultSet* rs) const {
	if (m_BindingClause != NULL) m_BindingClause->bindVariables(db, rs);
	m_GroupGraphPattern->bindVariables(db, rs);
    }

    void ExpressionAliasList::project (ResultSet* rs, ExpressionAliasList* groupBy, ProductionVector<const w3c_sw::Expression*>* having) const {
	rs->project(&m_Expressions, groupBy, having);
    }

    void StarVarSet::project (ResultSet* /* rs */, ExpressionAliasList* /* groupBy */, ProductionVector<const w3c_sw::Expression*>* /* having */) const {
    }

    void SolutionModifier::order (ResultSet* rs) {
	if (m_OrderConditions != NULL)
	    rs->order(m_OrderConditions);
    }

    void BindingClause::bindVariables (RdfDB* db, ResultSet* rs) const {
	for (ResultSetIterator it = rs->begin() ; it != rs->end(); ) {
	    for (std::vector<const Binding*>::const_iterator binding = begin() ; binding != end(); ++binding) {
		Result* r = new Result(rs);
		rs->insert(it, r);
		(*binding)->bindVariables(db, rs, r, m_Vars);
	    }
	    delete *it;
	    it = rs->erase(it);
	}
    }

    void Binding::bindVariables (RdfDB*, ResultSet* rs, Result* r, TTermList* p_Vars) const {
	std::vector<const TTerm*>::const_iterator variable = p_Vars->begin();
	std::vector<const TTerm*>::const_iterator value = begin();
	while (value != end()) {
	    rs->set(r, *variable, *value, false);
	    variable++;
	    value++;
	}
    }

    void Filter::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet island(rs->getAtomFactory(), rs->debugStream);
	m_TableOperation->bindVariables(db, &island);
	for (std::vector<const Expression*>::const_iterator it = m_Expressions.begin();
	     it != m_Expressions.end(); it++)
	    island.restrict(*it);
	rs->joinIn(&island, false);
    }

    void TableConjunction::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet island(rs->getAtomFactory(), rs->debugStream);
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end() && rs->size() > 0; it++)
	    (*it)->bindVariables(db, &island);
	rs->joinIn(&island, false);
    }

    void TableConjunction::construct (RdfDB* target, const ResultSet* rs, BNodeEvaluator* evaluator, BasicGraphPattern* bgp) const {
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end() && rs->size() > 0; it++)
	    (*it)->construct(target, rs, evaluator, bgp);
    }

    void TableConjunction::deletePattern (RdfDB* target, const ResultSet* rs, BNodeEvaluator* evaluator, BasicGraphPattern* bgp) const {
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end() && rs->size() > 0; it++)
	    (*it)->deletePattern(target, rs, evaluator, bgp);
    }

    void TableDisjunction::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet island(rs->getAtomFactory(), rs->debugStream);
	delete *(island.begin());
	island.erase(island.begin());
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end(); it++) {
	    ResultSet disjoint(rs->getAtomFactory(), rs->debugStream);
	    (*it)->bindVariables(db, &disjoint);
#if 0
	    for (std::vector<const Filter*>::const_iterator it = m_Filters.begin();
		 it != m_Filters.end(); it++)
		disjoint.restrict(*it);
#endif
	    for (ResultSetIterator row = disjoint.begin() ; row != disjoint.end(); ) {
		island.insert(island.end(), (*row)->duplicate(&island, island.end()));
		delete *row;
		row = disjoint.erase(row);
	    }
	}
	rs->joinIn(&island, false);
    }

    void SubSelect::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet island(rs->getAtomFactory(), rs->debugStream);
	m_Select->execute(db, &island);
	rs->joinIn(&island, false);
    }

    /* wrapper function pushed into .cpp because RdfDB is incomplete. */
    void BasicGraphPattern::_bindVariables (RdfDB* db, ResultSet* rs, const TTerm* p_name) const {
	db->bindVariables(rs, p_name, this);

	/*
+ "algebra__filter_nested_2": 			check measured == expected
- "optional__dawg_optional_complex_1": 		check measured == ResultSet(&F, &rdfDB, "")
- "optional_filter__dawg_optional_filter_002": 	check measured == ResultSet(&F, &rdfDB, "")
- "optional_filter__dawg_optional_filter_003": 	check measured == ResultSet(&F, &rdfDB, "")
- "boolean_effective_value__dawg_bev_5": 	check measured == ResultSet(&F, &rdfDB, "")
- "boolean_effective_value__dawg_bev_6": 	check measured == ResultSet(&F, &rdfDB, "")
- "bound__dawg_bound_query_001": 		check measured == ResultSet(&F, &rdfDB, "")!

compared against
	ResultSet island(rs->getAtomFactory());
	db->bindVariables(&island, p_name, this);
	for (std::vector<const Filter*>::const_iterator it = m_Filters.begin();
	     it != m_Filters.end(); it++)
	    island.restrict(*it);
	rs->joinIn(&island, false);

	*/
    }

    CanonicalRDFLiteral::e_CANON CanonicalRDFLiteral::format = CANON_brief;
    std::ostream* BasicGraphPattern::DiffStream = NULL;
    bool (*BasicGraphPattern::MappableTerm)(const TTerm*) = &BasicGraphPattern::MapVarsAndBNodes;
    ServiceGraphPattern::e_HTTP_METHOD ServiceGraphPattern::defaultServiceProtocol = ServiceGraphPattern::HTTP_METHOD_GET;

    bool BasicGraphPattern::operator== (const BasicGraphPattern& ref) const {

	ResultSet rs(NULL);
	bindVariables(&rs, &ref);
	if (rs.size() == 0)
	    return false;
	// make sure the solution is 1:1 for mappables.
	for (ResultSetIterator row = rs.begin(); row != rs.end(); ++row) {
	    std::set<const TTerm*> seen;
	    for (BindingSetConstIterator b = (*row)->begin(); b != (*row)->end(); ++b) {
		if (seen.find(b->second.tterm) != seen.end())
		    // std::cerr << rs; // see the mapping
		    return false; // break and see if next row is 1:1?
		seen.insert(b->second.tterm);
	    }
	}
	return true;
    }

    void BasicGraphPattern::bindVariables (ResultSet* rs, const BasicGraphPattern* toMatch, const TTerm* graphVar, const TTerm* graphName) const {
 	if (rs->debugStream != NULL && *rs->debugStream != NULL)
	    **rs->debugStream << "matching " << *toMatch;
	for (std::vector<const TriplePattern*>::const_iterator constraint = toMatch->m_TriplePatterns.begin();
	     constraint != toMatch->m_TriplePatterns.end(); constraint++) {
	    for (ResultSetIterator row = rs->begin() ; row != rs->end(); ) {
		bool rowMatched = false;
		const TTerm* s = (*constraint)->getS();
		if ((*BasicGraphPattern::MappableTerm)(s))
		    s = (*row)->get(s);
		const TTerm* p = (*constraint)->getP();
		if ((*BasicGraphPattern::MappableTerm)(p))
		    p = (*row)->get(p);
		const TTerm* o = (*constraint)->getO();
		if ((*BasicGraphPattern::MappableTerm)(o))
		    o = (*row)->get(o);

		TTerm2TTerm2Triple_type::range outer;
		TTerm2Triple_type::const_iterator e;
		TTerm2Triple_range inner(e, e);
		bool useOuter = false;
		bool matchFail = false;
		if (s)
		    if (p)
			inner = SP.get(s, p, &matchFail);
		    else if (o)
			inner = OS.get(o, s, &matchFail);
		    else {
			outer = SP.get(s, &matchFail);
			useOuter = true;
		    }
		else if (p)
		    if (o)
			inner = PO.get(p, o, &matchFail);
		    else {
			outer = PO.get(p, &matchFail);
			useOuter = true;
		    }
		else if (o) {
		    outer = OS.get(o, &matchFail);
		    useOuter = true;
		} else {
		    outer = TTerm2TTerm2Triple_type::range(SP.begin(), SP.end());
		    useOuter = true;
		}

		// TTerm2Triple_range inner
		//     = dynamic_cast<const Bindable*>(pToMatch) 
		//     ? TTerm2Triple_range(TTerm2Triple.begin(), TTerm2Triple.end())
		//     : TTerm2Triple.equal_range (pToMatch);

		if (!matchFail) {
		    if (!useOuter)
			for (TTerm2Triple_type::const_iterator triple = inner.first; triple != inner.second; ++triple) {
			    Result* newRow = (*row)->duplicate(rs, row);
			    /* @@@ move filter her */
			    if ((*constraint)->bindVariables(triple->second, toMatch->allOpts, rs, newRow, graphVar, graphName)) {
				rowMatched = true;
				rs->insert(row, newRow);
			    } else {
				delete newRow;
			    }
			}
		    else
			for (TTerm2TTerm2Triple_type::const_iterator tterm2triple = outer.first; tterm2triple != outer.second; ++tterm2triple) {
			    inner = TTerm2Triple_range(tterm2triple->second.begin(), tterm2triple->second.end());
			    for (TTerm2Triple_type::const_iterator triple = inner.first; triple != inner.second; ++triple) {
				Result* newRow = (*row)->duplicate(rs, row);
				/* @@@ move filter her */
				if ((*constraint)->bindVariables(triple->second, toMatch->allOpts, rs, newRow, graphVar, graphName)) {
				    rowMatched = true;
				    rs->insert(row, newRow);
				} else {
				    delete newRow;
				}
			    }
			}
		}
		if (rowMatched || !toMatch->allOpts) {
		    delete *row;
		    row = rs->erase(row);
		} else {
		    row++;
		}
	    }
	}
	if (rs->debugStream != NULL && *rs->debugStream != NULL)
	    **rs->debugStream << "produced\n" << *rs;
    }
    bool TTerm::bindVariable (const TTerm* constant, ResultSet* rs, Result* provisional, bool weaklyBound) const {
	if (this == Unbound || constant == Unbound)
	    return true;
	TreatAsVar treatAsVar;
	const TTerm* curVal = evalTTerm(provisional, &treatAsVar); // doesn't need to generate symbols
	if (curVal == Unbound) {
	    rs->set(provisional, this, constant, weaklyBound);
	    return true;
	}
	return constant == curVal;
    }

    void GraphGraphPattern::construct (RdfDB* target, const ResultSet* rs, BNodeEvaluator* evaluator, BasicGraphPattern* /* bgp */) const {
	const URI* graphName = dynamic_cast<const URI*>(m_VarOrIRIref);
	if (graphName != NULL) {
	    /* GRAPH <x> { ?s ?p ?o } */
	    BasicGraphPattern* bgp = target->ensureGraph(graphName);
	    m_TableOperation->construct(target, rs, evaluator, bgp);
	} else {
	    /* GRAPH ?g { ?s ?p ?o } */
	    for (ResultSetConstIterator result = rs->begin() ; result != rs->end(); result++) {
		const TTerm* evaldGraphName = m_VarOrIRIref->evalTTerm(*result, evaluator);
		BasicGraphPattern* bgp = target->ensureGraph(evaldGraphName);
		m_TableOperation->construct(target, rs, evaluator, bgp);
	    }
	}
    }

    void GraphGraphPattern::deletePattern (RdfDB* target, const ResultSet* rs, BNodeEvaluator* evaluator, BasicGraphPattern* /* bgp */) const {
	const URI* graphName = dynamic_cast<const URI*>(m_VarOrIRIref);
	if (graphName != NULL) {
	    /* GRAPH <x> { ?s ?p ?o } */
	    BasicGraphPattern* bgp = target->ensureGraph(graphName);
	    m_TableOperation->deletePattern(target, rs, evaluator, bgp);
	} else {
	    /* GRAPH ?g { ?s ?p ?o } */
	    for (ResultSetConstIterator result = rs->begin() ; result != rs->end(); result++) {
		const TTerm* evaldGraphName = m_VarOrIRIref->evalTTerm(*result, evaluator);
		BasicGraphPattern* bgp = target->ensureGraph(evaldGraphName);
		m_TableOperation->deletePattern(target, rs, evaluator, bgp);
	    }
	}
    }

    void _constructQuery (const URI* service, const TableOperation* op, ResultSet* rs, AtomFactory* atomFactory, SWSAXparser* xmlParser, SWWEBagent* agent, std::ostream** debugStream) {
	/* The VarLister is a serializer which also records all variables.
	 */
	struct VarLister : public SPARQLSerializer {
	    std::set<const TTerm*> vars;
	    ExpressionAliasList* l;
	    VarLister () : l(new ExpressionAliasList()) {  }
	    virtual void variable (const Variable* const self, std::string lexicalValue) {
		if (vars.find(self) == vars.end()) {
		    vars.insert(self);
		    l->push_back(new ExpressionAlias(new TTermExpression(self)));
		}
		SPARQLSerializer::variable(self, lexicalValue);
	    }
	};

	VarLister vars;
	op->express(&vars);

	/* Copy graph pattern for inclusion in a new Select. */
	SWObjectDuplicator dup(NULL); // doesn't need to create new atoms.
	op->express(&dup);
	const Operation* query = new Select(DIST_distinct, vars.l,
					    new ProductionVector<const DatasetClause*>(),
					    new WhereClause(dup.last.tableOperation, NULL),
					    new SolutionModifier(NULL, NULL, NULL, LIMIT_None, OFFSET_None)); // !!! groupBy, having

	/* Constrain query with any existing result bindings. */
	const Operation* rsConstrained = rs->getConstrainedOperation(query);
	SWWEBagent::ParameterList p;
	p.set("query", (rsConstrained ? rsConstrained : query)->toString());
	if (rsConstrained)
	    delete rsConstrained;
	delete query;

	if (debugStream != NULL && *(debugStream) != NULL)
	    **(debugStream) << "Querying <" << service->getLexicalValue() << "> for\n" << p;

	/* Do an HTTP GET and parse results into a ResultSet. */
	std::string s;
	switch (ServiceGraphPattern::defaultServiceProtocol) {
	case ServiceGraphPattern::HTTP_METHOD_GET:
	    s = agent->get(service->getLexicalValue().c_str(), p);
	    break;
	case ServiceGraphPattern::HTTP_METHOD_POST:
	    s = agent->post(service->getLexicalValue().c_str(), p);
	    break;
	default:
	    throw "program flow exception -- unknown defaultServiceProtocol";
	}
	IStreamContext istr(s, IStreamContext::STRING);
	try {
	    ResultSet red(atomFactory, xmlParser, istr);
	    if (debugStream != NULL && *(debugStream) != NULL) {
		**(debugStream) << " yielded";
		size_t size = red.size();
		if (size > ResultSet::DebugEnumerateLimit)
		    **debugStream << " " << size
				  << " result" << (size == 1 ? "" : "s")
				  << ".\n";
		else
		    **debugStream << "\n" << red;
	    }

	    /* Join those results against our initial results. */
	    rs->joinIn(&red);
	} catch (std::string e) {
	    throw e + "\nerror parsing response from service " + service->toString() + ".";
	}
    }
    void ServiceGraphPattern::bindVariables (RdfDB* db, ResultSet* rs) const {
	const URI* graph = dynamic_cast<const URI*>(m_VarOrIRIref);
	if (graph != NULL)
	    _constructQuery(graph, m_TableOperation, rs, atomFactory, db->xmlParser, db->webAgent, db->debugStream);
	else {
	    const Variable* graphVar = dynamic_cast<const Variable*>(m_VarOrIRIref);
	    if (graphVar != NULL) {
		for (ResultSetIterator outerRow = rs->begin() ; outerRow != rs->end(); ) {
		    const URI* graph = dynamic_cast<const URI*>((*outerRow)->get(graphVar));
		    if (graph != NULL) {
			ResultSet* single = (*outerRow)->makeResultSet(atomFactory);
			_constructQuery(graph, m_TableOperation, single, atomFactory, db->xmlParser, db->webAgent, db->debugStream);
			for (ResultSetIterator innerRow = single->begin() ; innerRow != single->end(); ) {
			    rs->insert(outerRow, *innerRow);
			    innerRow = single->erase(innerRow);
			}
		    } else {
			// treat like a TypeError; no result
		    }
		    delete *outerRow;
		    outerRow = rs->erase(outerRow);
		}
	    } else
		throw std::string("Service name must be an IRI; attempted to call SERVICE ").append(m_VarOrIRIref->toString());
	}
    }

    void ServiceGraphPattern::construct (RdfDB* /* target */, const ResultSet* /* rs */, BNodeEvaluator* /* evaluator */, BasicGraphPattern* /* bgp */) const {
	throw std::string("@@ServiceGraphPattern::construct not yet written");
	// const URI* serviceName = dynamic_cast<const URI*>(m_VarOrIRIref);
	// if (serviceName != NULL) {
	//     /* GRAPH <x> { ?s ?p ?o } */
	//     BasicGraphPattern* bgp = target->ensureGraph(graphName);
	//     m_TableOperation->construct(target, rs, evaluator, bgp);
	// } else {
	//     /* SERVICE ?g { ?s ?p ?o } */
	//     for (ResultSetConstIterator result = rs->begin() ; result != rs->end(); result++) {
	// 	const TTerm* evaldServiceName = m_VarOrIRIref->evalTTerm(*result, evaluator);
	// 	BasicGraphPattern* bgp = target->ensureGraph(evaldServiceName);
	// 	m_TableOperation->construct(target, rs, evaluator, bgp);
	//     }
	// }
    }

    void ServiceGraphPattern::deletePattern (RdfDB* /* target */, const ResultSet* /* rs */, BNodeEvaluator* /* evaluator */, BasicGraphPattern* /* bgp */) const {
	throw std::string("@@ServiceGraphPattern::delete not yet written");
	// const URI* serviceName = dynamic_cast<const URI*>(m_VarOrIRIref);
	// if (serviceName != NULL) {
	//     /* GRAPH <x> { ?s ?p ?o } */
	//     BasicGraphPattern* bgp = target->ensureGraph(graphName);
	//     m_TableOperation->deletePattern(target, rs, evaluator, bgp);
	// } else {
	//     /* SERVICE ?g { ?s ?p ?o } */
	//     for (ResultSetConstIterator result = rs->begin() ; result != rs->end(); result++) {
	// 	const TTerm* evaldServiceName = m_VarOrIRIref->evalTTerm(*result, evaluator);
	// 	BasicGraphPattern* bgp = target->ensureGraph(evaldServiceName);
	// 	m_TableOperation->deletePattern(target, rs, evaluator, bgp);
	//     }
	// }
    }

    void OptionalGraphPattern::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet optRS(*rs); // no AtomFactory
	m_TableOperation->bindVariables(db, &optRS);
	rs->joinIn(&optRS, &m_Expressions, ResultSet::OP_outer);
    }

    void MinusGraphPattern::bindVariables (RdfDB* db, ResultSet* rs) const {
	ResultSet optRS(*rs); // no AtomFactory
	m_TableOperation->bindVariables(db, &optRS);
	rs->joinIn(&optRS, NULL, ResultSet::OP_minus);
    }

    void BasicGraphPattern::construct (BasicGraphPattern* target, const ResultSet* rs, BNodeEvaluator* evaluator) const {
	for (ResultSetConstIterator result = rs->begin() ; result != rs->end(); result++)
	    for (std::vector<const TriplePattern*>::const_iterator triple = m_TriplePatterns.begin();
		 triple != m_TriplePatterns.end(); triple++)
		(*triple)->construct(target, *result, rs->getAtomFactory(), evaluator);
    }

    void BasicGraphPattern::construct (RdfDB* target, const ResultSet* rs, BNodeEvaluator* evaluator, BasicGraphPattern* bgp) const {
	if (bgp == NULL)
	    bgp = target->ensureGraph(NULL);
	construct(bgp, rs, evaluator);
    }

    void BasicGraphPattern::deletePattern (RdfDB* target, const ResultSet* rs, BNodeEvaluator* /* evaluator */, BasicGraphPattern* bgp) const {
	if (bgp == NULL)
	    bgp = target->ensureGraph(NULL);
	for (std::vector<const TriplePattern*>::const_iterator constraint = m_TriplePatterns.begin();
	     constraint != m_TriplePatterns.end(); constraint++) {
	    for (ResultSetConstIterator row = rs->begin() ; row != rs->end(); ++row) {
		for (std::vector<const TriplePattern*>::iterator triple = bgp->m_TriplePatterns.begin();
		     triple != bgp->m_TriplePatterns.end(); ) {
		    ResultSet* island = (*row)->makeResultSet(rs->getAtomFactory());
		    if ((*constraint)->bindVariables(*triple, false, island, *island->begin())) // may need graphVar, graphName?
			triple = bgp->m_TriplePatterns.erase(triple);
		    else
			triple++;
		    delete island;
		}
	    }
	}
    }

    bool TriplePattern::construct (BasicGraphPattern* target, const Result* r, AtomFactory* atomFactory, BNodeEvaluator* evaluator) const {
	bool ret = false;
	const TTerm *s, *p, *o;
	if ((s = m_s->evalTTerm(r, evaluator)) != TTerm::Unbound && 
	    (p = m_p->evalTTerm(r, evaluator)) != TTerm::Unbound && 
	    (o = m_o->evalTTerm(r, evaluator)) != TTerm::Unbound) {
	    if (atomFactory == NULL) {
		if (s == m_s && p == m_p && o == m_o && !weaklyBound)
		    target->addTriplePattern(this);
		else
		    throw(std::runtime_error("TriplePattern::construct requires AtomFactory when constructing new triples."));
	    } else
		  target->addTriplePattern(atomFactory->getTriple(s, p, o));
	}
	return ret;
    }

    TableOperation* TableOperationOnOperation::getDNF ( ) const {
	TableOperation* op = m_TableOperation->getDNF();
	TableDisjunction* disjoints;
	if ((disjoints = dynamic_cast<TableDisjunction*>(op)) == NULL) {
	    return makeANewThis(op);
	}

	/* GRAPH <X> { A || B } => GRAPH <X> { A } || GRAPH <X> { B } 
	 * likewise for OPTIONALS.*/
	TableDisjunction* ret = new TableDisjunction();
	for (std::vector<const TableOperation*>::const_iterator disjoint = disjoints->begin();
	     disjoint != disjoints->end(); disjoint++)
	    ret->addTableOperation(makeANewThis(*disjoint), false);
	disjoints->clear();
	delete disjoints;
	return ret;
    }
    TableOperation::TableOperation (const TableOperation& ref) :
	Base(ref) {
#if 0
	SWObjectDuplicator dup(NULL); // doesn't need to create new atoms.
	for (std::vector<const Filter*>::const_iterator it = ref.m_Filters.begin();
	     it != ref.m_Filters.end(); ++it) {
	    (*it)->express(&dup);
	    m_Filters.push_back(dup.last.filter);
	}
#endif
    }
    std::string TriplePattern::toString (MediaType mediaType, NamespaceMap* namespaces) const {
	std::stringstream s;
	if (mediaType.match("text/turtle")) {
	    s << m_s->toString() << " " << m_p->toString() << " " << m_o->toString() << " ." << std::endl;
	} else {
	    s << "{" << m_s->toString() << " " << m_p->toString() << " " << m_o->toString() << "}";
	}
	return s.str();
    }
    std::string TableOperation::toString (MediaType mediaType, NamespaceMap* namespaces) const {
	SPARQLSerializer s(mediaType, namespaces, "  ", SPARQLSerializer::DEBUG_none, "");
	express(&s);
	return s.str();
    }
    std::string BasicGraphPattern::toString (MediaType mediaType, NamespaceMap* namespaces) const {
	std::stringstream ret;
	if (mediaType.match("text/trig")) {
	    SPARQLSerializer s(mediaType, namespaces, "  ", SPARQLSerializer::DEBUG_none, "");
	    express(&s);
	    ret << s.str();
	} else {
	    for (std::vector<const TriplePattern*>::const_iterator triple = m_TriplePatterns.begin();
		 triple != m_TriplePatterns.end(); triple++)
		ret << (*triple)->toString(mediaType, namespaces);
	}
	return ret.str();
    }
    TableOperation* TableDisjunction::getDNF () const {
	TableDisjunction* ret = new TableDisjunction();
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end(); ++it) {
	    TableOperation* op = (*it)->getDNF();
	    TableDisjunction* disjoints;
	    if ((disjoints = dynamic_cast<TableDisjunction*>(op)) != NULL) {
		for (std::vector<const TableOperation*>::const_iterator disjoint = disjoints->begin();
		     disjoint != disjoints->end(); disjoint++)
		    ret->addTableOperation(*disjoint, true);
		disjoints->clear();
		delete disjoints;
	    } else {
		ret->addTableOperation(op, true);
	    }
	}
	return ret;
    }


    /**
     * DisjointList - compile structure for a disjunctive normal form.
     * @method join takes TableOperations and sorts them into the DisjointList.
     */
    struct ConjointList;
    struct DisjointList;
    std::ostream& operator <<(std::ostream& os, const ConjointList& cl);
    std::ostream& operator <<(std::ostream& os, DisjointList& top);

    TableOperation* _copyTableOperation (const TableOperation& ref) {
	SWObjectDuplicator dup(NULL);
	ref.express(&dup);
	return dup.last.tableOperation;
    }

#if defined(SWIG)
} /* namespace w3c_sw */
namespace std {%template(vector_TableOperationstar) vector<const w3c_sw::TableOperation*>;}
namespace w3c_sw {
#endif /* defined(SWIG) */
    struct ConjointList : public std::vector<const TableOperation*> {

	ConjointList () : std::vector<const TableOperation*>() {  }
	void copy (const ConjointList& ref) {
	    const BasicGraphPattern* bgp;
	    for (std::vector<const TableOperation*>::const_iterator in = ref.begin();
		 in != ref.end(); ++in) {
		if ((bgp = dynamic_cast<const BasicGraphPattern*>(*in)) != NULL)
		    push_back(_copyTableOperation(*bgp));
		else
		    throw std::string("unknown type");
	    }
	}

	void free () {
	    for (std::vector<const TableOperation*>::const_iterator in = begin();
		 in != end(); ++in)
		delete *in;
	}

	TableOperation* toTableOperation () const {
	    if (size() == 0)
		throw std::string("empty ConjointList");
	    if (size() == 1)
		return (TableOperation*)at(0); // !!! Lies
	    TableConjunction* ret = new TableConjunction();
	    for (ConjointList::const_iterator con = begin();
		 con != end(); ++con)
		ret->addTableOperation(*con, false);
	    return ret;
	}

    };

    struct DisjointList;
    std::ostream& operator <<(std::ostream& os, DisjointList& top);
#if defined(SWIG)
} /* namespace w3c_sw */
namespace std {%template(vector_ConjointList) vector<w3c_sw::ConjointList>;}
namespace w3c_sw {
#endif /* defined(SWIG) */
    struct DisjointList : public std::vector<ConjointList> {

	DisjointList () {
	    push_back(ConjointList());
	}

	void free () {
	    for (std::vector<ConjointList>::iterator in = begin();
		 in != end(); ++in)
		in->free();
	}

	void disjoin (const TableDisjunction* ins) {
	    for (DisjointList::iterator dis = begin();
		 dis != end(); ) {
		for (std::vector<const TableOperation*>::const_iterator in = ins->begin();
		     in != ins->end(); ++in) {
		    ConjointList copy;
		    copy.copy(*dis);
		    dis = insert(dis, copy);
		    const TableConjunction* conjoints;
		    const BasicGraphPattern* bgp;
		    if ((conjoints = dynamic_cast<const TableConjunction*>(*in)) != NULL)
			for (std::vector<const TableOperation*>::const_iterator in2 = conjoints->begin();
			     in2 != conjoints->end(); ++in2) {
			    if ((bgp = dynamic_cast<const BasicGraphPattern*>(*in2)) != NULL)
				dis->push_back(_copyTableOperation(*bgp));
			    else
				throw std::string("unknown type");
			}
		    else if ((bgp = dynamic_cast<const BasicGraphPattern*>(*in)) != NULL)
			dis->push_back(_copyTableOperation(*bgp));
		    else
			throw std::string("unknown type");
		    ++dis;
		}
		dis->free();
		dis = erase(dis);
	    }
	}

	void conjoin (const TableConjunction* ins) {
	    for (std::vector<const TableOperation*>::const_iterator in = ins->begin();
		 in != ins->end(); ++in)
		join(*in);
	}

	void add (const BasicGraphPattern* ins) {
	    for (DisjointList::iterator dis = begin();
		 dis != end(); ++dis) {
		dis->push_back(_copyTableOperation(*ins));
	    }
	}

	void join (const TableOperation* ins) {
	    const TableDisjunction* disjoints;
	    const TableConjunction* conjoints;
	    const BasicGraphPattern* bgp;
	    if ((disjoints = dynamic_cast<const TableDisjunction*>(ins)) != NULL)
		disjoin(disjoints);
	    else if ((conjoints = dynamic_cast<const TableConjunction*>(ins)) != NULL)
		conjoin(conjoints);
	    else if ((bgp = dynamic_cast<const BasicGraphPattern*>(ins)) != NULL)
		add(bgp);
	    else
		throw std::string("unknown type");
	}

	TableOperation* toTableOperation () const {
	    if (size() == 1)
		return at(0).size() == 0
		    ? NULL
		    : at(0).toTableOperation();
	    TableDisjunction* ret = new TableDisjunction();
	    for (DisjointList::const_iterator dis = begin();
		 dis != end(); ++dis)
		ret->addTableOperation(dis->toTableOperation(), false);
	    return ret;
	}

    };

    std::ostream& operator << (std::ostream& os, const ConjointList& cl) {
	for (ConjointList::const_iterator con = cl.begin();
	     con != cl.end(); ++con) {
	    if (con != cl.begin())
		os << "�";
	    os << (*con)->toString();
	}
	return os;
    }

    std::ostream& operator << (std::ostream& os, DisjointList& dl) {
	for (DisjointList::const_iterator dis = dl.begin();
	     dis != dl.end(); ++dis) {
	    if (dis != dl.begin())
		os << " | ";
	    os << *dis;
	}
	return os;
    }

    TableOperation* TableConjunction::getDNF () const {
	/* Create a disjunction of conjunctions: (A & B) | (C & D) */
	DisjointList dl;

	/* for each of our elements... */
	for (std::vector<const TableOperation*>::const_iterator it = m_TableOperations.begin();
	     it != m_TableOperations.end(); ++it) {
	    TableOperation* op = (*it)->getDNF();
	    dl.join(op);
	    delete op;
	}
	return dl.toTableOperation();
    }

    TableOperationOnOperation* Filter::makeANewThis (const TableOperation* p_TableOperation) const {
	Filter* ret = new Filter(p_TableOperation);
	SWObjectDuplicator dup(NULL); // doesn't need to create new atoms.
	for (std::vector<const Expression*>::const_iterator it = m_Expressions.begin();
	     it != m_Expressions.end(); ++it) {
	    (*it)->express(&dup);
	    ret->m_Expressions.push_back(dup.last.expression);
	}
	return ret;
    }

    std::ostream& operator<< (std::ostream& os, BasicGraphPattern const& my) {
	SPARQLSerializer s;
	my.express(&s);
	return os << s.str();
    }

    std::ostream& operator<< (std::ostream& os, TableOperation const& my) {
	return os << my.toString();
    }

    std::ostream& operator<< (std::ostream& os, WhereClause const& my) {
	SPARQLSerializer s;
	my.express(&s);
	return os << s.str();
    }

} // namespace w3c_sw

