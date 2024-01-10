//
// Created by Xavier VINCENT on 24/12/2023.
//

#pragma once
#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>

namespace Tools
{
  class EndianConverter {
   public:
    EndianConverter(boost::asio::const_buffer const &buffer);
    ~EndianConverter();
    boost::asio::const_buffer getLittleEndian();
    boost::asio::const_buffer getNativeEndian();
    boost::asio::const_buffer getBuffer() const;
    void setBuffer(boost::asio::const_buffer const &buffer);

   protected:
   private:
    boost::asio::const_buffer buffer;
  };
}
