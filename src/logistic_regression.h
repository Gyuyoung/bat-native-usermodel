// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SRC_LOGISTIC_REGRESSION_H_
#define SRC_LOGISTIC_REGRESSION_H_

#include <vector>
#include "bag_of_words_extractor.h"
#include "deps/bat-native-rapidjson/include/rapidjson/document.h"
#include "deps/bat-native-rapidjson/include/rapidjson/writer.h"
#include "deps/bat-native-rapidjson/include/rapidjson/stringbuffer.h"

namespace usermodel {
class LogisticRegression {
 public:
  LogisticRegression();
  ~LogisticRegression();
  bool LoadModel(const std::string& model);
  std::vector<double> Predict(std::map<std::string, double> features);

 private:
  std::vector<std::string> features_;
  std::map<std::string, double> weights_;
  double bias_;
};
}  // namespace usermodel

#endif  // SRC_LOGISTIC_REGRESSION_H_
