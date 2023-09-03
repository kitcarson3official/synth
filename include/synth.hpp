#pragma once
#include <functional>
#include <vector>

namespace synth {
class Block {
  using BlockFunction = std::function<float(std::vector<float>)>;

public:
  Block(BlockFunction f, unsigned int f_args_len)
      : f{f}, f_args_len(f_args_len) {}
  Block(const Block &o) = delete;
  Block(Block &&moved) = delete;
  inline float get() const { return x; }
  inline void update() { x += dx; }
  inline void step() {
    std::vector<float> params(f_args_len);
    for (auto [i, b] : param_map) {
      params[i] = b->get();
    }
    dx = f(params);
  }

private:
  BlockFunction f;
  unsigned int f_args_len;
  std::vector<std::pair<unsigned int, Block *>> param_map;
  float x, dx;
};

class Synth {
public:
  ~Synth();

private:
  std::vector<Block *> blocks;
};
} // namespace synth
