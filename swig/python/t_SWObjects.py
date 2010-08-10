#!/usr/bin/python
# 
# 

import unittest
import SWObjects

class TestSWObjects(unittest.TestCase):

    def setUp (self):
        11

    def test_constants (self):
        # Test access to constants.
        self.assertEqual(SWObjects.cvar.NS_xml, "http://www.w3.org/XML/1998/namespace")

    def test_type_integrity (self):
        DB = SWObjects.RdfDB()
        self.assertRaises(TypeError, DB.ensureGraph, "blah")

    def test_turtleParser (self):
        # Test Turtle parser .
        F = SWObjects.AtomFactory()
        manualDB = SWObjects.RdfDB()
        manDefault = manualDB.ensureGraph(SWObjects.cvar.DefaultGraph)
        manDefault.addTriplePattern(F.getTriple(
                F.getURI("s" ), 
                F.getURI("p1"), 
                F.getURI("o1")
                ))
        bnodeMap = SWObjects.String2BNode()
        F.parseNTriples(manDefault, 
                        "<s> <p2> <o2> ."
                        "<s> <p2> <o3> .", bnodeMap);
        # print "manualDB: ", manualDB.toString()
        parsedDB = SWObjects.RdfDB()
        tparser = SWObjects.TurtleSDriver("", F)
        tparser.setGraph(parsedDB.ensureGraph(None)) # None = SWObjects.cvar.DefaultGraph
        tparser.parse(SWObjects.IStreamContext(
                "<s> <p1> <o1> ; <p2> <o2> ; <p2> <o3> .",
                SWObjects.StreamContextIstream.STRING))
        # print "parsedDB: ", parsedDB.toString()
        self.assertEqual(manualDB, parsedDB)

        different = SWObjects.RdfDB()
        tparser.setGraph(different.ensureGraph(None))
        tparser.parse(SWObjects.IStreamContext(
                "<s2> <p1> <o1> ; <p2> <o2> ; <p2> <o2> .",
                SWObjects.StreamContextIstream.STRING))
        # print "different: ", different.toString()
        self.assertNotEqual(parsedDB, different)


    def test_trigParser (self):
        # Test Trig parser .
        F = SWObjects.AtomFactory()
        manualDB = SWObjects.RdfDB()
        manDefault = manualDB.ensureGraph(None)
        bnodeMap = SWObjects.String2BNode()
        F.parseNTriples(manDefault, "<s> <p1> <o1> .", bnodeMap);
        manG = manualDB.ensureGraph(F.getURI("g"))
        F.parseNTriples(manG, "<s> <p2> <o2> .", bnodeMap);
        # print "manualDB: ", manualDB.toString()
        parsedDB = SWObjects.RdfDB()
        tparser = SWObjects.TrigSDriver("", F)
        tparser.setDB(parsedDB)
        tparser.parse(SWObjects.IStreamContext(
                "{ <s> <p1> <o1> . } <g> { <s> <p2> <o2> . }",
                SWObjects.StreamContextIstream.STRING))
        # print "parsedDB: ", parsedDB.toString()
        self.assertEqual(manualDB, parsedDB)

        different = SWObjects.RdfDB()
        tparser.setDB(different)
        tparser.parse(SWObjects.IStreamContext(
                "<g> { <s> <p1> <o1> . } { <s> <p2> <o2> . }",
                SWObjects.StreamContextIstream.STRING))
        # print "different: ", different.toString()
        self.assertNotEqual(parsedDB, different)


    def test_s_p1_o1_p2_o2 (self):
        # Test a query.
        F = SWObjects.AtomFactory()
        DB = SWObjects.RdfDB()
        tparser = SWObjects.TurtleSDriver("", F)
        tparser.setGraph(DB.ensureGraph(None))
        tparser.parse(SWObjects.IStreamContext(
                "<s> <p1> <o1> ; <p2> <o2> .",
                SWObjects.StreamContextIstream.STRING))
        # print "DB: ", DB.toString()
        sparser = SWObjects.SPARQLfedDriver("", F)
        sparser.parse(SWObjects.IStreamContext(
                "SELECT * { ?s <p1> ?o1 ; <p2> ?o2 }",
                SWObjects.StreamContextIstream.STRING))
        query = sparser.root
        # s = SWObjects.SPARQLSerializer()
        # query.express(s)
        # print "parsed: ", s.str()
        rs = SWObjects.ResultSet(F)
        query.execute(DB, rs)
        bnodereps = SWObjects.BNode2string()
        bnodeMap = SWObjects.String2BNode()
        reference = SWObjects.ResultSet(F, """
# Results for T1.
+------+------+-----+
| ?o1  | ?o2  | ?s  |
| <o1> | <o2> | <s> |
+------+------+-----+
""", False, bnodeMap);
        self.assertEqual(reference, rs)

        different = SWObjects.ResultSet(F, """
# Results for T1.
+------+------+------+
| ?o1  | ?o2  | ?s   |
| <o1> | <o2> | <s2> |
+------+------+------+
""", False, bnodeMap);
        self.assertNotEqual(different, rs)


    def test_remote (self):
        # Test a query.
        F = SWObjects.AtomFactory()

        agent = SWObjects.WEBagent_boostASIO()
        xmlParser = SWObjects.SAXparser_expat()
        DB = SWObjects.RdfDB(agent, xmlParser)
        sparser = SWObjects.SPARQLfedDriver("", F)
        sparser.parse(SWObjects.IStreamContext("""
PREFIX foaf: <http://xmlns.com/foaf/0.1/>
SELECT ?craft ?homepage
 WHERE {
  SERVICE <http://api.talis.com/stores/space/services/sparql> {
    ?craft foaf:name "Apollo 8" .
    ?craft foaf:homepage ?homepage
  }
}""", SWObjects.StreamContextIstream.STRING))
        query = sparser.root
        # s = SWObjects.SPARQLSerializer()
        # query.express(s)
        # print "parsed: ", s.str()
        rs = SWObjects.ResultSet(F)
        query.execute(DB, rs)
        bnodeMap = SWObjects.String2BNode()
        reference = SWObjects.ResultSet(F, """
# name and homepage of Apollo 8
+------------------------------------------------------+------------------------------------------------------------------+
| ?craft                                               | ?homepage                                                        |
| <http://nasa.dataincubator.org/spacecraft/1968-118A> | <http://nssdc.gsfc.nasa.gov/database/MasterCatalog?sc=1968-118A> |
+------------------------------------------------------+------------------------------------------------------------------+
""", False, bnodeMap);
        self.assertEqual(reference, rs)


    def test_update (self):
        # Test update .
        F = SWObjects.AtomFactory()

        updatedDB = SWObjects.RdfDB()
        sparser = SWObjects.SPARQLfedDriver("", F)
        sparser.parse(SWObjects.IStreamContext(
                "INSERT { <s> <p1> <o1> ; <p2> <o2> }",
                SWObjects.StreamContextIstream.STRING))
        query = sparser.root
        # s = SWObjects.SPARQLSerializer()
        # query.express(s)
        # print "parsed: ", s.str()
        rs = SWObjects.ResultSet(F)
        #rs.setRdfDB(updatedDB)
        query.execute(updatedDB, rs)

        referenceDB = SWObjects.RdfDB()
        tparser = SWObjects.TurtleSDriver("", F)
        tparser.setGraph(referenceDB.ensureGraph(None))
        tparser.parse(SWObjects.IStreamContext(
                "<s> <p1> <o1> ; <p2> <o2> .",
                SWObjects.StreamContextIstream.STRING))
        self.assertEqual(referenceDB, updatedDB)

    def test_construct (self):
        # Test update .
        F = SWObjects.AtomFactory()

        sourceDB = SWObjects.RdfDB()
        manDefault = sourceDB.ensureGraph(None)
        bnodeMap = SWObjects.String2BNode()
        F.parseNTriples(manDefault, "<s> <p1> <o1> .", bnodeMap);
        sparser = SWObjects.SPARQLfedDriver("", F)
        sparser.parse(SWObjects.IStreamContext(
                "CONSTRUCT { ?s ?p <o2> ; <p2> <o3> } WHERE { ?s ?p ?o }",
                SWObjects.StreamContextIstream.STRING))
        query = sparser.root
        # s = SWObjects.SPARQLSerializer()
        # query.express(s)
        # print "parsed: ", s.str()
        rs = SWObjects.ResultSet(F)

        # We're expecting a CONSTRUCT, so give the ResultSet a fresh database
        # for storing the constructed triples.
        self.assertEqual(query.getOperationType(), SWObjects.Operation.CONSTRUCT)
        constructDB = SWObjects.RdfDB()
        rs.setRdfDB(constructDB)

        query.execute(sourceDB, rs)

        # Expected results:
        expectedDB = SWObjects.RdfDB()
        F.parseNTriples(expectedDB.ensureGraph(None),
                        "<s> <p1> <o2> ."
                        "<s> <p2> <o3> .", bnodeMap);
        self.assertEqual(expectedDB, constructDB)


if __name__ == '__main__':
    unittest.main()

