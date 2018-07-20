//
// Created by liuchengde on 2018/7/16.
//


#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>

namespace chegde {
  namespace magic {
    struct OutOfRange {
      OutOfRange(unsigned pos, unsigned length) {}
    };

    constexpr unsigned requires_in_range(unsigned i, unsigned len) {
      return i >= len ? throw OutOfRange(i, len) : i;
    };


    class const_str {
      const char *const begin_;
      unsigned size_;

      public:
      template<unsigned N>
        constexpr const_str(const char (&arr)[N]) :begin_(arr), size_(N - 1) {
          static_assert(N >= 1, "not a string literal");
        }

      constexpr char operator[]( unsigned i ) const { 
        return requires_in_range(i, size_), begin_[i]; 
      }

      constexpr operator const char *() const { 
        return begin_; 
      }

      constexpr const char* begin() const { return begin_; }
      constexpr const char* end() const { return begin_ + size_; }

      constexpr unsigned size() const { 
        return size_; 
      }
    };

    const unsigned find_closing_tag(const_str s, unsigned p) {
      return s[p] == '>' ? p : find_closing_tag(s, p+1);
    }

  }

}

class util {
  public:
    static std::map<utility::string_t, utility::string_t> getParams(web::http::http_request message);

    static utility::string_t getPath(web::http::http_request message);
};

#endif //SERVER_UTIL_H
