/* SQLizer.hpp - simple SPARQL serializer for SPARQL compile trees.
 *
 * $Id: SQLizer.hpp,v 1.21 2008-09-09 17:38:19 eric Exp $
 */

#ifndef SQLizer_H
#define SQLizer_H

#include <cstdlib>
#include <limits>
#include <map>
#include "exs.hpp"
#include "POS2BGPMap.hpp"
#include "SPARQLSerializer.hpp"

namespace w3c_sw {

    class SQLizer : public Expressor {

	class AliasAttr {
	public:
	    std::string alias;
	    std::string attr;
	    //	    AliasAttr () {  }
	    AliasAttr (std::string alias, std::string attr) : alias(alias), attr(attr) {  }
	};

	class Constraint {
	protected:
	public:
	    Constraint () {  }
	    virtual ~Constraint () {  }
	};
	class WhereConstraint : public Constraint {
	protected:
	public:
	    WhereConstraint () {  }
	    virtual ~WhereConstraint () {  }
	    virtual std::string toString(std::string pad = "") = 0;
	};
	class ConjunctionConstraint : public WhereConstraint {
	    std::vector<WhereConstraint*> constraints;
	public:
	    ConjunctionConstraint () : WhereConstraint(), constraints() {  }
	    void addConstraint (WhereConstraint* constraint) { constraints.push_back(constraint); }
	    virtual std::string toString (std::string pad) {
		std::stringstream s;
		for (std::vector<WhereConstraint*>::iterator it = constraints.begin();
		     it != constraints.end(); it++) {
		    if (it != constraints.begin()) s << " AND ";
		    s << (*it)->toString(pad);
		}
		return s.str();
	    }
	};
	class EqConstraint : public WhereConstraint {
	    WhereConstraint *left, *right;
	public:
	    EqConstraint () : WhereConstraint(), left(), right() {  }
	    void setLeft (WhereConstraint* constraint) { left = constraint; }
	    void setRight (WhereConstraint* constraint) { right = constraint; }
	    virtual std::string toString (std::string pad) {
		std::stringstream s;
		s << left->toString(pad);
		s << " = ";
		s << right->toString(pad);
		return s.str();
	    }
	};
	class LiteralConstraint : public WhereConstraint {
	    std::string value;
	public:
	    LiteralConstraint (std::string value) : WhereConstraint(), value(value) {  }
	    virtual std::string toString (std::string pad) {
		std::stringstream s;
		s << "\"" << value << "\"";
		return s.str();
	    }
	};
	class AliasAttrConstraint : public WhereConstraint {
	    AliasAttr aattr;
	public:
	    AliasAttrConstraint (AliasAttr aattr) : WhereConstraint(), aattr(aattr) {  }
	    virtual std::string toString (std::string pad) {
		std::stringstream s;
		s << aattr.alias;
		s << ".";
		s << aattr.attr;
		return s.str();
	    }
	};

	class Join {
	    class JoinConstraint : public Constraint {
	    protected:
		std::string myAttr;
	    public:
		JoinConstraint (std::string myAttr) : Constraint(), myAttr(myAttr) {  }
		virtual ~JoinConstraint () {  }
		virtual std::string toString(std::string alias, std::string pad = "") = 0;
	    };
	    class ForeignKeyJoinConstraint : public JoinConstraint {
		std::string otherAlias;
		std::string otherAttr;
	    public:
		ForeignKeyJoinConstraint (std::string myAttr, std::string otherAlias, std::string otherAttr) : JoinConstraint(myAttr), otherAlias(otherAlias), otherAttr(otherAttr) {  }
		virtual std::string toString (std::string alias, std::string) {
		    std::stringstream s;
		    s << alias << "." << myAttr << "=" << otherAlias << "." << otherAttr;
		    return s.str();
		}
	    };
	    class IntegerJoinConstraint : public JoinConstraint {
		int value;
	    public:
		IntegerJoinConstraint (std::string myAttr, int value) : JoinConstraint(myAttr), value(value) {  }
		virtual std::string toString (std::string alias, std::string) {
		    std::stringstream s;
		    s << alias << "." << myAttr << "=" << value;
		    return s.str();
		}
	    };
	    class StringJoinConstraint : public JoinConstraint {
		std::string value;
	    public:
		StringJoinConstraint (std::string myAttr, std::string value) : JoinConstraint(myAttr), value(value) {  }
		virtual std::string toString (std::string alias, std::string) {
		    std::stringstream s;
		    s << alias << "." << myAttr << "=\"" << value << "\"";
		    return s.str();
		}
	    };
	    std::string alias;
	    bool optional;
	    std::vector<JoinConstraint*> constraints;
	public:
	    Join (std::string alias, bool optional) : alias(alias), optional(optional) {  }
	    virtual ~Join () {
		for (std::vector<JoinConstraint*>::iterator it = constraints.begin();
		     it != constraints.end(); ++it)
		    delete *it;
	    }
	    std::string debug_getAlias () { return alias; }
	    virtual std::string getRelationText (std::string pad = "") = 0;
	    std::string toString (std::string* captureConstraints = NULL, std::string pad = "") {
		std::stringstream s;
		if (captureConstraints == NULL) s << endl << pad << "            " << (optional ? "LEFT OUTER JOIN " : "INNER JOIN ");
		s << getRelationText(pad) << " AS " << alias;
		std::stringstream on;
		for (std::vector<JoinConstraint*>::iterator it = constraints.begin();
		     it != constraints.end(); ++it) {
		    if (it != constraints.begin())
			on << " AND ";
		    on << (*it)->toString(alias, pad);
		}
		std::string onStr = on.str();
		if (!onStr.empty()) {
		    if (captureConstraints == NULL)
			s << " ON " << onStr;
		    else
			*captureConstraints = onStr;
		}
		return s.str();
	    }
	    void addForeignKeyJoinConstraint (std::string myAttr, std::string otherAlias, std::string otherAttr) {
		if (alias != otherAlias || myAttr != otherAttr)
		    constraints.push_back(new ForeignKeyJoinConstraint(myAttr, otherAlias, otherAttr));
	    }
	    void addConstantJoinConstraint (std::string myAttr, int value) {
		constraints.push_back(new IntegerJoinConstraint(myAttr, value));
	    }
	    void addConstantJoinConstraint (std::string myAttr, std::string value) {
		constraints.push_back(new StringJoinConstraint(myAttr, value));
	    }
	};

	class TableJoin : public Join {
	    std::string relation;
	protected:
	    virtual std::string getRelationText (std::string) { return relation; }
	public:
	    TableJoin (std::string relation, std::string alias, bool optional) : Join(alias, optional), relation(relation) {  }
	};

	class SQLQuery;
	class SubqueryJoin : public Join {
	    SQLQuery* subquery;
	protected:
	    virtual std::string getRelationText (std::string pad = "") {
		std::stringstream s;
		s << "(" << std::endl << subquery->toString(pad) << std::endl << pad << "             )";
		return s.str();
	    }
	public:
	    SubqueryJoin (SQLQuery* subquery, std::string alias, bool optional) : Join(alias, optional), subquery(subquery) {  }
	    virtual ~SubqueryJoin () { delete subquery; }
	};

	class Attachment {
	protected:
	    std::string name;
	public:
	    Attachment (std::string name) : name(name) {  }
	    virtual ~Attachment () {  }
	    virtual std::string toString(std::string pad = "") = 0;
	    virtual void constrain(AliasAttr aattr, SQLQuery* query) = 0;
	    virtual AliasAttr getAliasAttr () { FAIL("unbound variable"); }
	};

	class TightAttachment : public Attachment {
	    AliasAttr aattr;
	public:
	    TightAttachment (AliasAttr aattr, std::string name) : Attachment(name), aattr(aattr) {  }
	    virtual std::string toString (std::string) {
		std::string ret;
		ret.append(aattr.alias); ret.append("."); ret.append(aattr.attr); ret.append(" AS "); ret.append(name);
		return ret;
	    }
	    virtual void constrain (AliasAttr aattr, SQLQuery* query) {
		query->constrain(aattr, this->aattr);
	    }
	    virtual AliasAttr getAliasAttr () { return aattr; }
	};

	class NullAttachment : public Attachment {
	public:
	    NullAttachment (std::string name) : Attachment(name) {  }
	    virtual std::string toString (std::string) {
		std::string ret;
		ret.append("NULL AS "); ret.append(name);
		return ret;
	    }
	    virtual void constrain (AliasAttr, SQLQuery*) {
		FAIL("trying to constrain against a NullAttachment");
	    }
	};
	class ConstantAttachment : public Attachment {
	    int value;
	public:
	    ConstantAttachment (int value, std::string name) : Attachment(name), value(value) {  }
	    virtual std::string toString (std::string) {
		std::stringstream ret;
		ret << value << " AS " << name;
		return ret.str();
	    }
	    virtual void constrain (AliasAttr, SQLQuery*) {
		FAIL("trying to constrain against a ConstantAttachment");
	    }
	};

	class SQLUnion;
	class SQLQuery {
	protected:
	    SQLQuery* parent;

	    std::map<POS*, map<std::string, std::string> > aliasMap;
	    std::set<string> usedAliases;
	    std::vector<Join*> joins;
	    std::vector<WhereConstraint*> constraints;
	    std::map<std::string, Attachment*> attachments;
	    std::vector<Attachment*> selects;
	    bool distinct;
	    int nextUnionAlias;
	    int nextOptAlias;
	    int limit, offset;

	public:
	    SQLQuery (SQLQuery* parent) : parent(parent), distinct(false), nextUnionAlias(0), nextOptAlias(0), limit(-1), offset(-1) {  }
	    virtual ~SQLQuery () {

		for (std::vector<Join*>::iterator iJoins = joins.begin();
		     iJoins != joins.end(); ++iJoins)
		    delete *iJoins;

		for (std::vector<WhereConstraint*>::iterator iConstraints = constraints.begin();
		     iConstraints != constraints.end(); ++iConstraints)
		    delete *iConstraints;

		for (std::map<string, Attachment*>::iterator iAttachments = attachments.begin();
		     iAttachments != attachments.end(); ++iAttachments)
		    delete iAttachments->second;
	    }
	    void addConstraint (WhereConstraint* constraint) { constraints.push_back(constraint); }
	    virtual std::string toString (std::string pad = "") {
		std::stringstream s;
		s << pad << "SELECT ";
		if (distinct) s << "DISTINCT ";

		/* SELECT attributes */
		for (std::vector<Attachment*>::iterator it = selects.begin();
		     it != selects.end(); ++it) {
		    if (it != selects.begin()) s << ", ";
		    s << (*it)->toString(pad);
		}
		if (selects.begin() == selects.end()) s << "NULL";

		/* JOINs */
		std::string where;
		for (std::vector<Join*>::iterator it = joins.begin();
		     it != joins.end(); ++it)
		    if (it == joins.begin())
			s << endl << pad << "       FROM " << (*it)->toString(&where, pad);
		    else
			s << (*it)->toString(NULL, pad);

		/* WHERE */
		for (std::vector<WhereConstraint*>::iterator it = constraints.begin();
		     it != constraints.end(); ++it)
		    if (it == constraints.begin()) {
			s << std::endl << pad << " WHERE ";
			if (where.length() != 0)
			    s << where << " AND ";
			s << (*it)->toString(pad);
		    } else
			s << "AND" << (*it)->toString(pad);

		if (limit != -1) s << " LIMIT " << limit;
		if (offset != -1) s << " OFFSET " << offset;

		return s.str();
	    }
	    void setDistinct (bool state = true) { distinct = state; }
	    void setLimit (int limit) { this->limit = limit; }
	    void setOffset (int offset) { this->offset = offset; }
	    std::string attachTuple (POS* subject, std::string toRelation) {
		std::map<POS*, map<std::string, std::string> >::iterator byPOS = aliasMap.find(subject);
		if (byPOS != aliasMap.end()) {
		    map<std::string, std::string>::iterator byRelation = aliasMap[subject].find(toRelation);
		    if (byRelation != aliasMap[subject].end())
			return aliasMap[subject][toRelation];
		}
		string aliasName = subject->getTerminal();
		unsigned ordinal = 0;
		while (usedAliases.find(aliasName) != usedAliases.end()) {
		    std::stringstream s;
		    s << subject->getTerminal() << "_" << ++ordinal;
		    aliasName = s.str();
		}
		joins.push_back(new TableJoin(toRelation, aliasName, false));
		usedAliases.insert(aliasName);
		//std::cerr << "SQLQuery " << this << ": attachTuple: " << subject << ", " << toRelation << "." << attribute << " bound to " << aliasName << std::endl;
		aliasMap[subject][toRelation] = aliasName;
		return aliasName;
	    }
	    SQLUnion* makeUnion (std::vector<POS*> corefs) {
		std::stringstream s;
		s << "union" << ++nextUnionAlias;
		SQLUnion* ret = new SQLUnion(this, corefs, s.str());
		joins.push_back(new SubqueryJoin(ret, s.str(), false));		
		return ret;
	    }
	    void attachVariable (AliasAttr aattr, std::string terminal) {
		std::map<string, Attachment*>::iterator it = attachments.find(terminal);
		if (it == attachments.end())
		    attachments[terminal] = new TightAttachment(aattr, terminal);
		else
		    attachments[terminal]->constrain(aattr, this);
	    }
	    AliasAttrConstraint* getVariableConstraint (std::string terminal) {
		std::map<string, Attachment*>::iterator it = attachments.find(terminal);
		if (it == attachments.end())
		    FAIL("can't find variable");
		else
		    return new AliasAttrConstraint(it->second->getAliasAttr());
	    }
	    void selectVariable (std::string terminal) {
		if (attachments.find(terminal) == attachments.end())
		    attachments[terminal] = new NullAttachment(terminal);
		//std::cerr << "selectVariable " << terminal << " attached to " << attachments[terminal]->toString() << std::endl;
		selects.push_back(attachments[terminal]);
	    }
	    void selectConstant (int value, std::string alias) {
		if (attachments.find(alias) == attachments.end())
		    attachments[alias] = new ConstantAttachment(value, alias);
		//std::cerr << "selectVariable " << terminal << " attached to " << attachments[terminal]->toString() << std::endl;
		selects.push_back(attachments[alias]);
	    }
	    /* Always add to the last join unless we figure out a reason this doesn't work. */
	    void constrain (AliasAttr x, AliasAttr y) {
		//std::cerr << "SQLQuery " << this << " constraint: " << x.alias << "." << x.attr << "=" << y.alias << "." << y.attr << std::endl;
		if (joins.back()->debug_getAlias() != x.alias) FAIL("constraint is not for last join");
		joins.back()->addForeignKeyJoinConstraint(x.attr, y.alias, y.attr);
	    }
	    void constrain (AliasAttr aattr, std::string otherAlias, std::string otherAttribute) {
		if (joins.back()->debug_getAlias() != aattr.alias) FAIL("constraint is not for last join");
		joins.back()->addForeignKeyJoinConstraint(aattr.attr, otherAlias, otherAttribute);
	    }
	    void constrain (AliasAttr aattr, std::string value) {
		if (joins.back()->debug_getAlias() != aattr.alias) FAIL("constraint is not for last join");
		joins.back()->addConstantJoinConstraint(aattr.attr, value);
	    }
	    void constrain (AliasAttr aattr, int value) {
		if (joins.back()->debug_getAlias() != aattr.alias) FAIL("constraint is not for last join");
		joins.back()->addConstantJoinConstraint(aattr.attr, value);
	    }
	};

	class SQLDisjoint;
	class SQLUnion : public SQLQuery {
	    std::vector<SQLDisjoint*> disjoints;
	    std::vector<POS*> corefs;
	    std::string name;
	public:
	    SQLUnion (SQLQuery* parent, std::vector<POS*> corefs, std::string name) : 
		SQLQuery(parent), corefs(corefs), name(name)
	    {  }
	    virtual ~SQLUnion () {
		for (std::vector<SQLDisjoint*>::iterator it = disjoints.begin();
		     it != disjoints.end(); ++it)
		    delete *it;
	    }
	    SQLDisjoint* makeDisjoint () {
		SQLDisjoint* ret = new SQLDisjoint(this);
		disjoints.push_back(ret);
		return ret;
	    }
	    void attach () {
		unsigned nextDisjointCardinal = 1;
		for (std::vector<SQLDisjoint*>::iterator dis = disjoints.begin();
		     dis != disjoints.end(); ++dis)
		    (*dis)->selectConstant(nextDisjointCardinal++, "_DISJOINT_");
		for (std::vector<POS*>::iterator it = corefs.begin();
		     it != corefs.end(); ++it) {
		    for (std::vector<SQLDisjoint*>::iterator dis = disjoints.begin();
			 dis != disjoints.end(); ++dis)
			(*dis)->selectVariable((*it)->getTerminal());
		    parent->attachVariable(AliasAttr(name, (*it)->getTerminal()), (*it)->getTerminal());
		}
	    }
	    virtual std::string toString (std::string pad = "") {
		std::stringstream s;
		std::string newPad = pad + "    ";
		for (std::vector<SQLDisjoint*>::iterator it = disjoints.begin();
		     it != disjoints.end(); ++it) {
		    if (it != disjoints.begin())
			s << std::endl << pad << "  UNION" << std::endl;
		    s << (*it)->toString(newPad);
		}
		return s.str();
	    }
	};

	class SQLDisjoint : public SQLQuery {
	    SQLUnion* partOf;
	public:
	    SQLDisjoint (SQLUnion* partOf) : SQLQuery(NULL), partOf(partOf) {  }
	};

	struct nonLocalIdentifierException : StringException {
 	    std::string stem, crack;
	    nonLocalIdentifierException (std::string stem, std::string crack) : 
		StringException(make(stem, crack)), stem(stem), crack(crack) {  }
	    virtual ~nonLocalIdentifierException () throw() {  }
	protected:
	    std::string make (std::string stem, std::string crack) {
		std::stringstream s;
		s << "crack <" << crack << "> is not in the domain of "
		  << "stem <" << stem << ">";
		return s.str();
	    }
	};

	int resolve (std::string crack, std::string* relation, std::string* attribute, int* value = NULL) {
	    std::string valueS;

	    char* delim = value ? nodeDelims : predicateDelims;
	    std::string *strings[] = {relation, attribute, &valueS};
	    if (crack.compare(0, stem.size(), stem) != 0)
		throw(nonLocalIdentifierException(stem, crack));

	    size_t pos = 0;
	    for(std::string::iterator iter=crack.begin() + stem.size();
		iter != crack.end() && pos < (value == NULL ? 2 : 3); ++iter)
		if (*iter==delim[pos])
		    pos += 1;
		else
		    *(strings[pos])+=*iter;

	    if (value != NULL && valueS.size() > 0) {
		char *ep = 0;
		*value = std::strtol(valueS.c_str(), &ep, 10);
	    }

	    return pos+1;
	}
	AliasAttr getPKAttr (std::string alias) { return AliasAttr(alias, "id"); }

	std::string stem;
	/*	AliasContext* curAliases; */
	enum {MODE_outside, MODE_subject, MODE_predicate, MODE_object, MODE_selectVar, MODE_constraint, MODE_overrun} mode;
	SQLQuery* curQuery;
	POS* curSubject;
	AliasAttr curAliasAttr;
	TableOperation* curTableOperation;
	std::string subjectRelation, predicateRelation;
	Consequents* consequentsP;
	VarSet* m_VarSet;
	char* predicateDelims;
	char* nodeDelims;
	WhereConstraint* curConstraint;

    public:
	SQLizer (std::string stem, char predicateDelims[], char nodeDelims[]) : 
	    stem(stem), mode(MODE_outside), curAliasAttr("bogusAlias", "bogusAttr"), 
	    m_VarSet(NULL), predicateDelims(predicateDelims), nodeDelims(nodeDelims)
	{  }
	~SQLizer () { delete curQuery; }

	std::string getSPARQLstring () { return curQuery->toString(); }

	virtual Base* base (std::string productionName) { throw(std::runtime_error(productionName)); };

	virtual URI* uri (std::string terminal) {
	    MARK;
	    std::string relation, attribute;
	    int value;

	    switch (mode) {

	    case MODE_predicate:
		NOW("URI as predicate");
		if (resolve(terminal, &relation, &attribute) != 2) FAIL("malformed predicate");
		curAliasAttr.alias = curQuery->attachTuple(curSubject, relation);
		curAliasAttr.attr = attribute;
		predicateRelation = relation;
		break;

	    case MODE_subject:
		NOW("URI as subject");
		if (resolve(terminal, &relation, &attribute, &value) != 3) FAIL("incomplete key");
		if (predicateRelation != relation)
		    std::cerr << "!Subject relation is " << relation << " while predicate relation is " << predicateRelation << std::endl;
		curQuery->constrain(getPKAttr(curAliasAttr.alias), value);
		break;

	    case MODE_object:
		NOW("URI as object");
		if (resolve(terminal, &relation, &attribute, &value) != 3) FAIL("incomplete key");
		curQuery->constrain(curAliasAttr, value);
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual Variable* variable (std::string terminal) {

	    // enforce coreferences
	    switch (mode) {

	    case MODE_subject:
		NOW("Variable as subject");
		curQuery->attachVariable(getPKAttr(curAliasAttr.alias), terminal);
		break;

	    case MODE_predicate:
		FAIL("No variable predicates, please.");
		break;

	    case MODE_object:
		NOW("Variable as object");
		curQuery->attachVariable(curAliasAttr, terminal);
		break;

	    case MODE_selectVar:
		NOW("URI as selectVar");
		curQuery->selectVariable(terminal);
		break;

	    case MODE_constraint:
		NOW("URI as constraint");
		curConstraint = curQuery->getVariableConstraint(terminal);
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual BNode* bnode (std::string terminal) {

	    // enforce coreferences
	    switch (mode) {

	    case MODE_subject:
		NOW("Variable as subject");
		curQuery->attachVariable(getPKAttr(curAliasAttr.alias), terminal);
		break;

	    case MODE_predicate:
		FAIL("No variable predicates, please.");
		break;

	    case MODE_object:
		NOW("Variable as object");
		curQuery->attachVariable(curAliasAttr, terminal);
		break;

	    case MODE_selectVar:
		FAIL("no told bnodes");
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	/* Literal Map -- http://www.w3.org/2008/07/MappingRules/#litMap !!! not done */
	virtual RDFLiteral* rdfLiteral (std::string terminal, w3c_sw::URI* datatype, w3c_sw::LANGTAG* p_LANGTAG) {
	    MARK;
	    std::string value = terminal;
	    if (datatype != NULL) {
		if (datatype->getTerminal() == "http://www.w3.org/2001/XMLSchema#dateTime") {
		    value.replace(value.find("T"), 1, " ");
		} else {
		    std::cerr << "unknown datatype: " << datatype->getTerminal() << std::endl;
		    FAIL("unknown datatype");
		}
	    }
	    if (p_LANGTAG != NULL) {
		FAIL("how do we literalMap langtags?");
	    }

	    switch (mode) {

	    case MODE_subject:
		NOW("Literal as subject -- odd, but why not?");
		curQuery->constrain(getPKAttr(curAliasAttr.alias), value);
		break;

	    case MODE_predicate:
		FAIL("No literal predicates, please.");
		break;

	    case MODE_object:
		NOW("Literal as object");
		curQuery->constrain(curAliasAttr, value);
		break;

	    case MODE_selectVar:
		NOW("Literal as selectVar");
		curQuery->selectVariable(value);
		break;

	    case MODE_constraint:
		NOW("Literal as constraint");
		curConstraint = new LiteralConstraint(value);
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual NumericRDFLiteral* rdfLiteral (int p_value) {
	    MARK;
	    switch (mode) {

	    case MODE_subject:
		NOW("int as subject -- odd, but why not?");
		curQuery->constrain(getPKAttr(curAliasAttr.alias), p_value);
		break;

	    case MODE_predicate:
		FAIL("No literal predicates, please.");
		break;

	    case MODE_object:
		NOW("int as object");
		curQuery->constrain(curAliasAttr, p_value);
		break;

	    case MODE_selectVar:
		NOW("int as selectVar");
		curQuery->selectConstant(p_value, "__CONSTANT_INT__");
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual NumericRDFLiteral* rdfLiteral (float p_value) {
	    MARK;
	    switch (mode) {

	    case MODE_subject:
		NOW("float as subject -- odd, but why not?");
		curQuery->constrain(getPKAttr(curAliasAttr.alias), p_value);
		break;

	    case MODE_predicate:
		FAIL("No literal predicates, please.");
		break;

	    case MODE_object:
		NOW("float as object");
		curQuery->constrain(curAliasAttr, p_value);
		break;

	    case MODE_selectVar:
		NOW("float as selectVar");
		curQuery->selectConstant(p_value, "__CONSTANT_FLOAT__");
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual NumericRDFLiteral* rdfLiteral (double p_value) {
	    MARK;
	    switch (mode) {

	    case MODE_subject:
		NOW("double as subject -- odd, but why not?");
		curQuery->constrain(getPKAttr(curAliasAttr.alias), p_value);
		break;

	    case MODE_predicate:
		FAIL("No literal predicates, please.");
		break;

	    case MODE_object:
		NOW("double as object");
		curQuery->constrain(curAliasAttr, p_value);
		break;

	    case MODE_selectVar:
		NOW("double as selectVar");
		curQuery->selectConstant(p_value, "__CONSTANT_DOUBLE__");
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual BooleanRDFLiteral* rdfLiteral (bool p_value) {
	    MARK;
	    switch (mode) {

	    case MODE_subject:
		NOW("bool as subject -- odd, but why not?");
		curQuery->constrain(getPKAttr(curAliasAttr.alias), p_value);
		break;

	    case MODE_predicate:
		FAIL("No literal predicates, please.");
		break;

	    case MODE_object:
		NOW("bool as object");
		curQuery->constrain(curAliasAttr, p_value);
		break;

	    case MODE_selectVar:
		NOW("bool as selectVar");
		curQuery->selectConstant(p_value, "__CONSTANT_BOOL__");
		break;

	    default:
		FAIL("wierd state");
	    }
	    return NULL;
	}
	virtual NULLpos* nullpos () {
	    return NULL;
	}
	virtual TriplePattern* triplePattern (w3c_sw::POS* p_s, w3c_sw::POS* p_p, w3c_sw::POS* p_o) {
	    curSubject = p_s;
	    START("checking predicate");
	    mode = MODE_predicate;
	    p_p->express(this);

	    NOW("checking subject");
	    mode = MODE_subject;
	    p_s->express(this);


	    NOW("checking object");
	    mode = MODE_object;
	    p_o->express(this);

	    mode = MODE_outside;
	    return NULL;
	}
	virtual Filter* filter (w3c_sw::Expression* p_Constraint) {
	    p_Constraint->express(this);
	    return NULL;
	}
	void _BasicGraphPattern (ProductionVector<w3c_sw::TriplePattern*>* p_TriplePatterns, ProductionVector<w3c_sw::Filter*>* p_Filters) {
	    MARK;
	    for (std::vector<TriplePattern*>::iterator tripleIt = p_TriplePatterns->begin();
		 tripleIt != p_TriplePatterns->end(); ++tripleIt)
		try {
		    (*tripleIt)->express(this);
		} catch (nonLocalIdentifierException& e) {
		    SPARQLSerializer sparqlizer("  ");
		    (*tripleIt)->express(&sparqlizer);
		    std::cerr << "pattern {" << sparqlizer.getSPARQLstring() << "} is not handled by stem " << stem << " because " << e.what() << endl;
		}
	    NOW("bgp filters");
	    for (std::vector<Filter*>::iterator filterIt = p_Filters->begin();
		 filterIt != p_Filters->end(); ++filterIt)
		try {
		    (*filterIt)->express(this);
		    curQuery->addConstraint(curConstraint);
		} catch (nonLocalIdentifierException& e) {
		    SPARQLSerializer sparqlizer("  ");
		    (*filterIt)->express(&sparqlizer);
		    std::cerr << "filter {" << sparqlizer.getSPARQLstring() << "} is not handled by stem " << stem << " because " << e.what() << endl;
		}
	}
	virtual NamedGraphPattern* namedGraphPattern (w3c_sw::POS*, bool /*p_allOpts*/, ProductionVector<w3c_sw::TriplePattern*>* p_TriplePatterns, ProductionVector<w3c_sw::Filter*>* p_Filters) {
	    MARK;
	    _BasicGraphPattern(p_TriplePatterns, p_Filters);
	    return NULL;
	}
	virtual DefaultGraphPattern* defaultGraphPattern (bool /*p_allOpts*/, ProductionVector<w3c_sw::TriplePattern*>* p_TriplePatterns, ProductionVector<w3c_sw::Filter*>* p_Filters) {
	    MARK;
	    _BasicGraphPattern(p_TriplePatterns, p_Filters);
	    return NULL;
	}
	virtual TableDisjunction* tableDisjunction (ProductionVector<w3c_sw::TableOperation*>* p_TableOperations, ProductionVector<w3c_sw::Filter*>* p_Filters) {
	    SQLQuery* parent = curQuery;
	    SQLUnion* disjunction = parent->makeUnion(consequentsP->entriesFor(curTableOperation));
	    for (std::vector<TableOperation*>::iterator it = p_TableOperations->begin();
		 it != p_TableOperations->end(); ++it) {
		MARK;
		curQuery = disjunction->makeDisjoint();
		curTableOperation = *it;
		curTableOperation->express(this);
	    }
	    disjunction->attach();
	    p_Filters->express(this);
	    curQuery = parent;
	    return NULL;
	}
	virtual TableConjunction* tableConjunction (ProductionVector<w3c_sw::TableOperation*>* p_TableOperations, ProductionVector<w3c_sw::Filter*>* p_Filters) {
	    MARK;
	    for (std::vector<TableOperation*>::iterator it = p_TableOperations->begin();
		 it != p_TableOperations->end(); ++it) {
		MARK;
		curTableOperation = *it;
		curTableOperation->express(this);
	    }
	    p_Filters->express(this);
	    return NULL;
	}
	virtual OptionalGraphPattern* optionalGraphPattern (w3c_sw::TableOperation* p_GroupGraphPattern) {
	    MARK;
	    curTableOperation = p_GroupGraphPattern; 
	    curTableOperation->express(this);
	    return NULL;
	}
	virtual GraphGraphPattern* graphGraphPattern (w3c_sw::POS* p_POS, w3c_sw::TableOperation* p_GroupGraphPattern) {
	    FAIL("don't do federation with GraphGraphPatterns yet");
	    p_POS->express(this);
	    curTableOperation = p_GroupGraphPattern;
	    curTableOperation->express(this);
	    return NULL;
	}
	virtual POSList* posList (ProductionVector<w3c_sw::POS*>* p_POSs) {
	    for (std::vector<POS*>::iterator it = p_POSs->begin();
		 it != p_POSs->end(); ++it)
		(*it)->express(this);
	    return NULL;
	}
	virtual StarVarSet* starVarSet () {
	    FAIL("need to select all pertinent vars");
	    return NULL;
	}
	virtual DefaultGraphClause* defaultGraphClause (w3c_sw::POS* p_IRIref) {
	    p_IRIref->express(this);
	    return NULL;
	}
	virtual NamedGraphClause* namedGraphClause (w3c_sw::POS* p_IRIref) {
	    p_IRIref->express(this);
	    return NULL;
	}
	virtual SolutionModifier* solutionModifier (std::vector<s_OrderConditionPair>* p_OrderConditions, int p_limit, int p_offset) {
	    if (p_limit != LIMIT_None) curQuery->setLimit(p_limit);
	    if (p_offset != OFFSET_None) curQuery->setOffset(p_offset);
	    if (p_OrderConditions)
		for (std::vector<s_OrderConditionPair>::iterator it = p_OrderConditions->begin();
		     it != p_OrderConditions->end(); ++it)
		    /*bool desc = p_OrderConditions->at(i).ascOrDesc == w3c_sw::ORDER_Desc;*/
		    // !!!
		    it->expression->express(this);
	    return NULL;
	}
	virtual Binding* binding (ProductionVector<w3c_sw::POS*>* values) {//!!!
	    // !!!
	    for (std::vector<POS*>::iterator it = values->begin();
		 it != values->end(); ++it)
		(*it)->express(this);
	    return NULL;
	}
	virtual BindingClause* bindingClause (w3c_sw::POSList* p_Vars, ProductionVector<w3c_sw::Binding*>* p_Bindings) {
	    p_Vars->express(this);
	    p_Bindings->ProductionVector<w3c_sw::Binding*>::express(this);
	    return NULL;
	}
	virtual WhereClause* whereClause (w3c_sw::TableOperation* p_GroupGraphPattern, w3c_sw::BindingClause* p_BindingClause) {
	    START("p_GroupGraphPattern");
	    Consequents consequents(p_GroupGraphPattern, m_VarSet);
	    consequentsP = &consequents;
	    curTableOperation = p_GroupGraphPattern;
	    curTableOperation->express(this);
	    if (p_BindingClause) p_BindingClause->express(this);
	    return NULL;
	}
	virtual Select* select (w3c_sw::e_distinctness p_distinctness, w3c_sw::VarSet* p_VarSet, ProductionVector<w3c_sw::DatasetClause*>* p_DatasetClauses, w3c_sw::WhereClause* p_WhereClause, w3c_sw::SolutionModifier* p_SolutionModifier) {
	    START("cracking select clause");
	    curQuery = new SQLQuery(NULL);
	    m_VarSet = p_VarSet;
	    if (p_distinctness == w3c_sw::DIST_distinct) curQuery->setDistinct(true);
	    //if (p_distinctness == w3c_sw::DIST_reduced) ...
	    if (p_DatasetClauses->size() > 0) FAIL("don't know what to do with DatasetClauses");
	    NOW("p_WhereClause");
	    p_WhereClause->express(this);
	    //p_SolutionModifier->express(this);
	    mode = MODE_selectVar;
	    p_VarSet->express(this);
	    return NULL;
	}
	virtual Construct* construct (w3c_sw::DefaultGraphPattern* p_ConstructTemplate, ProductionVector<w3c_sw::DatasetClause*>* p_DatasetClauses, w3c_sw::WhereClause* p_WhereClause, w3c_sw::SolutionModifier* p_SolutionModifier) {
	    FAIL("CONSTRUCT");
	    p_ConstructTemplate->express(this);
	    p_DatasetClauses->express(this);
	    p_WhereClause->express(this);
	    p_SolutionModifier->express(this);
	    return NULL;
	}
	virtual Describe* describe (w3c_sw::VarSet* p_VarSet, ProductionVector<w3c_sw::DatasetClause*>* p_DatasetClauses, w3c_sw::WhereClause* p_WhereClause, w3c_sw::SolutionModifier* p_SolutionModifier) {
	    FAIL("DESCRIBE");
	    p_VarSet->express(this);
	    p_DatasetClauses->express(this);
	    p_WhereClause->express(this);
	    p_SolutionModifier->express(this);
	    return NULL;
	}
	virtual Ask* ask (ProductionVector<w3c_sw::DatasetClause*>* p_DatasetClauses, w3c_sw::WhereClause* p_WhereClause) {
	    FAIL("ASK");
	    p_DatasetClauses->express(this);
	    p_WhereClause->express(this);
	    return NULL;
	}
	virtual Replace* replace (w3c_sw::WhereClause* p_WhereClause, w3c_sw::TableOperation* p_GraphTemplate) {
	    FAIL("REPLACE");
	    p_WhereClause->express(this);
	    p_GraphTemplate->express(this);
	    return NULL;
	}
	virtual Insert* insert (w3c_sw::TableOperation* p_GraphTemplate, w3c_sw::WhereClause* p_WhereClause) {
	    FAIL("INSERT {");
	    p_GraphTemplate->express(this);
	    if (p_WhereClause) p_WhereClause->express(this);
	    return NULL;
	}
	virtual Delete* del (w3c_sw::TableOperation* p_GraphTemplate, w3c_sw::WhereClause* p_WhereClause) {
	    FAIL("DELET");
	    p_GraphTemplate->express(this);
	    p_WhereClause->express(this);
	    return NULL;
	}
	virtual Load* load (ProductionVector<w3c_sw::URI*>* p_IRIrefs, w3c_sw::URI* p_into) {
	    FAIL("LOAD");
	    p_IRIrefs->express(this);
	    p_into->express(this);
	    return NULL;
	}
	virtual Clear* clear (w3c_sw::URI* p__QGraphIRI_E_Opt) {
	    FAIL("CLEAR");
	    p__QGraphIRI_E_Opt->express(this);
	    return NULL;
	}
	virtual Create* create (w3c_sw::e_Silence p_Silence, w3c_sw::URI* p_GraphIRI) {
	    FAIL("CREATE");
	    if (p_Silence != w3c_sw::SILENT_Yes) ;// !!!
	    p_GraphIRI->express(this);
	    return NULL;
	}
	virtual Drop* drop (w3c_sw::e_Silence p_Silence, w3c_sw::URI* p_GraphIRI) {
	    if (p_Silence != w3c_sw::SILENT_Yes) ;// !!!
	    p_GraphIRI->express(this);
	    return NULL;
	}
	virtual VarExpression* varExpression (w3c_sw::Variable* p_Variable) {
	    MARK;
	    mode = MODE_constraint;
	    p_Variable->express(this);
	    return NULL;
	}
	virtual LiteralExpression* literalExpression (w3c_sw::RDFLiteral* p_RDFLiteral) {
	    MARK;
	    p_RDFLiteral->express(this);
	    return NULL;
	}
	virtual BooleanExpression* booleanExpression (w3c_sw::BooleanRDFLiteral* p_BooleanRDFLiteral) {
	    MARK;
	    p_BooleanRDFLiteral->express(this);
	    return NULL;
	}
	virtual URIExpression* uriExpression (w3c_sw::URI* p_URI) {
	    MARK;
	    p_URI->express(this);
	    return NULL;
	}
	virtual ArgList* argList (ProductionVector<w3c_sw::Expression*>* p__O_QNIL_E_Or_QGT_LPAREN_E_S_QExpression_E_S_QGT_COMMA_E_S_QExpression_E_Star_S_QGT_RPAREN_E_C) {
	    MARK;
	    p__O_QNIL_E_Or_QGT_LPAREN_E_S_QExpression_E_S_QGT_COMMA_E_S_QExpression_E_Star_S_QGT_RPAREN_E_C->express(this);
	    return NULL;
	}
	// !!!
	virtual FunctionCall* functionCall (w3c_sw::URI* p_IRIref, w3c_sw::ArgList* p_ArgList) {
	    MARK;
	    p_IRIref->express(this);
	    p_ArgList->express(this);
	    return NULL;
	}
	virtual FunctionCallExpression* functionCallExpression (w3c_sw::FunctionCall* p_FunctionCall) {
	    MARK;
	    p_FunctionCall->express(this);
	    return NULL;
	}
	/* Expressions */
	virtual BooleanNegation* booleanNegation (w3c_sw::Expression* p_Expression) {
	    MARK;
	    p_Expression->express(this);
	    return NULL;
	}
	virtual ArithmeticNegation* arithmeticNegation (w3c_sw::Expression* p_Expression) {
	    MARK;
	    p_Expression->express(this);
	    return NULL;
	}
	virtual ArithmeticInverse* arithmeticInverse (w3c_sw::Expression* p_Expression) {
	    MARK;
	    p_Expression->express(this);
	    return NULL;
	}
	virtual BooleanConjunction* booleanConjunction (ProductionVector<w3c_sw::Expression*>* p_Expressions) {
	    MARK;
	    ConjunctionConstraint* conj = new ConjunctionConstraint();
	    for (std::vector<Expression*>::iterator it = p_Expressions->begin();
		 it != p_Expressions->end(); ++it) {
		(*it)->express(this);
		conj->addConstraint(curConstraint);
	    }
	    curConstraint = conj;
	    return NULL;
	}
	virtual BooleanDisjunction* booleanDisjunction (ProductionVector<w3c_sw::Expression*>* p_Expressions) {
	    MARK;
	    for (std::vector<Expression*>::iterator it = p_Expressions->begin();
		 it != p_Expressions->end(); ++it)
		(*it)->express(this);
	    return NULL;
	}
	virtual ArithmeticSum* arithmeticSum (ProductionVector<w3c_sw::Expression*>* p_Expressions) {
	    MARK;
	    for (std::vector<Expression*>::iterator it = p_Expressions->begin();
		 it != p_Expressions->end(); ++it)
		(*it)->express(this);
	    return NULL;
	}
	virtual ArithmeticProduct* arithmeticProduct (ProductionVector<w3c_sw::Expression*>* p_Expressions) {
	    MARK;
	    for (std::vector<Expression*>::iterator it = p_Expressions->begin();

		 it != p_Expressions->end(); ++it)
		(*it)->express(this);
	    return NULL;
	}
	virtual BooleanEQ* booleanEQ (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    EqConstraint* c = new EqConstraint();
	    p_left->express(this);
	    c->setLeft(curConstraint);
	    p_right->express(this);
	    c->setRight(curConstraint);
	    curConstraint = c;
	    return NULL;
	}
	virtual BooleanNE* booleanNE (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    p_left->express(this);
	    p_right->express(this);
	    return NULL;
	}
	virtual BooleanLT* booleanLT (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    p_left->express(this);
	    p_right->express(this);
	    return NULL;
	}
	virtual BooleanGT* booleanGT (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    p_left->express(this);
	    p_right->express(this);
	    return NULL;
	}
	virtual BooleanLE* booleanLE (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    p_left->express(this);
	    p_right->express(this);
	    return NULL;
	}
	virtual BooleanGE* booleanGE (w3c_sw::Expression* p_left, w3c_sw::Expression* p_right) {
	    MARK;
	    p_left->express(this);
	    p_right->express(this);
	    return NULL;
	}
	virtual ComparatorExpression* comparatorExpression (w3c_sw::BooleanComparator* p_BooleanComparator) {
	    MARK;
	    p_BooleanComparator->express(this);
	    return NULL;
	}
	virtual NumberExpression* numberExpression (w3c_sw::NumericRDFLiteral* p_NumericRDFLiteral) {
	    MARK;
	    p_NumericRDFLiteral->express(this);
	    return NULL;
	}
    };

} // namespace w3c_sw

#endif // SQLizer_H

