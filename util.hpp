// concat-fuse
// Copyright (C) 2015 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_UTIL_HPP
#define HEADER_UTIL_HPP

#include <assert.h>
#include <sstream>

bool is_hex(char c)
{
  return (('0' <= c && c <= '9') ||
          ('a' <= c && c <= 'f') ||
          ('A' <= c && c <= 'F'));
}

int hex2int(char c)
{
  if ('0' <= c && c <= '9')
  {
    return c - '0';
  }
  else if ('a' <= c && c <= 'f')
  {
    return c - 'a' + 10;
  }
  else if ('A' <= c && c <= 'F')
  {
    return c - 'A' + 10;
  }
  else
  {
    return 0;
  }
}

std::string url_quote(const std::string& url)
{
  std::ostringstream str;
  str.fill('0');
  str << std::hex;
   
  for(std::string::size_type i = 0; i < url.size(); ++i)
  {
    if (isalpha(url[i]))
    {
      str << url[i];
    }
    else
    {
      str << "%" << static_cast<int>(url[i]);
    }
  }
  
  return str.str();
}

std::string url_unquote(const std::string& url)
{
  std::ostringstream str;

  for(std::string::size_type i = 0; i < url.size(); ++i)
  {
    if (url[i] == '%')
    {
      if (i+2 < url.size() && is_hex(url[i+1]) && is_hex(url[i+2]))
      {
        char c = (hex2int(url[i+1]) << 4) | hex2int(url[i+2]);
        std::cout << hex2int(url[i+1]) << " -- " << hex2int(url[i+2]) << std::endl;
        str << c;
        i += 2;
      }
      else
      {
        // failed to decode escape, so leave it untouched
        str << url[i];
      }
    }
    else
    {
      str << url[i];
    }
  }
  
  return str.str();
}

bool has_prefix(const char* text, const char* prefix)
{
  size_t prefix_len = strlen(prefix);
  size_t text_len = strlen(text);
  if (text_len < prefix_len)
  {
    return false;
  }
  else
  {
    return strncmp(prefix, text, prefix_len) == 0;
  }
}

#endif

/* EOF */
