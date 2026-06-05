#pragma once


#include <cstdint>
#include <cstddef>

#include <optional>
#include <memory>
#include <chrono>
#include <string>


namespace acx {

  
  // Smart pointer aliases

  template <typename T>
  using up = std::unique_ptr<T>;

  template <typename T>
  using sp = std::shared_ptr<T>;

  template <typename T>
  using wp = std::weak_ptr<T>;


  using std::move;


  // Type aliases

  using std::string;

  template <typename T>
  using opt = std::optional<T>;

  using std::chrono::steady_clock;
  using std::chrono::system_clock;


  // Numeric type aliases

  using u8 = uint8_t;
  using i16 = int16_t;
  using u16 = uint16_t;
  using i32 = int32_t;
  using u32 = uint32_t;
  using i64 = int64_t;
  using u64 = uint64_t;

  using usize = size_t;
  using isize = ptrdiff_t;
  using uptr = uintptr_t;
  using iptr = intptr_t;

  using f32 = float;
  using f64 = double;
  //long double is platform-dependent


}