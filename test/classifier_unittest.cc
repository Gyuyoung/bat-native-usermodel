/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// #include "brave/vendor/bat-native-usermodel/src/data_point.h"
#include "brave/vendor/bat-native-usermodel/src/classifier.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace usermodel {

class Classifier_Test : public ::testing::Test {
 protected:
  Classifier_Test() {}
  ~Classifier_Test() override {}
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(Classifier_Test, Three_classes_test) {
  std::map<std::string,Data_point> weights = {
    {"class_1", std::vector<float>{1.0, 0.0, 0.0}},
    {"class_2", std::vector<float>{0.0, 1.0, 0.0}},
    {"class_3", std::vector<float>{0.0, 0.0, 1.0}}
  };
  std::map<std::string,float> biases = {
    {"class_1",0.0},
    {"class_2", 0.0},
    {"class_3",0.0}
  };
  Linear_classifier linear_classifier(weights,biases);
  
  auto class1 = Data_point(std::vector<float>{1.0, 0.0, 0.0});
  auto rez1 = linear_classifier.Predict(class1);
  EXPECT_TRUE(rez1["class_1"] > rez1["class_2"]);
  EXPECT_TRUE(rez1["class_1"] > rez1["class_3"]);

  auto class2 = Data_point(std::vector<float>{0.0, 1.0, 0.0});
  auto rez2 = linear_classifier.Predict(class2);
  EXPECT_TRUE(rez2["class_2"] > rez2["class_1"]);
  EXPECT_TRUE(rez2["class_2"] > rez2["class_3"]);

  auto class3 = Data_point(std::vector<float>{0.0, 1.0, 2.0});
  auto rez3 = linear_classifier.Predict(class3);
  EXPECT_TRUE(rez3["class_3"] > rez3["class_1"]);
  EXPECT_TRUE(rez3["class_3"] > rez3["class_2"]);
}

TEST_F(Classifier_Test, Biases_test) {
  std::map<std::string,Data_point> weights = {
    {"class_1", std::vector<float>{1.0, 0.0, 0.0}},
    {"class_2", std::vector<float>{0.0, 1.0, 0.0}},
    {"class_3", std::vector<float>{0.0, 0.0, 1.0}}
  };
  std::map<std::string,float> biases = {
    {"class_1",0.0},
    {"class_2", 0.0},
    {"class_3",1.0}
  };
  Linear_classifier biased_classifier(weights,biases);
  
  auto avg_point = Data_point(std::vector<float>{1.0, 1.0, 1.0});
  auto rez = biased_classifier.Predict(avg_point);
  EXPECT_TRUE(rez["class_3"] > rez["class_1"]);
  EXPECT_TRUE(rez["class_3"] > rez["class_2"]);


}

}  // namespace usermodel