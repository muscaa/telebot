#pragma once

#include <boost/config.hpp>

#define EXPORT BOOST_SYMBOL_EXPORT
#define IMPORT BOOST_SYMBOL_IMPORT

#if defined(API_EXPORT)
  #define API EXPORT
#else
  #define API IMPORT
#endif
