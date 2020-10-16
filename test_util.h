#include <chrono>
#include <memory>
#include <utility>
#include <vector>
#include <arrow/testing/gtest_util.h>

#include "gandiva/arrow.h"
#include "gandiva/configuration.h"


template<typename TYPE, typename C_TYPE>
static inline gandiva::ArrayPtr MakeArrowArray(std::vector<C_TYPE> values,
                                      std::vector<bool> validity) {
    gandiva::ArrayPtr out;
    arrow::ArrayFromVector<TYPE, C_TYPE>(validity, values, &out);
    return out;
}

template<typename TYPE, typename C_TYPE>
static inline gandiva::ArrayPtr MakeArrowArray(std::vector<C_TYPE> values) {
    gandiva::ArrayPtr out;
    arrow::ArrayFromVector<TYPE, C_TYPE>(values, &out);
    return out;
}

template<typename TYPE, typename C_TYPE>
static inline gandiva::ArrayPtr MakeArrowArray(const std::shared_ptr<arrow::DataType> &type,
                                      std::vector<C_TYPE> values,
                                      std::vector<bool> validity) {
    gandiva::ArrayPtr out;
    arrow::ArrayFromVector<TYPE, C_TYPE>(type, validity, values, &out);
    return out;
}

template<typename TYPE, typename C_TYPE>
static inline gandiva::ArrayPtr MakeArrowTypeArray(const std::shared_ptr<arrow::DataType> &type,
                                          const std::vector<C_TYPE> &values,
                                          const std::vector<bool> &validity) {
    gandiva::ArrayPtr out;
    arrow::ArrayFromVector<TYPE, C_TYPE>(type, validity, values, &out);
    return out;
}

#define MakeArrowArrayBool MakeArrowArray<arrow::BooleanType, bool>
#define MakeArrowArrayInt8 MakeArrowArray<arrow::Int8Type, int8_t>
#define MakeArrowArrayInt16 MakeArrowArray<arrow::Int16Type, int16_t>
#define MakeArrowArrayInt32 MakeArrowArray<arrow::Int32Type, int32_t>
#define MakeArrowArrayInt64 MakeArrowArray<arrow::Int64Type, int64_t>
#define MakeArrowArrayUint8 MakeArrowArray<arrow::UInt8Type, uint8_t>
#define MakeArrowArrayUint16 MakeArrowArray<arrow::UInt16Type, uint16_t>
#define MakeArrowArrayUint32 MakeArrowArray<arrow::UInt32Type, uint32_t>
#define MakeArrowArrayUint64 MakeArrowArray<arrow::UInt64Type, uint64_t>
#define MakeArrowArrayFloat32 MakeArrowArray<arrow::FloatType, float>
#define MakeArrowArrayFloat64 MakeArrowArray<arrow::DoubleType, double>
#define MakeArrowArrayDate64 MakeArrowArray<arrow::Date64Type, int64_t>
#define MakeArrowArrayUtf8 MakeArrowArray<arrow::StringType, std::string>
#define MakeArrowArrayBinary MakeArrowArray<arrow::BinaryType, std::string>
#define MakeArrowArrayDecimal MakeArrowArray<arrow::Decimal128Type, arrow::Decimal128>

#define EXPECT_ARROW_ARRAY_EQUALS(a, b)                               \
  EXPECT_TRUE((a)->Equals(b, arrow::EqualOptions().nans_equal(true))) \
      << "expected array: " << (a)->ToString() << " actual array: " << (b)->ToString()

#define EXPECT_ARROW_ARRAY_APPROX_EQUALS(a, b, epsilon)                           \
  EXPECT_TRUE(                                                                    \
      (a)->ApproxEquals(b, arrow::EqualOptions().atol(epsilon).nans_equal(true))) \
      << "expected array: " << (a)->ToString() << " actual array: " << (b)->ToString()

#define EXPECT_ARROW_TYPE_EQUALS(a, b)                                \
  EXPECT_TRUE((a)->Equals(b)) << "expected type: " << (a)->ToString() \
                              << " actual type: " << (b)->ToString()

static inline std::shared_ptr<gandiva::Configuration> TestConfiguration() {
    auto builder =gandiva:: ConfigurationBuilder();
    return builder.DefaultConfiguration();
}


