/*L*****************************************************************************
*
*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install, copy
*  or use the software.
*
*                Software License Agreement (BSD License)
*             For Smart Surveillance Interest Group Library
*                         http://ssig.dcc.ufmg.br
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#include "ssiglib/ml/pca_embedding.hpp"

namespace ssig {
cv::Ptr<PCAEmbedding> PCAEmbedding::create(const int dimensions) {
  auto ans = cv::Ptr<PCAEmbedding>(new PCAEmbedding());
  ans->mDimensions = dimensions;
  return ans;
}

PCAEmbedding::PCAEmbedding(const PCAEmbedding& rhs) {
  // Constructor Copy
  this->mDimensions = rhs.mDimensions;
}

PCAEmbedding& PCAEmbedding::operator=(const PCAEmbedding& rhs) {
  if (this != &rhs) {
    this->mDimensions = rhs.mDimensions;
  }
  return *this;
}

void PCAEmbedding::learn(cv::InputArray input) {
#ifdef _WIN32
  mPCA = std::make_unique<cv::PCA>();
#else
  mPCA = std::unique_ptr<cv::PCA>(new cv::PCA());
#endif
  cv::Mat X = input.getMat();
  mPCA->operator()(X, cv::noArray(), cv::PCA::DATA_AS_ROW);

}

void PCAEmbedding::project(
  cv::InputArray sample,
  cv::OutputArray output) {
  cv::Mat X = sample.getMat();
 
  output.create(X.rows, X.cols, CV_32F);
  mPCA->project(sample, output);
  cv::Mat dst = output.getMat();

  dst = dst.colRange(0, mDimensions);
  dst.copyTo(output);
}

void PCAEmbedding::read(const cv::FileNode& fn) {}

void PCAEmbedding::write(cv::FileStorage& fs) const {}
}  // namespace ssig