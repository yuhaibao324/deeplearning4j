//
// @author raver119@gmail.com
//


#include "testlayers.h"
#include <GraphExecutioner.h>

using namespace nd4j::graph;

class ProtoBufTests : public testing::Test {

};

TEST_F(ProtoBufTests, TestBinaryLoad1) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto graph = GraphExecutioner<float>::importFromTensorFlow("../../../tests/resources/tensorflow_inception_graph.pb");

    ASSERT_FALSE(graph == nullptr);
}

TEST_F(ProtoBufTests, TestTextLoad1) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto graph = GraphExecutioner<float>::importFromTensorFlow("../../../tests/resources/max_graph.pb.txt");

    ASSERT_FALSE(graph == nullptr);
}


TEST_F(ProtoBufTests, TestTextLoad2) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto graph = GraphExecutioner<float>::importFromTensorFlow("../../../tests/resources/max_add_2.pb.txt");

    ASSERT_FALSE(graph == nullptr);

    ASSERT_EQ(2, graph->getVariableSpace()->externalEntries());

    auto var0 = graph->getVariableSpace()->getVariable(new std::string("zeros"));
    auto var1 = graph->getVariableSpace()->getVariable(new std::string("ones"));


    // first we're veryfying variable states
    ASSERT_TRUE(var0 != nullptr);
    ASSERT_TRUE(var1 != nullptr);

    ASSERT_TRUE(var0->getNDArray() != nullptr);
    ASSERT_TRUE(var1->getNDArray() != nullptr);

    ASSERT_EQ(12, var0->getNDArray()->lengthOf());
    ASSERT_EQ(12, var1->getNDArray()->lengthOf());

    ASSERT_NEAR(0.0f, var0->getNDArray()->reduceNumber<simdOps::Sum<float>>(), 1e-5);
    ASSERT_NEAR(12.0f, var1->getNDArray()->reduceNumber<simdOps::Sum<float>>(), 1e-5);
    ASSERT_NEAR(1.0f, var1->getNDArray()->reduceNumber<simdOps::Mean<float>>(), 1e-5);


    // now we're veryfying op graph
    ASSERT_EQ(1, graph->totalNodes());
}