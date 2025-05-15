#pragma once

#include <boost/config.hpp>

#if defined(TELEBOT_API_EXPORTS)
  #define API BOOST_SYMBOL_EXPORT
#else
  #define API BOOST_SYMBOL_IMPORT
#endif
