#include <cmath>
#include <random>

struct Point {
  float x;
  float y;
  float z;
};

static void rejectionSampling(benchmark::State &state) {
  std::mt19937 g;
  std::uniform_real_distribution<float> uniform(0.0, 1.0);
  for (auto _ : state) {
    Point pt;
    float d = 2.0;
    while (d > 1.0) {
      pt.x = uniform(g) * 2.0 - 1.0;
      pt.y = uniform(g) * 2.0 - 1.0;
      pt.z = uniform(g) * 2.0 - 1.0;
      d = pt.x * pt.x + pt.y * pt.y + pt.z * pt.z;
    }
    benchmark::DoNotOptimize(pt);
  }
}
BENCHMARK(rejectionSampling);

static void normallyDistributedSampling(benchmark::State &state) {
  std::mt19937 g;
  std::normal_distribution<float> normal(0.0, 1.0);
  std::uniform_real_distribution<float> uniform(0.0, 1.0);
  for (auto _ : state) {
    float u = uniform(g);
    float x1 = normal(g);
    float x2 = normal(g);
    float x3 = normal(g);

    float mag = std::sqrt(x1 * x1 + x2 * x2 + x3 * x3);
    x1 /= mag;
    x2 /= mag;
    x3 /= mag;
    float c = std::cbrt(u);
    Point pt{x1 * c, x2 * c, x3 * c};
    benchmark::DoNotOptimize(pt);
  }
}
BENCHMARK(normallyDistributedSampling);

static void sphericalSampling(benchmark::State &state) {
  std::mt19937 g;
  std::uniform_real_distribution<float> uniform(0.0, 1.0);
  constexpr float PI = 3.14159265358979323846;
  for (auto _ : state) {
    float u = uniform(g);
    float v = uniform(g);
    float theta = u * 2.0 * PI;
    float phi = std::acos(2.0 * v - 1.0);
    float r = std::cbrt(uniform(g));
    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);
    float sinPhi = std::sin(phi);
    float cosPhi = std::cos(phi);

    Point pt{r * sinPhi * cosTheta, r * sinPhi * sinTheta, r * cosPhi};
    benchmark::DoNotOptimize(pt);
  }
}
BENCHMARK(normallyDistributedSampling);
