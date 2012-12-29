BOOST_AUTO_TEST_CASE( csv01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/csv-tsv-res/manifest#csv01";
    // name: csv01 - CSV Result Format
    // manifest: data-sparql11/csv-tsv-res/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/csv-tsv-res/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/csv-tsv-res/csvtsv01.rq";
    const char* result = "data-sparql11/csv-tsv-res/csvtsv01.csv";
    CSV_QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( csv01 ) */
BOOST_AUTO_TEST_CASE( csv02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/csv-tsv-res/manifest#csv02";
    // name: cvs02 - CSV Result Format
    // manifest: data-sparql11/csv-tsv-res/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/csv-tsv-res/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/csv-tsv-res/csvtsv02.rq";
    const char* result = "data-sparql11/csv-tsv-res/csvtsv02.csv";
    CSV_QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( csv02 ) */
BOOST_AUTO_TEST_CASE( csv03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/csv-tsv-res/manifest#csv03";
    // name: csv03 - CSV Result Format
    // manifest: data-sparql11/csv-tsv-res/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/csv-tsv-res/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/csv-tsv-res/csvtsv01.rq";
    const char* result = "data-sparql11/csv-tsv-res/csvtsv03.csv";
    CSV_QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( csv03 ) */