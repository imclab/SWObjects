/* RuleInverter.hpp - create a SPARQL CONSTRUCT rule that follows 
 * http://www.w3.org/2008/07/MappingRules/#_02
 *
 * $Id: RuleInverter.hpp,v 1.11 2008-10-14 12:05:14 eric Exp $
 */

#ifndef RuleInverter_H
#define RuleInverter_H

#include "SWObjectDuplicator.hpp"
#include "POS2BGPMap.hpp"
#include "SPARQLSerializer.hpp" // for debugging output
#include <set>

namespace w3c_sw {

    class OperationResultSet : public ResultSet {
    protected:
	TableDisjunction* constructed;
    public:
	OperationResultSet (TableDisjunction* constructed) : ResultSet(), constructed(constructed) {  }
	void addTableOperation (TableOperation* op) { constructed->addTableOperation(op); }
    };

    /* MappingConstruct — extends Construct::execute to peform steps 4 through 8
     *                    in http://www.w3.org/2008/07/MappingRules/#_04 .
     */
    class MappingConstruct : public Construct {

	/* MappedDuplicator — 
	 * • reproduce all portions of the constructRuleBodyAsConsequent which
	 *   are implicated in constructed patterns which might be matched by
	 *   the user's query.
	 * • substituted variables and constants from the user query by calling
         *   construct on each triple pattern.
	 */
	class MappedDuplicator : public SWObjectDuplicator {

	protected:
	    ConsequentMap* includeRequiredness;
	    Result* row;
	public:
	    MappedDuplicator (POSFactory* posFactory, Result* row, ConsequentMap* includeRequiredness) : SWObjectDuplicator(posFactory), includeRequiredness(includeRequiredness), row(row) {  }
	    TableOperation* getTableOperation () { return last.tableOperation; }


	    virtual void _TriplePatterns (ProductionVector<TriplePattern*>* p_TriplePatterns, BasicGraphPattern* p) {
		for (std::vector<TriplePattern*>::iterator triple = p_TriplePatterns->begin();
		     triple != p_TriplePatterns->end(); triple++)
		    (*triple)->construct(p, row);
	    }

	    /* Overload SWObjectDuplicator::_TableOperations to handle tree depletion. */
	    virtual void _TableOperations (ProductionVector<TableOperation*>* p_TableOperations, TableJunction* j) {
		for (std::vector<TableOperation*>::iterator it = p_TableOperations->begin();
		     it != p_TableOperations->end(); it++) {
		    last.tableOperation = NULL;
		    (*it)->express(this);
		    if (last.tableOperation != NULL)
			j->addTableOperation(last.tableOperation);
		}
	    }

	    virtual void namedGraphPattern999 (NamedGraphPattern* self, w3c_sw::POS* p_name, bool p_allOpts, ProductionVector<w3c_sw::TriplePattern*>* p_TriplePatterns, ProductionVector<w3c_sw::Filter*>* p_Filters) {
		last.tableOperation = NULL;
		GraphInclusion s = includeRequiredness->getOperationStrength(self);
		if (s != GraphInclusion_NONE) {
		    SWObjectDuplicator::namedGraphPattern (self, p_name, p_allOpts, p_TriplePatterns, p_Filters);
		}
	    }
	    virtual void defaultGraphPattern999 (DefaultGraphPattern* self, bool p_allOpts, ProductionVector<w3c_sw::TriplePattern*>* p_TriplePatterns, ProductionVector<w3c_sw::Filter*>* p_Filters) {
		last.tableOperation = NULL;
		GraphInclusion s = includeRequiredness->getOperationStrength(self);
		if (s != GraphInclusion_NONE) {
		    SWObjectDuplicator::defaultGraphPattern (self, p_allOpts, p_TriplePatterns, p_Filters);
		}
	    }
	    virtual void tableConjunction999 (TableConjunction* self, ProductionVector<w3c_sw::TableOperation*>* p_TableOperations, ProductionVector<w3c_sw::Filter*>* p_Filters) {
		last.tableOperation = NULL;
		GraphInclusion s = includeRequiredness->getOperationStrength(self);
		if (s != GraphInclusion_NONE) {
		    SWObjectDuplicator::tableConjunction (self, p_TableOperations, p_Filters);
		}
	    }
	    virtual void tableDisjunction999 (TableDisjunction* self, ProductionVector<w3c_sw::TableOperation*>* p_TableOperations, ProductionVector<w3c_sw::Filter*>* p_Filters) {
		last.tableOperation = NULL;
		GraphInclusion s = includeRequiredness->getOperationStrength(self);
		if (s != GraphInclusion_NONE) {
		    SWObjectDuplicator::tableDisjunction (self, p_TableOperations, p_Filters);
		}
	    }
	    virtual void optionalGraphPattern (OptionalGraphPattern* self, TableOperation* p_GroupGraphPattern) {
		last.tableOperation = NULL;
		GraphInclusion s = includeRequiredness->getOperationStrength(p_GroupGraphPattern);
		if (s != GraphInclusion_NONE) {
		    if (s == GraphInclusion_STRONG)
			// let p_GroupGraphPattern set last.tableOperation
			p_GroupGraphPattern->express(this);
		    else
			SWObjectDuplicator::optionalGraphPattern(self, p_GroupGraphPattern);
		}
	    }
	    virtual void graphGraphPattern999 (GraphGraphPattern* self, w3c_sw::POS* p_POS, w3c_sw::TableOperation* p_GroupGraphPattern) {
		FAIL("don't know how to deal with a graphGraphPattern in a stem query");
	    }
	};


    private:
	TableOperation* constructRuleBodyAsConsequent;
	Consequents consequents;
	POSFactory* posFactory;

    public:
	MappingConstruct (TableOperation* constructRuleBodyAsConsequent, ProductionVector<DatasetClause*>* p_DatasetClauses, 
			  WhereClause* constructRuleHeadAsPattern, SolutionModifier* p_SolutionModifier, POSFactory* posFactory, std::ostream* debugStream) : 
	    Construct(NULL, p_DatasetClauses, constructRuleHeadAsPattern, p_SolutionModifier), 
	    constructRuleBodyAsConsequent(constructRuleBodyAsConsequent), consequents(constructRuleBodyAsConsequent, NULL, debugStream), posFactory(posFactory)
	{  }
	~MappingConstruct () {
	    delete constructRuleBodyAsConsequent;
	}
	virtual OperationResultSet* execute (RdfDB* userQueryAsAssertions, ResultSet* rs = NULL) {
	    OperationResultSet* opRS = dynamic_cast<OperationResultSet*>(rs);
	    if (opRS == NULL)
		throw(std::runtime_error("MappingConstrucs need a result set.")); // @@ shouldn't happen? consequents[pos][bgp] = false;

	    /* 04 — Execute the query C on the query disjoint D, producing a result set RScd.
	     * http://www.w3.org/2008/07/MappingRules/#_04
	     */
	    //SPARQLSerializer sQ; m_WhereClause->express(&sQ); std::cerr << "Query: " << std::endl << sQ.getSPARQLstring() << std::endl;
	    //SPARQLSerializer sD; userQueryAsAssertions->express(&sD); std::cerr << "Data: " << std::endl << sD.getSPARQLstring() << std::endl;
	    m_WhereClause->bindVariables(userQueryAsAssertions, opRS);
	    std::cerr << "Results:" << std::endl << opRS->toString() << std::endl;
	    //XMLSerializer xs; opRS->toXml(&xs);
	    //std::cerr << "Results:" << std::endl << xs.getXMLstring() << std::endl;

	    /* 05 — For each rule solution S in RScd:
	     * http://www.w3.org/2008/07/MappingRules/#_05
	     */

	    TableConjunction* patternSpanningRows = new TableConjunction();
	    for (ResultSetIterator row = opRS->begin() ; row != opRS->end(); ++row) {

		/* 06 — Scan each basic graph pattern GA in the antecedent graph pattern A for variables in triple patterns:
		 * http://www.w3.org/2008/07/MappingRules/#_06
		 */
		/* Set of { BGP => optional } associations to indicate if the BGP is optional. */
		ConsequentMap includeRequiredness = consequents.getIncludeRequiredness(opRS, row, posFactory);

		/* 07 — Substitute the values in S for the variables in A.
		 * 08 — Create a stem query disjoint DQS which is a reproduction of the mapping rule antecedent A
		 * http://www.w3.org/2008/07/MappingRules/#_07
		 */
		MappedDuplicator e(posFactory, *row, &includeRequiredness);
		constructRuleBodyAsConsequent->express(&e);
		TableOperation* t = e.getTableOperation();
		if (t != NULL)
		    patternSpanningRows->addTableOperation(t);
		//SPARQLSerializer s2; e.getTableOperation()->express(&s2); std::cerr << "CONSTRUCTED: " << s2.getSPARQLstring() << std::endl;
	    }
	    opRS->addTableOperation(patternSpanningRows->simplify());
	    return opRS;
	}
    };

    class RuleInverter : public SWObjectDuplicator {
    protected:
	DefaultGraphPattern* constructRuleHead;
	TableOperation* constructRuleBody;
	MappingConstruct* m_Construct;
	std::ostream* debugStream;
	bool inRuleBody;
    public:
	RuleInverter (POSFactory* posFactory, std::ostream* debugStream = NULL) : 
	    SWObjectDuplicator(posFactory), debugStream(debugStream), inRuleBody(false) {  }

	MappingConstruct* getConstruct() { return m_Construct; }

	/* Create BasicGraphPatterns (named and default) with a flag
	 * indicating the special semantics of all triples being
	 * optional (03).
	 */
	virtual void namedGraphPattern (NamedGraphPattern*, POS* p_name, bool /*p_allOpts*/, ProductionVector<TriplePattern*>* p_TriplePatterns, ProductionVector<Filter*>* p_Filters) {
	    p_name->express(this);
	    NamedGraphPattern* ret = new NamedGraphPattern(last.posz.pos, inRuleBody); // allOpts = true when in rule body
	    _TriplePatterns(p_TriplePatterns, ret);
	    _Filters(p_Filters, ret);
	    last.tableOperation = ret;
	}
	virtual void defaultGraphPattern (DefaultGraphPattern*, bool /*p_allOpts*/, ProductionVector<TriplePattern*>* p_TriplePatterns, ProductionVector<Filter*>* p_Filters) {
	    DefaultGraphPattern* ret = new DefaultGraphPattern(inRuleBody); // allOpts = true when in rule body
	    _TriplePatterns(p_TriplePatterns, ret);
	    _Filters(p_Filters, ret);
	    last.tableOperation = ret;
	}

	virtual void whereClause (WhereClause*, TableOperation* p_GroupGraphPattern, BindingClause* p_BindingClause) {
	    if (p_BindingClause != NULL)
		throw(std::runtime_error("Don't know how to invert a Construct with a BindingClause."));

	    /* store the original antecedent (p_GroupGraphPattern) and create
	     * a new graph pattern with the original consequent
	     * (constructRuleHead).
	     */
	    constructRuleBody = p_GroupGraphPattern; // @@@
	    constructRuleHead->express(this);
	    TableOperation* op = last.tableOperation;
	    last.bindingClause = NULL;
	    if (p_BindingClause != NULL)
		p_BindingClause->express(this);
	    last.whereClause = new WhereClause(op, last.bindingClause);
	}

	virtual void construct (Construct*, DefaultGraphPattern* p_ConstructTemplate, ProductionVector<DatasetClause*>* p_DatasetClauses, WhereClause* p_WhereClause, SolutionModifier* p_SolutionModifier) {
	    if (p_DatasetClauses->size() != 0)
		throw(std::runtime_error("Don't know how to invert a Construct with a DatasetClauses."));

	    /* Record the current CONSTRUCT rule head.
	     * Expressing the WhereClause builds a new WhereClause based on
	     * constructRuleHead and sets constructRuleBody to the graph pattern
	     * of the CONSTRUCT WhereClause.
	     */
	    constructRuleHead = p_ConstructTemplate;
	    inRuleBody = true;
	    p_WhereClause->express(this);
	    inRuleBody = false;
	    WhereClause* constructRuleHeadAsPattern = last.whereClause;

	    /* create a new CONSTRUCT with the consequent of the old
	     * query (constructRuleHead) treated as where clause.
	     *
	     * # 03 — Treat C as a query, each triple being optional.
	     * http://www.w3.org/2008/07/MappingRules/#_03
	     */
	    constructRuleBody->express(this); // sets last.tableOperation
	    TableOperation* constructRuleBodyAsConsequent = last.tableOperation;
	    if (debugStream != NULL) {
		SPARQLSerializer sparqlizer("  ", SPARQLSerializer::DEBUG_graphs);
		constructRuleBodyAsConsequent->express(&sparqlizer);
		*debugStream << "product rule head (SPARQL):" << endl << sparqlizer.getSPARQLstring() << endl;
	    }
	    p_SolutionModifier->express(this);

	    m_Construct = new MappingConstruct(constructRuleBodyAsConsequent,	 // consequent of new mapping rule
					       _DatasetClauses(p_DatasetClauses),//
					       constructRuleHeadAsPattern,	 // antecedent of new mapping rule
					       last.solutionModifier, 		 //
					       posFactory, debugStream);
	}

	/* RuleInverter only works on CONSTRUCTs. All other verbs
	 * get a run-time error. (A compile-time error would be nice, but the
	 * expressor interface prevents that.
	 */
	virtual void select (Select*, e_distinctness, VarSet*, ProductionVector<DatasetClause*>*, WhereClause*, SolutionModifier*) {
	    throw(std::runtime_error("RuleInverter only works on CONSTRUCTs."));
	}
	// @@ should be similar errors for ASK, DESCRIBE and all SPARUL verbs.

    };

} // namespace w3c_sw

#endif // RuleInverter_H

