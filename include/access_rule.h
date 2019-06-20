#pragma once

namespace lika {

class AccessRule {

 private:
  unsigned firstIndex_;
  unsigned lastIndex_;
  unsigned step_;

 public:
  AccessRule();
  AccessRule(unsigned firstIndex, unsigned lastIndex, unsigned step);
  unsigned get(unsigned index) const;
  unsigned operator[](unsigned index) const;
  unsigned size() const;
  bool isRawData() const;
};

AccessRule::AccessRule() {}

AccessRule::AccessRule(unsigned firstIndex, unsigned lastIndex, unsigned step) {
  firstIndex_ = firstIndex;
  lastIndex_ = lastIndex;
  step_ = step;
}

unsigned AccessRule::get(unsigned index) const {
  return firstIndex_ + index * step_;
}

unsigned AccessRule::operator[](unsigned index) const {
  return firstIndex_ + index * step_;
}

unsigned AccessRule::size() const {
  return (lastIndex_ - firstIndex_) / step_ + 1;
}

bool AccessRule::isRawData() const {
  return step_ == 1;
}

}