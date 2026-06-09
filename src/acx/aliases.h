#pragma once


#include <cstdint>
#include <cstddef>

#include <optional>
#include <memory>
#include <chrono>
#include <string>


namespace acx {


  // ===== Memory =====

  /// Exclusive ownership pointer.
  template <typename T>
  using up = std::unique_ptr<T>;

  /// Shared ownership pointer.
  template <typename T>
  using sp = std::shared_ptr<T>;

  /// Non-owning observer for a shared pointer.
  template <typename T>
  using wp = std::weak_ptr<T>;

  /// Exposes std::move inside the acx namespace.
  using std::move;


  // ===== std:: Types =====

  /// Standard dynamic string.
  using std::string;

  /// Optional value.
  template <typename T>
  using opt = std::optional<T>;

  /// Monotonic clock for measuring elapsed time.
  using std::chrono::steady_clock;

  /// Wall-clock time source.
  using std::chrono::system_clock;


  // ===== Numeric =====

  /// Signed 8-bit integer.
  using i8 = std::int8_t;

  /// Unsigned 8-bit integer.
  using u8 = std::uint8_t;

  /// Signed 16-bit integer.
  using i16 = std::int16_t;

  /// Unsigned 16-bit integer.
  using u16 = std::uint16_t;

  /// Signed 32-bit integer.
  using i32 = std::int32_t;

  /// Unsigned 32-bit integer.
  using u32 = std::uint32_t;

  /// Signed 64-bit integer.
  using i64 = std::int64_t;

  /// Unsigned 64-bit integer.
  using u64 = std::uint64_t;

  /// Unsigned size value.
  using usize = std::size_t;

  /// Signed size or pointer-difference value.
  using isize = std::ptrdiff_t;

  /// Unsigned integer large enough to store a pointer value.
  using uptr = std::uintptr_t;

  /// Signed integer large enough to store a pointer value.
  using iptr = std::intptr_t;

  /// Single-precision floating-point value.
  using f32 = float;

  /// Double-precision floating-point value.
  using f64 = double;

  // long double is omitted intentionally, as it is platform-dependent

  /// 32-bit identifier.
  using id_t = u32;

  /// 64-bit identifier.
  using lid_t = u64;

  /// Menu option id.
  using menu_option_t = i32;
}
