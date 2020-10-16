#include <iostream>
#include "arrow/memory_pool.h"
#include "test_util.h"
#include "gandiva/projector.h"
#include "gandiva/filter.h"
#include <ctime>

#include "gandiva/tree_expr_builder.h"

using arrow::boolean;
using arrow::float32;
using arrow::int32;
using arrow::utf8;
using gandiva::TreeExprBuilder;
using gandiva::Projector;
using gandiva::Configuration;
using gandiva::SelectionVector;
using gandiva::Filter;
using std::cout;
using std::endl;

int main() {
    arrow::MemoryPool* pool_ = arrow::default_memory_pool();
    // schema for input fields
    auto field_a = field("a", utf8());

    //a=="hello"
    auto schema = arrow::schema({field_a});
    auto node_f0 = TreeExprBuilder::MakeField(field_a);

    auto literal_s = TreeExprBuilder::MakeStringLiteral("hello");
    auto equal = TreeExprBuilder::MakeFunction("equal", {node_f0, literal_s},
                                                      arrow::boolean());
    auto condition = TreeExprBuilder::MakeCondition(equal);

    std::shared_ptr<Filter> filter;
    clock_t  start = clock();
    auto status = Filter::Make(schema, condition, TestConfiguration(), &filter);
    clock_t  finish = clock();
    cout<< (double)(finish - start)<<endl;
    cout<<filter.get()<<endl;

    //a=="foo"
    auto literal_s1 = TreeExprBuilder::MakeStringLiteral("foo");
    auto equal1 = TreeExprBuilder::MakeFunction("equal", {node_f0, literal_s1},
                                               arrow::boolean());
    auto condition1 = TreeExprBuilder::MakeCondition(equal1);

    std::shared_ptr<Filter> filter2;
    start = clock();
    auto status2 = Filter::Make(schema, condition1, TestConfiguration(), &filter2);
    finish = clock();
    cout<< (double)(finish - start)<<endl;
    cout<<filter2.get()<<endl;

    int num_records = 4;
    auto array_a =
            MakeArrowArrayUtf8({"foo", "hello", "hello", "hi"}, {true, true, true, false});

    auto in_batch = arrow::RecordBatch::Make(schema, num_records, {array_a});

    std::shared_ptr<SelectionVector> selection_vector;
    status = SelectionVector::MakeInt16(num_records, pool_, &selection_vector);

    status = filter2->Evaluate(*in_batch, selection_vector);

    cout<<selection_vector.get()->ToArray()->ToString();

    return 0;
}
