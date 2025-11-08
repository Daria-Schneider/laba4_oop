#include <gtest/gtest.h>
#include <cmath>
#include <memory>
#include <type_traits>
#include <sstream>
#include "pentagon.h"
#include "hexagon.h" 
#include "octagon.h"
#include "array.h"

TEST(ConceptTest, ScalarTypeCheck) {
    static_assert(std::is_scalar_v<int>, "int should be scalar");
    static_assert(std::is_scalar_v<double>, "double should be scalar");
    static_assert(std::is_scalar_v<float>, "float should be scalar");
    static_assert(!std::is_scalar_v<std::string>, "string should not be scalar");
}

TEST(PentagonTest, AreaAndCenter) {
    Pentagon<double> pent;
    EXPECT_NEAR(pent.area(), 2.377, 0.001);
    
    auto center = pent.center();
    EXPECT_NEAR(center.x(), 0.0, 0.001);
    EXPECT_NEAR(center.y(), 0.0, 0.001);
}

TEST(PentagonTest, CustomConstructor) {
    Point<double> p1(0, 1), p2(-0.951, 0.309), p3(-0.588, -0.809), 
                  p4(0.588, -0.809), p5(0.951, 0.309);
    Pentagon<double> pent(p1, p2, p3, p4, p5);
    
    EXPECT_GT(pent.area(), 0);
    EXPECT_EQ(pent.vertex_count(), 5);
}

TEST(PentagonTest, DifferentTypes) {
    Pentagon<float> pent_float;
    Pentagon<int> pent_int;
    
    EXPECT_GT(pent_float.area(), 0);
    EXPECT_GE(pent_int.area(), 0);
}

TEST(HexagonTest, AreaAndCenter) {
    Hexagon<double> hex;
    EXPECT_NEAR(hex.area(), 2.598, 0.001);
    
    auto center = hex.center();
    EXPECT_NEAR(center.x(), 0.0, 0.001);
    EXPECT_NEAR(center.y(), 0.0, 0.001);
}

TEST(HexagonTest, SixVertices) {
    Hexagon<double> hex;
    EXPECT_EQ(hex.vertex_count(), 6);
}

TEST(OctagonTest, AreaAndCenter) {
    Octagon<double> oct;
    EXPECT_NEAR(oct.area(), 2.828, 0.001);
    
    auto center = oct.center();
    EXPECT_NEAR(center.x(), 0.0, 0.001);
    EXPECT_NEAR(center.y(), 0.0, 0.001);
}

TEST(OctagonTest, EightVertices) {
    Octagon<double> oct;
    EXPECT_EQ(oct.vertex_count(), 8);
}

TEST(FigureTest, DoubleConversion) {
    Pentagon<double> pent;
    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);
}

TEST(FigureTest, EqualityOperator) {
    Pentagon<double> pent1, pent2;
    Hexagon<double> hex;
    
    EXPECT_TRUE(pent1 == pent2);
    EXPECT_FALSE(pent1 == hex);
}

TEST(FigureTest, InequalityOperator) {
    Pentagon<double> pent1, pent2;
    Hexagon<double> hex;
    
    EXPECT_FALSE(pent1 != pent2);
    EXPECT_TRUE(pent1 != hex);
}

TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, EraseOperation) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.erase(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    
    Array<int> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, ResizeOperation) {
    Array<int> arr;
    
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    
    EXPECT_EQ(arr.size(), 10);
    EXPECT_GE(arr.capacity(), 10);
}

TEST(PointTest, BasicOperations) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(3.0, 4.0);
    
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
    EXPECT_EQ(p1.x(), 1.0);
    EXPECT_EQ(p1.y(), 2.0);
}

TEST(PointTest, IOOperations) {
    Point<double> p(5.5, 6.6);
    
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(5.5 6.6)");
}

TEST(IntegrationTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    figures.push_back(std::make_shared<Pentagon<double>>());
    figures.push_back(std::make_shared<Hexagon<double>>());
    figures.push_back(std::make_shared<Octagon<double>>());
    
    double totalArea = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        totalArea += static_cast<double>(*figures[i]);
    }
    
    EXPECT_GT(totalArea, 7.0);
    EXPECT_LT(totalArea, 8.0);
}

TEST(IntegrationTest, FigureDeletion) {
    Array<std::shared_ptr<Figure<double>>> figures;
    figures.push_back(std::make_shared<Pentagon<double>>());
    figures.push_back(std::make_shared<Hexagon<double>>());
    
    size_t initialSize = figures.size();
    figures.erase(0);
    
    EXPECT_EQ(figures.size(), initialSize - 1);
    EXPECT_EQ(figures[0]->vertex_count(), 6);
}

TEST(ArrayTest, MoveOnResize) {
    Array<std::string> arr;
    arr.push_back("test1");
    arr.push_back("test2");
    
    size_t old_capacity = arr.capacity();
    for (int i = 0; i < 10; ++i) {
        arr.push_back("test" + std::to_string(i + 3));
    }
    
    EXPECT_GT(arr.capacity(), old_capacity);
    EXPECT_EQ(arr.size(), 12);
}

TEST(ArrayTest, DifferentTemplateTypes) {
    Array<std::shared_ptr<Figure<double>>> figureArray;
    EXPECT_EQ(figureArray.size(), 0);
    
    Array<Hexagon<double>> hexagonArray;
    EXPECT_EQ(hexagonArray.size(), 0);
}

TEST(FigureTest, InputOutput) {
    Pentagon<double> pent;
    std::stringstream ss;
    ss << pent;
    
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find('('), std::string::npos);
}