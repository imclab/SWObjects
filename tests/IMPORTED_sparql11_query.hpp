BOOST_AUTO_TEST_CASE( agg01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg01";
    // name: COUNT 1
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg01.rq";
    const char* result = "data-sparql11/aggregates/agg01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg01 ) */
BOOST_AUTO_TEST_CASE( agg02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg02";
    // name: COUNT 2
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg02.rq";
    const char* result = "data-sparql11/aggregates/agg02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg02 ) */
BOOST_AUTO_TEST_CASE( agg03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg03";
    // name: COUNT 3
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg03.rq";
    const char* result = "data-sparql11/aggregates/agg03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg03 ) */
BOOST_AUTO_TEST_CASE( agg04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg04";
    // name: COUNT 4
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg04.rq";
    const char* result = "data-sparql11/aggregates/agg04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg04 ) */
BOOST_AUTO_TEST_CASE( agg05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg05";
    // name: COUNT 5
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg05.rq";
    const char* result = "data-sparql11/aggregates/agg05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg05 ) */
BOOST_AUTO_TEST_CASE( agg06 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg06";
    // name: COUNT 6
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg06.rq";
    const char* result = "data-sparql11/aggregates/agg06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg06 ) */
BOOST_AUTO_TEST_CASE( agg07 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg07";
    // name: COUNT 7
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg07.rq";
    const char* result = "data-sparql11/aggregates/agg07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg07 ) */
BOOST_AUTO_TEST_CASE( agg08b ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg08b";
    // name: COUNT 8b
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg08.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg08b.rq";
    const char* result = "data-sparql11/aggregates/agg08b.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg08b ) */
BOOST_AUTO_TEST_CASE( agg_groupconcat_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-groupconcat-01";
    // name: GROUP_CONCAT 1
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-groupconcat-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-groupconcat-1.rq";
    const char* result = "data-sparql11/aggregates/agg-groupconcat-1.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_groupconcat_01 ) */
BOOST_AUTO_TEST_CASE( agg_groupconcat_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-groupconcat-02";
    // name: GROUP_CONCAT 2
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-groupconcat-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-groupconcat-2.rq";
    const char* result = "data-sparql11/aggregates/agg-groupconcat-2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_groupconcat_02 ) */
BOOST_AUTO_TEST_CASE( agg_groupconcat_03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-groupconcat-03";
    // name: GROUP_CONCAT with SEPARATOR
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-groupconcat-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-groupconcat-3.rq";
    const char* result = "data-sparql11/aggregates/agg-groupconcat-3.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_groupconcat_03 ) */
BOOST_AUTO_TEST_CASE( agg_sum_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-sum-01";
    // name: SUM
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-sum-01.rq";
    const char* result = "data-sparql11/aggregates/agg-sum-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_sum_01 ) */
BOOST_AUTO_TEST_CASE( agg_sum_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-sum-02";
    // name: SUM with GROUP BY
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-sum-02.rq";
    const char* result = "data-sparql11/aggregates/agg-sum-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_sum_02 ) */
BOOST_AUTO_TEST_CASE( agg_avg_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-avg-01";
    // name: AVG
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-avg-01.rq";
    const char* result = "data-sparql11/aggregates/agg-avg-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_avg_01 ) */
BOOST_AUTO_TEST_CASE( agg_avg_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-avg-02";
    // name: AVG with GROUP BY
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-avg-02.rq";
    const char* result = "data-sparql11/aggregates/agg-avg-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_avg_02 ) */
BOOST_AUTO_TEST_CASE( agg_min_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-min-01";
    // name: MIN
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-min-01.rq";
    const char* result = "data-sparql11/aggregates/agg-min-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_min_01 ) */
BOOST_AUTO_TEST_CASE( agg_min_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-min-02";
    // name: MIN with GROUP BY
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-min-02.rq";
    const char* result = "data-sparql11/aggregates/agg-min-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_min_02 ) */
BOOST_AUTO_TEST_CASE( agg_max_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-max-01";
    // name: MAX
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-max-01.rq";
    const char* result = "data-sparql11/aggregates/agg-max-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_max_01 ) */
BOOST_AUTO_TEST_CASE( agg_max_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-max-02";
    // name: MAX with GROUP BY
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-max-02.rq";
    const char* result = "data-sparql11/aggregates/agg-max-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_max_02 ) */
BOOST_AUTO_TEST_CASE( agg_sample_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-sample-01";
    // name: SAMPLE
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-numeric.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-sample-01.rq";
    const char* result = "data-sparql11/aggregates/agg-sample-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_sample_01 ) */
BOOST_AUTO_TEST_CASE( agg_err_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-err-01";
    // name: Error in AVG
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-err-01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-err-01.rq";
    const char* result = "data-sparql11/aggregates/agg-err-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_err_01 ) */
BOOST_AUTO_TEST_CASE( agg_err_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-err-02";
    // name: Protect from error in AVG
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/agg-err-02.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-err-02.rq";
    const char* result = "data-sparql11/aggregates/agg-err-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_err_02 ) */
BOOST_AUTO_TEST_CASE( agg_empty_group2 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/aggregates/manifest#agg-empty-group2";
    // name: agg empty group
    // manifest: data-sparql11/aggregates/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/aggregates/empty.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/aggregates/agg-empty-group.rq";
    const char* result = "data-sparql11/aggregates/agg-empty-group2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( agg_empty_group2 ) */
BOOST_AUTO_TEST_CASE( bind01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind01";
    // name: bind01 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind01.rq";
    const char* result = "data-sparql11/bind/bind01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind01 ) */
BOOST_AUTO_TEST_CASE( bind02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind02";
    // name: bind02 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind02.rq";
    const char* result = "data-sparql11/bind/bind02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind02 ) */
BOOST_AUTO_TEST_CASE( bind03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind03";
    // name: bind03 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind03.rq";
    const char* result = "data-sparql11/bind/bind03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind03 ) */
BOOST_AUTO_TEST_CASE( bind04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind04";
    // name: bind04 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind04.rq";
    const char* result = "data-sparql11/bind/bind04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind04 ) */
BOOST_AUTO_TEST_CASE( bind05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind05";
    // name: bind05 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind05.rq";
    const char* result = "data-sparql11/bind/bind05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind05 ) */
BOOST_AUTO_TEST_CASE( bind06 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind06";
    // name: bind06 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind06.rq";
    const char* result = "data-sparql11/bind/bind06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind06 ) */
BOOST_AUTO_TEST_CASE( bind07 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind07";
    // name: bind07 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind07.rq";
    const char* result = "data-sparql11/bind/bind07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind07 ) */
BOOST_AUTO_TEST_CASE( bind08 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind08";
    // name: bind08 - BIND
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind08.rq";
    const char* result = "data-sparql11/bind/bind08.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind08 ) */
BOOST_AUTO_TEST_CASE( bind10 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind10";
    // name: bind10 - BIND scoping - Variable in filter not in scope
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind10.rq";
    const char* result = "data-sparql11/bind/bind10.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind10 ) */
BOOST_AUTO_TEST_CASE( bind11 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bind/manifest#bind11";
    // name: bind11 - BIND scoping - Variable in filter in scope
    // manifest: data-sparql11/bind/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bind/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bind/bind11.rq";
    const char* result = "data-sparql11/bind/bind11.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bind11 ) */
BOOST_AUTO_TEST_CASE( values1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values1";
    // name: Post-query VALUES with subj-var, 1 row
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values01.rq";
    const char* result = "data-sparql11/bindings/values01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values1 ) */
BOOST_AUTO_TEST_CASE( values2 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values2";
    // name: Post-query VALUES with obj-var, 1 row
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data02.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values02.rq";
    const char* result = "data-sparql11/bindings/values02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values2 ) */
BOOST_AUTO_TEST_CASE( values3 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values3";
    // name: Post-query VALUES with 2 obj-vars, 1 row
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data03.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values03.rq";
    const char* result = "data-sparql11/bindings/values03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values3 ) */
BOOST_AUTO_TEST_CASE( values4 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values4";
    // name: Post-query VALUES with 2 obj-vars, 1 row with UNDEF
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data04.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values04.rq";
    const char* result = "data-sparql11/bindings/values04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values4 ) */
BOOST_AUTO_TEST_CASE( values5 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values5";
    // name: Post-query VALUES with 2 obj-vars, 2 rows with UNDEF
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data05.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values05.rq";
    const char* result = "data-sparql11/bindings/values05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values5 ) */
BOOST_AUTO_TEST_CASE( values6 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values6";
    // name: Post-query VALUES with pred-var, 1 row
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data06.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values06.rq";
    const char* result = "data-sparql11/bindings/values06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values6 ) */
BOOST_AUTO_TEST_CASE( values7 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values7";
    // name: Post-query VALUES with (OPTIONAL) obj-var, 1 row
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data07.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values07.rq";
    const char* result = "data-sparql11/bindings/values07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values7 ) */
BOOST_AUTO_TEST_CASE( values8 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#values8";
    // name: Post-query VALUES with subj/obj-vars, 2 rows with UNDEF
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data08.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/values08.rq";
    const char* result = "data-sparql11/bindings/values08.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( values8 ) */
BOOST_AUTO_TEST_CASE( inline1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#inline1";
    // name: Inline VALUES graph pattern
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/inline01.rq";
    const char* result = "data-sparql11/bindings/inline01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( inline1 ) */
BOOST_AUTO_TEST_CASE( inline2 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/bindings/manifest#inline2";
    // name: Post-subquery VALUES
    // manifest: data-sparql11/bindings/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/bindings/data02.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/bindings/inline02.rq";
    const char* result = "data-sparql11/bindings/inline02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( inline2 ) */
BOOST_AUTO_TEST_CASE( constructwhere01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/construct/manifest#constructwhere01";
    // name: constructwhere01 - CONSTRUCT WHERE
    // manifest: data-sparql11/construct/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/construct/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/construct/constructwhere01.rq";
    const char* result = "data-sparql11/construct/constructwhere01result.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( constructwhere01 ) */
BOOST_AUTO_TEST_CASE( constructwhere02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/construct/manifest#constructwhere02";
    // name: constructwhere02 - CONSTRUCT WHERE
    // manifest: data-sparql11/construct/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/construct/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/construct/constructwhere02.rq";
    const char* result = "data-sparql11/construct/constructwhere02result.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( constructwhere02 ) */
BOOST_AUTO_TEST_CASE( constructwhere03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/construct/manifest#constructwhere03";
    // name: constructwhere03 - CONSTRUCT WHERE
    // manifest: data-sparql11/construct/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/construct/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/construct/constructwhere03.rq";
    const char* result = "data-sparql11/construct/constructwhere03result.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( constructwhere03 ) */
BOOST_AUTO_TEST_CASE( constructwhere04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/construct/manifest#constructwhere04";
    // name: constructwhere04 - CONSTRUCT WHERE
    // manifest: data-sparql11/construct/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/construct/constructwhere04.rq";
    const char* result = "data-sparql11/construct/constructwhere04result.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( constructwhere04 ) */
BOOST_AUTO_TEST_CASE( exists01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/exists/manifest#exists01";
    // name: Exists with one constant
    // manifest: data-sparql11/exists/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/exists/exists01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/exists/exists01.rq";
    const char* result = "data-sparql11/exists/exists01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists01 ) */
BOOST_AUTO_TEST_CASE( exists02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/exists/manifest#exists02";
    // name: Exists with ground triple
    // manifest: data-sparql11/exists/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/exists/exists01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/exists/exists02.rq";
    const char* result = "data-sparql11/exists/exists02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists02 ) */
BOOST_AUTO_TEST_CASE( exists03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/exists/manifest#exists03";
    // name: Exists within graph pattern
    // manifest: data-sparql11/exists/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/exists/exists01.ttl";
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/exists/exists02.ttl", "data-sparql11/exists/exists02.ttl")};
    const char* request = "data-sparql11/exists/exists03.rq";
    const char* result = "data-sparql11/exists/exists03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists03 ) */
BOOST_AUTO_TEST_CASE( exists04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/exists/manifest#exists04";
    // name: Nested positive exists
    // manifest: data-sparql11/exists/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/exists/exists01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/exists/exists04.rq";
    const char* result = "data-sparql11/exists/exists04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists04 ) */
BOOST_AUTO_TEST_CASE( exists05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/exists/manifest#exists05";
    // name: Nested negative exists in positive exists
    // manifest: data-sparql11/exists/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/exists/exists01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/exists/exists05.rq";
    const char* result = "data-sparql11/exists/exists05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists05 ) */
BOOST_AUTO_TEST_CASE( strdt01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strdt01";
    // name: STRDT()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strdt01.rq";
    const char* result = "data-sparql11/functions/strdt01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strdt01 ) */
BOOST_AUTO_TEST_CASE( strdt02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strdt02";
    // name: STRDT(STR())
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strdt02.rq";
    const char* result = "data-sparql11/functions/strdt02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strdt02 ) */
BOOST_AUTO_TEST_CASE( strdt03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strdt03";
    // name: STRDT() TypeErrors
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strdt03.rq";
    const char* result = "data-sparql11/functions/strdt03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strdt03 ) */
BOOST_AUTO_TEST_CASE( strlang01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strlang01";
    // name: STRLANG()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strlang01.rq";
    const char* result = "data-sparql11/functions/strlang01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strlang01 ) */
BOOST_AUTO_TEST_CASE( strlang02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strlang02";
    // name: STRLANG(STR())
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strlang02.rq";
    const char* result = "data-sparql11/functions/strlang02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strlang02 ) */
BOOST_AUTO_TEST_CASE( strlang03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strlang03";
    // name: STRLANG() TypeErrors
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strlang03.rq";
    const char* result = "data-sparql11/functions/strlang03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strlang03 ) */
BOOST_AUTO_TEST_CASE( isnumeric01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#isnumeric01";
    // name: isNumeric()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/isnumeric01.rq";
    const char* result = "data-sparql11/functions/isnumeric01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( isnumeric01 ) */
BOOST_AUTO_TEST_CASE( abs01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#abs01";
    // name: ABS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/abs01.rq";
    const char* result = "data-sparql11/functions/abs01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( abs01 ) */
BOOST_AUTO_TEST_CASE( ceil01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#ceil01";
    // name: CEIL()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/ceil01.rq";
    const char* result = "data-sparql11/functions/ceil01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( ceil01 ) */
BOOST_AUTO_TEST_CASE( floor01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#floor01";
    // name: FLOOR()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/floor01.rq";
    const char* result = "data-sparql11/functions/floor01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( floor01 ) */
BOOST_AUTO_TEST_CASE( round01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#round01";
    // name: ROUND()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/round01.rq";
    const char* result = "data-sparql11/functions/round01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( round01 ) */
BOOST_AUTO_TEST_CASE( concat01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#concat01";
    // name: CONCAT()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/concat01.rq";
    const char* result = "data-sparql11/functions/concat01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( concat01 ) */
BOOST_AUTO_TEST_CASE( concat02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#concat02";
    // name: CONCAT() 2
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/concat02.rq";
    const char* result = "data-sparql11/functions/concat02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( concat02 ) */
BOOST_AUTO_TEST_CASE( substring01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#substring01";
    // name: SUBSTR() (3-argument)
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/substring01.rq";
    const char* result = "data-sparql11/functions/substring01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( substring01 ) */
BOOST_AUTO_TEST_CASE( substring02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#substring02";
    // name: SUBSTR() (2-argument)
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/substring02.rq";
    const char* result = "data-sparql11/functions/substring02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( substring02 ) */
BOOST_AUTO_TEST_CASE( length01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#length01";
    // name: STRLEN()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/length01.rq";
    const char* result = "data-sparql11/functions/length01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( length01 ) */
BOOST_AUTO_TEST_CASE( ucase01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#ucase01";
    // name: UCASE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/ucase01.rq";
    const char* result = "data-sparql11/functions/ucase01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( ucase01 ) */
BOOST_AUTO_TEST_CASE( lcase01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#lcase01";
    // name: LCASE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/lcase01.rq";
    const char* result = "data-sparql11/functions/lcase01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( lcase01 ) */
BOOST_AUTO_TEST_CASE( encode01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#encode01";
    // name: ENCODE_FOR_URI()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/encode01.rq";
    const char* result = "data-sparql11/functions/encode01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( encode01 ) */
BOOST_AUTO_TEST_CASE( contains01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#contains01";
    // name: CONTAINS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/contains01.rq";
    const char* result = "data-sparql11/functions/contains01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( contains01 ) */
BOOST_AUTO_TEST_CASE( starts01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#starts01";
    // name: STRSTARTS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/starts01.rq";
    const char* result = "data-sparql11/functions/starts01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( starts01 ) */
BOOST_AUTO_TEST_CASE( ends01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#ends01";
    // name: STRENDS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/ends01.rq";
    const char* result = "data-sparql11/functions/ends01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( ends01 ) */
BOOST_AUTO_TEST_CASE( plus_1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#plus-1";
    // name: plus-1
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data-builtin-3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/plus-1.rq";
    const char* result = "data-sparql11/functions/plus-1.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( plus_1 ) */
BOOST_AUTO_TEST_CASE( plus_2 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#plus-2";
    // name: plus-2
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data-builtin-3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/plus-2.rq";
    const char* result = "data-sparql11/functions/plus-2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( plus_2 ) */
BOOST_AUTO_TEST_CASE( md5_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#md5-01";
    // name: MD5()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/md5-01.rq";
    const char* result = "data-sparql11/functions/md5-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( md5_01 ) */
BOOST_AUTO_TEST_CASE( md5_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#md5-02";
    // name: MD5() over Unicode data
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/md5-02.rq";
    const char* result = "data-sparql11/functions/md5-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( md5_02 ) */
BOOST_AUTO_TEST_CASE( sha1_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha1-01";
    // name: SHA1()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha1-01.rq";
    const char* result = "data-sparql11/functions/sha1-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha1_01 ) */
BOOST_AUTO_TEST_CASE( sha1_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha1-02";
    // name: SHA1() on Unicode data
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/hash-unicode.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha1-02.rq";
    const char* result = "data-sparql11/functions/sha1-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha1_02 ) */
BOOST_AUTO_TEST_CASE( sha256_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha256-01";
    // name: SHA256()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha256-01.rq";
    const char* result = "data-sparql11/functions/sha256-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha256_01 ) */
BOOST_AUTO_TEST_CASE( sha256_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha256-02";
    // name: SHA256() on Unicode data
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/hash-unicode.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha256-02.rq";
    const char* result = "data-sparql11/functions/sha256-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha256_02 ) */
BOOST_AUTO_TEST_CASE( sha512_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha512-01";
    // name: SHA512()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha512-01.rq";
    const char* result = "data-sparql11/functions/sha512-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha512_01 ) */
BOOST_AUTO_TEST_CASE( sha512_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#sha512-02";
    // name: SHA512() on Unicode data
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/hash-unicode.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/sha512-02.rq";
    const char* result = "data-sparql11/functions/sha512-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( sha512_02 ) */
BOOST_AUTO_TEST_CASE( minutes ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#minutes";
    // name: MINUTES()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/minutes-01.rq";
    const char* result = "data-sparql11/functions/minutes-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( minutes ) */
BOOST_AUTO_TEST_CASE( seconds ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#seconds";
    // name: SECONDS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/seconds-01.rq";
    const char* result = "data-sparql11/functions/seconds-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( seconds ) */
BOOST_AUTO_TEST_CASE( hours ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#hours";
    // name: HOURS()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/hours-01.rq";
    const char* result = "data-sparql11/functions/hours-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( hours ) */
BOOST_AUTO_TEST_CASE( month ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#month";
    // name: MONTH()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/month-01.rq";
    const char* result = "data-sparql11/functions/month-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( month ) */
BOOST_AUTO_TEST_CASE( year ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#year";
    // name: YEAR()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/year-01.rq";
    const char* result = "data-sparql11/functions/year-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( year ) */
BOOST_AUTO_TEST_CASE( day ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#day";
    // name: DAY()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/day-01.rq";
    const char* result = "data-sparql11/functions/day-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( day ) */
BOOST_AUTO_TEST_CASE( timezone ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#timezone";
    // name: TIMEZONE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/timezone-01.rq";
    const char* result = "data-sparql11/functions/timezone-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( timezone ) */
BOOST_AUTO_TEST_CASE( tz ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#tz";
    // name: TZ()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/tz-01.rq";
    const char* result = "data-sparql11/functions/tz-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( tz ) */
BOOST_AUTO_TEST_CASE( bnode01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#bnode01";
    // name: BNODE(str)
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/bnode01.rq";
    const char* result = "data-sparql11/functions/bnode01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bnode01 ) */
BOOST_AUTO_TEST_CASE( bnode02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#bnode02";
    // name: BNODE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/bnode02.rq";
    const char* result = "data-sparql11/functions/bnode02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( bnode02 ) */
BOOST_AUTO_TEST_CASE( in01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#in01";
    // name: IN 1
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/in01.rq";
    const char* result = "data-sparql11/functions/in01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( in01 ) */
BOOST_AUTO_TEST_CASE( in02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#in02";
    // name: IN 2
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/in02.rq";
    const char* result = "data-sparql11/functions/in02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( in02 ) */
BOOST_AUTO_TEST_CASE( notin01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#notin01";
    // name: NOT IN 1
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/notin01.rq";
    const char* result = "data-sparql11/functions/notin01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( notin01 ) */
BOOST_AUTO_TEST_CASE( notin02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#notin02";
    // name: NOT IN 2
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/notin02.rq";
    const char* result = "data-sparql11/functions/notin02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( notin02 ) */
BOOST_AUTO_TEST_CASE( now01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#now01";
    // name: NOW()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/now01.rq";
    const char* result = "data-sparql11/functions/now01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( now01 ) */
BOOST_AUTO_TEST_CASE( rand01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#rand01";
    // name: RAND()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/rand01.rq";
    const char* result = "data-sparql11/functions/rand01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( rand01 ) */
BOOST_AUTO_TEST_CASE( iri01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#iri01";
    // name: IRI()/URI()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/iri01.rq";
    const char* result = "data-sparql11/functions/iri01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( iri01 ) */
BOOST_AUTO_TEST_CASE( if01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#if01";
    // name: IF()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/if01.rq";
    const char* result = "data-sparql11/functions/if01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( if01 ) */
BOOST_AUTO_TEST_CASE( if02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#if02";
    // name: IF() error propogation
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/if02.rq";
    const char* result = "data-sparql11/functions/if02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( if02 ) */
BOOST_AUTO_TEST_CASE( coalesce01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#coalesce01";
    // name: COALESCE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data-coalesce.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/coalesce01.rq";
    const char* result = "data-sparql11/functions/coalesce01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( coalesce01 ) */
BOOST_AUTO_TEST_CASE( strbefore01a ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strbefore01a";
    // name: STRBEFORE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strbefore01.rq";
    const char* result = "data-sparql11/functions/strbefore01a.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strbefore01a ) */
BOOST_AUTO_TEST_CASE( strbefore02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strbefore02";
    // name: STRBEFORE() datatyping
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data4.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strbefore02.rq";
    const char* result = "data-sparql11/functions/strbefore02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strbefore02 ) */
BOOST_AUTO_TEST_CASE( strafter01a ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strafter01a";
    // name: STRAFTER()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strafter01.rq";
    const char* result = "data-sparql11/functions/strafter01a.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strafter01a ) */
BOOST_AUTO_TEST_CASE( strafter02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#strafter02";
    // name: STRAFTER() datatyping
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data4.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/strafter02.rq";
    const char* result = "data-sparql11/functions/strafter02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( strafter02 ) */
BOOST_AUTO_TEST_CASE( replace01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#replace01";
    // name: REPLACE()
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/replace01.rq";
    const char* result = "data-sparql11/functions/replace01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( replace01 ) */
BOOST_AUTO_TEST_CASE( replace02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#replace02";
    // name: REPLACE() with overlapping pattern
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/replace02.rq";
    const char* result = "data-sparql11/functions/replace02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( replace02 ) */
BOOST_AUTO_TEST_CASE( replace03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#replace03";
    // name: REPLACE() with captured substring
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/replace03.rq";
    const char* result = "data-sparql11/functions/replace03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( replace03 ) */
BOOST_AUTO_TEST_CASE( uuid01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#uuid01";
    // name: UUID() pattern match
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data-empty.nt";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/uuid01.rq";
    const char* result = "data-sparql11/functions/uuid01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( uuid01 ) */
BOOST_AUTO_TEST_CASE( struuid01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/functions/manifest#struuid01";
    // name: STRUUID() pattern match
    // manifest: data-sparql11/functions/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/functions/data-empty.nt";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/functions/struuid01.rq";
    const char* result = "data-sparql11/functions/struuid01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( struuid01 ) */
BOOST_AUTO_TEST_CASE( group01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/grouping/manifest#group01";
    // name: Group-1
    // manifest: data-sparql11/grouping/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/grouping/group-data-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/grouping/group01.rq";
    const char* result = "data-sparql11/grouping/group01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( group01 ) */
BOOST_AUTO_TEST_CASE( group03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/grouping/manifest#group03";
    // name: Group-3
    // manifest: data-sparql11/grouping/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/grouping/group-data-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/grouping/group03.rq";
    const char* result = "data-sparql11/grouping/group03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( group03 ) */
BOOST_AUTO_TEST_CASE( group04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/grouping/manifest#group04";
    // name: Group-4
    // manifest: data-sparql11/grouping/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/grouping/group-data-1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/grouping/group04.rq";
    const char* result = "data-sparql11/grouping/group04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( group04 ) */
BOOST_AUTO_TEST_CASE( group05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/grouping/manifest#group05";
    // name: Group-5
    // manifest: data-sparql11/grouping/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/grouping/group-data-2.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/grouping/group05.rq";
    const char* result = "data-sparql11/grouping/group05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( group05 ) */
BOOST_AUTO_TEST_CASE( subset_by_exclusion_nex_1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#subset-by-exclusion-nex-1";
    // name: Subsets by exclusion (NOT EXISTS)
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/subsetByExcl.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/subsetByExcl01.rq";
    const char* result = "data-sparql11/negation/subsetByExcl01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subset_by_exclusion_nex_1 ) */
BOOST_AUTO_TEST_CASE( subset_by_exclusion_minus_1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#subset-by-exclusion-minus-1";
    // name: Subsets by exclusion (MINUS)
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/subsetByExcl.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/subsetByExcl02.rq";
    const char* result = "data-sparql11/negation/subsetByExcl02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subset_by_exclusion_minus_1 ) */
BOOST_AUTO_TEST_CASE( temporal_proximity_by_exclusion_nex_1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#temporal-proximity-by-exclusion-nex-1";
    // name: Medical, temporal proximity by exclusion (NOT EXISTS)
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/temporalProximity01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/temporalProximity01.rq";
    const char* result = "data-sparql11/negation/temporalProximity01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( temporal_proximity_by_exclusion_nex_1 ) */
BOOST_AUTO_TEST_CASE( subset_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#subset-01";
    // name: Calculate which sets are subsets of others (include A subsetOf A)
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/subset-01.rq";
    const char* result = "data-sparql11/negation/subset-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subset_01 ) */
BOOST_AUTO_TEST_CASE( subset_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#subset-02";
    // name: Calculate which sets are subsets of others (exclude A subsetOf A)
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/subset-02.rq";
    const char* result = "data-sparql11/negation/subset-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subset_02 ) */
BOOST_AUTO_TEST_CASE( set_equals_1 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#set-equals-1";
    // name: Calculate which sets have the same elements
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/set-equals-1.rq";
    const char* result = "data-sparql11/negation/set-equals-1.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( set_equals_1 ) */
BOOST_AUTO_TEST_CASE( subset_03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#subset-03";
    // name: Calculate proper subset
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/subset-03.rq";
    const char* result = "data-sparql11/negation/subset-03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subset_03 ) */
BOOST_AUTO_TEST_CASE( exists_01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#exists-01";
    // name: Positive EXISTS 1
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/exists-01.rq";
    const char* result = "data-sparql11/negation/exists-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists_01 ) */
BOOST_AUTO_TEST_CASE( exists_02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#exists-02";
    // name: Positive EXISTS 2
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/set-data.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/exists-02.rq";
    const char* result = "data-sparql11/negation/exists-02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( exists_02 ) */
BOOST_AUTO_TEST_CASE( full_minuend ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#full-minuend";
    // name: Subtraction with MINUS from a fully bound minuend
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/full-minuend.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/full-minuend.rq";
    const char* result = "data-sparql11/negation/full-minuend.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( full_minuend ) */
BOOST_AUTO_TEST_CASE( partial_minuend ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/negation/manifest#partial-minuend";
    // name: Subtraction with MINUS from a partially bound minuend
    // manifest: data-sparql11/negation/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/negation/part-minuend.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/negation/part-minuend.rq";
    const char* result = "data-sparql11/negation/part-minuend.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( partial_minuend ) */
BOOST_AUTO_TEST_CASE( projexp01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp01";
    // name: Expression is equality
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp01.rq";
    const char* result = "data-sparql11/project-expression/projexp01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp01 ) */
BOOST_AUTO_TEST_CASE( projexp02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp02";
    // name: Expression raise an error
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp02.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp02.rq";
    const char* result = "data-sparql11/project-expression/projexp02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp02 ) */
BOOST_AUTO_TEST_CASE( projexp03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp03";
    // name: Reuse a project expression variable in select
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp03.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp03.rq";
    const char* result = "data-sparql11/project-expression/projexp03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp03 ) */
BOOST_AUTO_TEST_CASE( projexp04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp04";
    // name: Reuse a project expression variable in order by
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp04.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp04.rq";
    const char* result = "data-sparql11/project-expression/projexp04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp04 ) */
BOOST_AUTO_TEST_CASE( projexp05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp05";
    // name: Expression may return no value
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp05.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp05.rq";
    const char* result = "data-sparql11/project-expression/projexp05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp05 ) */
BOOST_AUTO_TEST_CASE( projexp06 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp06";
    // name: Expression has undefined variable
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp06.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp06.rq";
    const char* result = "data-sparql11/project-expression/projexp06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp06 ) */
BOOST_AUTO_TEST_CASE( projexp07 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/project-expression/manifest#projexp07";
    // name: Expression has variable that may be unbound
    // manifest: data-sparql11/project-expression/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/project-expression/projexp07.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/project-expression/projexp07.rq";
    const char* result = "data-sparql11/project-expression/projexp07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( projexp07 ) */
BOOST_AUTO_TEST_CASE( pp01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp01";
    // name: (pp01) Simple path
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp01.rq";
    const char* result = "data-sparql11/property-path/pp01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp01 ) */
BOOST_AUTO_TEST_CASE( pp02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp02";
    // name: (pp02) Star path
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp01.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp02.rq";
    const char* result = "data-sparql11/property-path/pp02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp02 ) */
BOOST_AUTO_TEST_CASE( pp03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp03";
    // name: (pp03) Simple path with loop
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp03.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp03.rq";
    const char* result = "data-sparql11/property-path/pp03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp03 ) */
BOOST_AUTO_TEST_CASE( pp06 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp06";
    // name: (pp06) Path with two graphs
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/property-path/pp061.ttl", "data-sparql11/property-path/pp061.ttl"), LG("data-sparql11/property-path/pp062.ttl", "data-sparql11/property-path/pp062.ttl")};
    const char* request = "data-sparql11/property-path/pp06.rq";
    const char* result = "data-sparql11/property-path/pp06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp06 ) */
BOOST_AUTO_TEST_CASE( pp07 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp07";
    // name: (pp07) Path with one graph
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/property-path/pp07.ttl", "data-sparql11/property-path/pp07.ttl")};
    const char* request = "data-sparql11/property-path/pp06.rq";
    const char* result = "data-sparql11/property-path/pp07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp07 ) */
BOOST_AUTO_TEST_CASE( pp08 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp08";
    // name: (pp08) Reverse path
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp08.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp08.rq";
    const char* result = "data-sparql11/property-path/pp08.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp08 ) */
BOOST_AUTO_TEST_CASE( pp09 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp09";
    // name: (pp09) Reverse sequence path
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp09.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp09.rq";
    const char* result = "data-sparql11/property-path/pp09.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp09 ) */
BOOST_AUTO_TEST_CASE( pp10 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp10";
    // name: (pp10) Path with negation
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp10.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp10.rq";
    const char* result = "data-sparql11/property-path/pp10.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp10 ) */
BOOST_AUTO_TEST_CASE( pp11 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp11";
    // name: (pp11) Simple path and two paths to same target node
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp11.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp11.rq";
    const char* result = "data-sparql11/property-path/pp11.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp11 ) */
BOOST_AUTO_TEST_CASE( pp12 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp12";
    // name: (pp12) Variable length path and two paths to same target node
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp11.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp12.rq";
    const char* result = "data-sparql11/property-path/pp12.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp12 ) */
BOOST_AUTO_TEST_CASE( pp14 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp14";
    // name: (pp14) Star path over foaf:knows
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp14.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp14.rq";
    const char* result = "data-sparql11/property-path/pp14.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp14 ) */
BOOST_AUTO_TEST_CASE( pp16 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp16";
    // name: (pp16) Duplicate paths and cycles through foaf:knows*
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp16.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp14.rq";
    const char* result = "data-sparql11/property-path/pp16.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp16 ) */
BOOST_AUTO_TEST_CASE( pp21 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp21";
    // name: (pp21) Diamond -- :p+
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/data-diamond.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-2-2.rq";
    const char* result = "data-sparql11/property-path/diamond-2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp21 ) */
BOOST_AUTO_TEST_CASE( pp23 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp23";
    // name: (pp23) Diamond, with tail -- :p+
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/data-diamond-tail.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-2-2.rq";
    const char* result = "data-sparql11/property-path/diamond-tail-2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp23 ) */
BOOST_AUTO_TEST_CASE( pp25 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp25";
    // name: (pp25) Diamond, with loop -- :p+
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/data-diamond-loop.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-2-2.rq";
    const char* result = "data-sparql11/property-path/diamond-loop-2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp25 ) */
BOOST_AUTO_TEST_CASE( pp28a ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp28a";
    // name: (pp28a) Diamond, with loop -- (:p/:p)?
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/data-diamond-loop.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-3-3.rq";
    const char* result = "data-sparql11/property-path/diamond-loop-5a.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp28a ) */
BOOST_AUTO_TEST_CASE( pp30 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp30";
    // name: (pp30) Operator precedence 1
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/path-p1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-p1.rq";
    const char* result = "data-sparql11/property-path/path-p1.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp30 ) */
BOOST_AUTO_TEST_CASE( pp31 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp31";
    // name: (pp31) Operator precedence 2
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/path-p1.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-p2.rq";
    const char* result = "data-sparql11/property-path/path-p2.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp31 ) */
BOOST_AUTO_TEST_CASE( pp32 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp32";
    // name: (pp32) Operator precedence 3
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/path-p3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-p3.rq";
    const char* result = "data-sparql11/property-path/path-p3.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp32 ) */
BOOST_AUTO_TEST_CASE( pp33 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp33";
    // name: (pp33) Operator precedence 4
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/path-p3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/path-p4.rq";
    const char* result = "data-sparql11/property-path/path-p4.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp33 ) */
BOOST_AUTO_TEST_CASE( pp34 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp34";
    // name: (pp34) Named Graph 1
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/property-path/ng-01.ttl", "data-sparql11/property-path/ng-01.ttl"), LG("data-sparql11/property-path/ng-02.ttl", "data-sparql11/property-path/ng-02.ttl"), LG("data-sparql11/property-path/ng-03.ttl", "data-sparql11/property-path/ng-03.ttl")};
    const char* request = "data-sparql11/property-path/path-ng-01.rq";
    const char* result = "data-sparql11/property-path/path-ng-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp34 ) */
BOOST_AUTO_TEST_CASE( pp35 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp35";
    // name: (pp35) Named Graph 2
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/property-path/ng-01.ttl", "data-sparql11/property-path/ng-01.ttl"), LG("data-sparql11/property-path/ng-02.ttl", "data-sparql11/property-path/ng-02.ttl"), LG("data-sparql11/property-path/ng-03.ttl", "data-sparql11/property-path/ng-03.ttl")};
    const char* request = "data-sparql11/property-path/path-ng-02.rq";
    const char* result = "data-sparql11/property-path/path-ng-01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp35 ) */
BOOST_AUTO_TEST_CASE( pp36 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp36";
    // name: (pp36) Arbitrary path with bound endpoints
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/clique3.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp36.rq";
    const char* result = "data-sparql11/property-path/pp36.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp36 ) */
BOOST_AUTO_TEST_CASE( pp37 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/property-path/manifest#pp37";
    // name: (pp37) Nested (*)*
    // manifest: data-sparql11/property-path/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/property-path/pp37.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/property-path/pp37.rq";
    const char* result = "data-sparql11/property-path/pp37.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( pp37 ) */
BOOST_AUTO_TEST_CASE( subquery01 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery01";
    // name: sq01 - Subquery within graph pattern
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq01.rdf", "data-sparql11/subquery/sq01.rdf")};
    const char* request = "data-sparql11/subquery/sq01.rq";
    const char* result = "data-sparql11/subquery/sq01.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery01 ) */
BOOST_AUTO_TEST_CASE( subquery02 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery02";
    // name: sq02 - Subquery within graph pattern, graph variable is bound
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq01.rdf", "data-sparql11/subquery/sq01.rdf")};
    const char* request = "data-sparql11/subquery/sq02.rq";
    const char* result = "data-sparql11/subquery/sq02.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery02 ) */
BOOST_AUTO_TEST_CASE( subquery03 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery03";
    // name: sq03 - Subquery within graph pattern, graph variable is not bound
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq01.rdf", "data-sparql11/subquery/sq01.rdf")};
    const char* request = "data-sparql11/subquery/sq03.rq";
    const char* result = "data-sparql11/subquery/sq03.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery03 ) */
BOOST_AUTO_TEST_CASE( subquery04 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery04";
    // name: sq04 - Subquery within graph pattern, default graph does not apply
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq04.rdf";
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq01.rdf", "data-sparql11/subquery/sq01.rdf")};
    const char* request = "data-sparql11/subquery/sq04.rq";
    const char* result = "data-sparql11/subquery/sq04.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery04 ) */
BOOST_AUTO_TEST_CASE( subquery05 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery05";
    // name: sq05 - Subquery within graph pattern, from named applies
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq05.rdf", "data-sparql11/subquery/sq05.rdf")};
    const char* request = "data-sparql11/subquery/sq05.rq";
    const char* result = "data-sparql11/subquery/sq05.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery05 ) */
BOOST_AUTO_TEST_CASE( subquery06 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery06";
    // name: sq06 - Subquery with graph pattern, from named applies
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq05.rdf";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq06.rq";
    const char* result = "data-sparql11/subquery/sq06.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery06 ) */
BOOST_AUTO_TEST_CASE( subquery07 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery07";
    // name: sq07 - Subquery with from 
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = NULL;
    LabeledGraph namedGraphs_in[] = {LG("data-sparql11/subquery/sq05.rdf", "data-sparql11/subquery/sq05.rdf")};
    const char* request = "data-sparql11/subquery/sq07.rq";
    const char* result = "data-sparql11/subquery/sq07.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery07 ) */
BOOST_AUTO_TEST_CASE( subquery08 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery08";
    // name: sq08 - Subquery with aggregate
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq08.rdf";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq08.rq";
    const char* result = "data-sparql11/subquery/sq08.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery08 ) */
BOOST_AUTO_TEST_CASE( subquery09 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery09";
    // name: sq09 - Nested Subqueries
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq09.rdf";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq09.rq";
    const char* result = "data-sparql11/subquery/sq09.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery09 ) */
BOOST_AUTO_TEST_CASE( subquery10 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery10";
    // name: sq10 - Subquery with exists
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq10.rdf";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq10.rq";
    const char* result = "data-sparql11/subquery/sq10.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery10 ) */
BOOST_AUTO_TEST_CASE( subquery11 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery11";
    // name: sq11 - Subquery limit per resource
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq11.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq11.rq";
    const char* result = "data-sparql11/subquery/sq11.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery11 ) */
BOOST_AUTO_TEST_CASE( subquery12 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery12";
    // name: sq12 - Subquery in CONSTRUCT with built-ins
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq12.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq12.rq";
    const char* result = "data-sparql11/subquery/sq12_out.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery12 ) */
BOOST_AUTO_TEST_CASE( subquery13 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery13";
    // name: sq13 - Subqueries don't inject bindings
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq11.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq11.rq";
    const char* result = "data-sparql11/subquery/sq11.srx";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery13 ) */
BOOST_AUTO_TEST_CASE( subquery14 ) {
    const char* test = "http://www.w3.org/2009/sparql/docs/tests/data-sparql11/subquery/manifest#subquery14";
    // name: sq14 - limit by resource
    // manifest: data-sparql11/subquery/manifest.ttl
    const char* defaultGraph_in = "data-sparql11/subquery/sq14.ttl";
    LabeledGraph namedGraphs_in[] = {};
    const char* request = "data-sparql11/subquery/sq14.rq";
    const char* result = "data-sparql11/subquery/sq14-out.ttl";
    QUERY_TEST();
} /* BOOST_AUTO_TEST_CASE( subquery14 ) */
