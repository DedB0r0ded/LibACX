// timЕ.h 
#pragma once
#ifdef ACX_TIME


#include <acx/strings.h>
#include <acx/aliases.h>
#include <acx/result.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <ctime>
#include <chrono>


namespace acx {


  class Time {
  private:
    static constexpr u16 FLAG_NULL = 1;

    u16 year_;
    u8 month_;
    u8 day_;
    u32 milliseconds_from_midnight_;
    i16 timezone_offset_minutes_;

    u8 leap_second_;
    u8 is_dst_;
    u16 microseconds_;
    u16 reserved_;

    // Private ctor for internal usage
    Time(u16 year, u8 month, u8 day, u32 milliseconds_from_midnight,
      i16 timezone_offset_minutes, u8 leap_second, u8 is_dst,
      u16 microseconds, u16 reserved) noexcept
      : year_(year), month_(month), day_(day),
      milliseconds_from_midnight_(milliseconds_from_midnight),
      timezone_offset_minutes_(timezone_offset_minutes),
      leap_second_(leap_second), is_dst_(is_dst),
      microseconds_(microseconds), reserved_(reserved) {
    }

  public:
    // Ctors

    Time() noexcept : Time(1970, 1, 1, 0, 0, 0, 0, 0, 0) {}

    static Time null() noexcept {
      return Time(1970, 1, 1, 0, 0, 0, 0, 0, FLAG_NULL);
    }


    // Static fabric instead of public ctors

    static Result<Time> create(u16 year, u8 month, u8 day,
      u32 milliseconds_from_midnight,
      i16 timezone_offset_minutes = 0,
      u8 leap_second = 0,
      u8 is_dst = 0,
      u16 microseconds = 0,
      u16 reserved = 0) {
      Time t(year, month, day, milliseconds_from_midnight, timezone_offset_minutes,
        leap_second, is_dst, microseconds, reserved);

      auto validation = t.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }

      return Ok(t);
    }


    // Rule of five

    Time(const Time&) = default;
    Time(Time&&) noexcept = default;
    Time& operator=(const Time&) = default;
    Time& operator=(Time&&) noexcept = default;
    ~Time() = default;


    // Getters

    u16 year() const noexcept { return year_; }
    u8 month() const noexcept { return month_; }
    u8 day() const noexcept { return day_; }
    u8 hours() const noexcept { return milliseconds_from_midnight_ / 3600000; }
    u8 minutes() const noexcept { return (milliseconds_from_midnight_ % 3600000) / 60000; }
    u8 seconds() const noexcept { return (milliseconds_from_midnight_ % 60000) / 1000; }
    u16 milliseconds() const noexcept { return milliseconds_from_midnight_ % 1000; }
    u32 milliseconds_from_midnight() const noexcept { return milliseconds_from_midnight_; }
    i16 timezone_offset_minutes() const noexcept { return timezone_offset_minutes_; }
    bool leap_second() const noexcept { return leap_second_ != 0; }
    bool is_dst() const noexcept { return is_dst_ != 0; }
    u16 microseconds() const noexcept { return microseconds_; }
    bool is_null() const noexcept { return (reserved_ & FLAG_NULL) != 0; }
    bool has_value() const noexcept { return !is_null(); }


    // Setters + validation

    Result<void> year(u16 value) noexcept {
      year_ = value;
      return validate();
    }

    Result<void> month(u8 value) noexcept {
      if (value < 1 || value > 12) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_MONTH_RANGE));
      }
      month_ = value;
      return Ok();
    }

    Result<void> day(u8 value) noexcept {
      if (value < 1 || value > 31) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_DAY_RANGE));
      }
      day_ = value;
      return Ok();
    }

    Result<void> hours(u8 value) noexcept {
      if (value > 23) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_HOUR_RANGE));
      }
      u32 current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      u32 current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      u32 current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        value * 3600000 +
        current_minutes * 60000 +
        current_seconds * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> minutes(u8 value) noexcept {
      if (value > 59) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_MINUTE_RANGE));
      }
      u32 current_hours = milliseconds_from_midnight_ / 3600000;
      u32 current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      u32 current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        value * 60000 +
        current_seconds * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> seconds(u8 value) noexcept {
      if (value > 59) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_SECOND_RANGE));
      }
      u32 current_hours = milliseconds_from_midnight_ / 3600000;
      u32 current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      u32 current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        current_minutes * 60000 +
        value * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> milliseconds(u16 value) noexcept {
      if (value > 999) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_MILLISECOND_RANGE));
      }
      u32 current_hours = milliseconds_from_midnight_ / 3600000;
      u32 current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      u32 current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        current_minutes * 60000 +
        current_seconds * 1000 +
        value;
      return Ok();
    }

    Result<void> milliseconds_from_midnight(u32 value) noexcept {
      u32 max_millis = 86400000 + (leap_second_ ? 1000 : 0);
      if (value >= max_millis) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_MIDNIGHT_RANGE));
      }
      milliseconds_from_midnight_ = value;
      return Ok();
    }

    Result<void> timezone_offset_minutes(i16 value) noexcept {
      if (!valid_timezone_offset(value)) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_TZ_RANGE));
      }
      timezone_offset_minutes_ = value;
      return Ok();
    }

    void leap_second(bool value) noexcept {
      leap_second_ = value ? 1 : 0;
    }

    void is_dst(bool value) noexcept {
      is_dst_ = value ? 1 : 0;
    }

    Result<void> set_microseconds(u16 value) noexcept {
      if (value >= 1000) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_MICROSECOND_RANGE));
      }
      microseconds_ = value;
      return Ok();
    }


    // Validation

    static bool valid_timezone_offset(i16 timezone_offset_minutes) noexcept {
      return timezone_offset_minutes >= -720 && timezone_offset_minutes <= 840;
    }

    bool has_valid_timezone_offset() const noexcept {
      return valid_timezone_offset(timezone_offset_minutes_);
    }

    Result<void> validate() const noexcept {
      if (month_ < 1 || month_ > 12) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_INVALID_MONTH));
      }
      if (day_ < 1 || day_ > 31) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_INVALID_DAY));
      }
      u32 max_millis = 86400000 + (leap_second_ ? 1000 : 0);
      if (milliseconds_from_midnight_ >= max_millis) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_INVALID_MILLISECONDS));
      }
      if (!has_valid_timezone_offset()) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_INVALID_TZ));
      }
      if (microseconds_ >= 1000) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_INVALID_MICROSECONDS));
      }
      return Ok();
    }


    // Depricated

    std::string validate_legacy() const {
      auto result = validate();
      if (result.is_ok()) {
        return std::string(TXT_EMPTY);
      }
      return result.error().message();
    }


    // Change to another timezone

    Result<void> move_to_timezone(i16 target_timezone_offset_minutes) noexcept {
      if (!valid_timezone_offset(target_timezone_offset_minutes)) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(ERR_TIME_TARGET_TZ));
      }
      int32_t diff = target_timezone_offset_minutes - timezone_offset_minutes_;
      timezone_offset_minutes_ = target_timezone_offset_minutes;
      int64_t new_millis = static_cast<int64_t>(milliseconds_from_midnight_) + (diff * 60000);
      // Next day processing
      if (new_millis < 0) {
        // TODO: reduce a day
        new_millis += 86400000;
      }
      else if (new_millis >= 86400000) {
        // TODO: increase a day
        new_millis -= 86400000;
      }
      milliseconds_from_midnight_ = static_cast<u32>(new_millis);
      return Ok();
    }


    // From/to std time types

    static Result<Time> from_tm(const std::tm& tm_info, i16 tz_offset = 0) noexcept {
      Time result;
      result.year_ = tm_info.tm_year + 1900;
      result.month_ = tm_info.tm_mon + 1;
      result.day_ = tm_info.tm_mday;
      result.milliseconds_from_midnight_ =
        tm_info.tm_hour * 3600000 +
        tm_info.tm_min * 60000 +
        tm_info.tm_sec * 1000;
      result.timezone_offset_minutes_ = tz_offset;
      result.leap_second_ = 0;
      result.is_dst_ = tm_info.tm_isdst > 0 ? 1 : 0;
      result.microseconds_ = 0;
      result.reserved_ = 0;
      auto validation = result.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }
      return Ok(result);
    }

    static Result<Time> from_time_t(std::time_t t, i16 tz_offset = 0) {
      std::tm tm_buf{};
      std::tm* tm_info = nullptr;
#ifdef _WIN32
      if (gmtime_s(&tm_buf, &t) != 0) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_TIME_T));
      }
      tm_info = &tm_buf;
#else
      tm_info = std::gmtime(&t);
#endif
      if (!tm_info) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_TIME_T));
      }
      return from_tm(*tm_info, tz_offset);
    }

    std::tm to_tm() const noexcept {
      std::tm tm_info = {};
      tm_info.tm_year = year_ - 1900;
      tm_info.tm_mon = month_ - 1;
      tm_info.tm_mday = day_;
      tm_info.tm_hour = hours();
      tm_info.tm_min = minutes();
      tm_info.tm_sec = seconds();
      tm_info.tm_isdst = is_dst_;
      return tm_info;
    }

    Result<std::time_t> to_time_t() const noexcept {
      auto validation = validate();
      if (!validation) {
        return Err<std::time_t>(validation.error().code(), validation.error().message());
      }
      std::tm tm_info = to_tm();
#ifdef _WIN32
      std::time_t result = _mkgmtime(&tm_info);
#else
      std::time_t result = timegm(&tm_info);
#endif
      if (result == -1) {
        return Err<std::time_t>(ErrorCode::INVALID_ARGUMENT, std::string( ERR_TIME_TO_TIME_T));
      }
      return Ok(result);
    }

    // system_clock processing

    static Result<Time> from_system_clock(const std::chrono::system_clock::time_point& tp,
      i16 tz_offset = 0) {
      std::time_t t = std::chrono::system_clock::to_time_t(tp);
      auto duration_since_epoch = tp.time_since_epoch();
      auto total_micros = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
      auto micros_in_second = total_micros % 1000000;
      u16 milliseconds_part = static_cast<u16>(micros_in_second / 1000);
      u16 microseconds_part = micros_in_second % 1000;
      auto result = from_time_t(t, tz_offset);
      if (!result) {
        return result;
      }
      Time time = result.value();
      auto millis_result = time.milliseconds(milliseconds_part);
      if (!millis_result) {
        return Err<Time>(millis_result.error().code(), millis_result.error().message());
      }
      auto micros_result = time.set_microseconds(microseconds_part);
      if (!micros_result) {
        return Err<Time>(micros_result.error().code(), micros_result.error().message());
      }
      return Ok(time);
    }

    Result<std::chrono::system_clock::time_point> to_system_clock() const {
      auto time_t_result = to_time_t();
      if (!time_t_result) {
        return Err<std::chrono::system_clock::time_point>(
          time_t_result.error().code(),
          time_t_result.error().message());
      }
      auto tp = std::chrono::system_clock::from_time_t(time_t_result.value());
      tp += std::chrono::milliseconds(milliseconds());
      tp += std::chrono::microseconds(microseconds());
      return Ok(tp);
    }

    // system_clock::time_point ctor (for reverse compatibility)
    explicit Time(const std::chrono::system_clock::time_point& tp, i16 tz_offset = 0) {
      auto result = from_system_clock(tp, tz_offset);
      if (result) {
        *this = result.value();
      }
      else {
        *this = Time(); // Fallback to the defaults
      }
    }


    // Serialization

    void to_bytes(u8* buffer) const noexcept {
      std::memcpy(buffer, this, sizeof(Time));
    }

    static Result<Time> from_bytes(const u8* buffer) {
      if (buffer == nullptr) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string( ERR_TIME_BUFFER_NULL));
      }
      Time t;
      std::memcpy(&t, buffer, sizeof(Time));
      auto validation = t.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }
      return Ok(t);
    }


    // Comparison ops

    bool operator==(const Time& other) const noexcept {
      if (this == &other) return true;
      return std::memcmp(this, &other, sizeof(Time)) == 0;
    }

    bool operator!=(const Time& other) const noexcept {
      return !(*this == other);
    }

    bool operator<(const Time& other) const noexcept {
      if (year_ != other.year_) return year_ < other.year_;
      if (month_ != other.month_) return month_ < other.month_;
      if (day_ != other.day_) return day_ < other.day_;
      if (milliseconds_from_midnight_ != other.milliseconds_from_midnight_)
        return milliseconds_from_midnight_ < other.milliseconds_from_midnight_;
      return microseconds_ < other.microseconds_;
    }

    bool operator<=(const Time& other) const noexcept {
      return *this < other || *this == other;
    }

    bool operator>(const Time& other) const noexcept {
      return !(*this <= other);
    }

    bool operator>=(const Time& other) const noexcept {
      return !(*this < other);
    }


    // String values

    static Result<Time> from_string(std::string_view value) {
      std::string text(value);
      unsigned year = 0;
      unsigned month = 0;
      unsigned day = 0;
      unsigned hour = 0;
      unsigned minute = 0;
      unsigned second = 0;
      unsigned millisecond = 0;
      unsigned microsecond = 0;
      unsigned timezone_hours = 0;
      unsigned timezone_minutes = 0;
      char timezone_sign_char = '\0';
      bool leap_second = false;
      bool is_dst = false;
      int parsed = 0;
      if (std::sscanf(text.c_str(), "%4u-%2u-%2uT%2u:%2u:%2u.%3u%c%2u:%2u%n",
        &year, &month, &day, &hour, &minute, &second, &millisecond,
        &timezone_sign_char, &timezone_hours, &timezone_minutes, &parsed) != 10 ||
        parsed != static_cast<int>(text.size())) {
        parsed = 0;
        if (std::sscanf(text.c_str(), "%4u-%2u-%2u %2u:%2u:%2u.%3u.%3u%n",
          &year, &month, &day, &hour, &minute, &second, &millisecond,
          &microsecond, &parsed) != 8) {
          return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_PARSE));
        }
        if (text.compare(parsed, 5, TXT_LEAP_SECOND) == 0) {
          leap_second = true;
          parsed += 5;
        }
        int timezone_end = 0;
        if (std::sscanf(text.c_str() + parsed, " (UTC%c%2u:%2u)%n",
          &timezone_sign_char, &timezone_hours, &timezone_minutes, &timezone_end) != 3) {
          return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_PARSE));
        }
        parsed += timezone_end;
        if (text.compare(parsed, text.size() - parsed, TXT_DST) == 0) {
          is_dst = true;
          parsed = static_cast<int>(text.size());
        }
        if (parsed != static_cast<int>(text.size())) {
          return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_PARSE));
        }
      }
      if (timezone_sign_char != '+' && timezone_sign_char != '-') {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_PARSE));
      }
      if (year > 65535 || month > 255 || day > 255 ||
        hour > 23 || minute > 59 || second > 59 ||
        millisecond > 999 || microsecond > 999 ||
        timezone_hours > 23 || timezone_minutes > 59) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(ERR_TIME_PARSE));
      }
      int timezone_sign = timezone_sign_char == '-' ? -1 : 1;
      int timezone_offset = timezone_sign * static_cast<int>(timezone_hours * 60 + timezone_minutes);
      u32 milliseconds_from_midnight =
        static_cast<u32>(hour * 3600000 + minute * 60000 + second * 1000 + millisecond);
      return create(
        static_cast<u16>(year),
        static_cast<u8>(month),
        static_cast<u8>(day),
        milliseconds_from_midnight,
        static_cast<i16>(timezone_offset),
        leap_second ? 1 : 0,
        is_dst ? 1 : 0,
        static_cast<u16>(microsecond));
    }

    std::string to_string() const {
      char buffer[128];
      std::snprintf(buffer, sizeof(buffer),
        FMT_TIME_STRING.data(),
        year_, month_, day_, hours(), minutes(), seconds(),
        milliseconds(), microseconds(),
        leap_second() ?  TXT_LEAP_SECOND.data() :  TXT_EMPTY.data(),
        timezone_offset_minutes_ / 60,
        static_cast<unsigned>(std::abs(timezone_offset_minutes_ % 60)),
        is_dst() ? TXT_DST.data() : TXT_EMPTY.data());
      return std::string(buffer);
    }

    std::string to_iso8601() const {
      char buffer[64];
      std::snprintf(buffer, sizeof(buffer),
        FMT_TIME_ISO8601.data(),
        year_, month_, day_, hours(), minutes(), seconds(),
        milliseconds(),
        timezone_offset_minutes_ / 60,
        static_cast<unsigned>(std::abs(timezone_offset_minutes_ % 60)));
      return std::string(buffer);
    }


    // Current time

    static Result<Time> now() {
      auto t_now = std::chrono::system_clock::now();
      return from_system_clock(t_now);
    }
  };


} // namespace acx


#endif
