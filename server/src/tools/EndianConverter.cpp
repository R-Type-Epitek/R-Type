//
// Created by Xavier VINCENT on 24/12/2023.
//

#include <boost/asio/buffer.hpp>
#include <boost/endian/conversion.hpp>
#include "tools/EndianConverter.hpp"

namespace Tools
{
  EndianConverter::EndianConverter(boost::asio::const_buffer const &buffer)
  {
    this->buffer = buffer;
  }

  EndianConverter::~EndianConverter()
  {
  }

  boost::asio::const_buffer EndianConverter::getLittleEndian()
  {
    return boost::asio::buffer(boost::endian::native_to_little(this->buffer));
  }

  boost::asio::const_buffer EndianConverter::getNativeEndian()
  {
    return boost::asio::buffer(boost::endian::native_to_little(this->buffer));
  }

  boost::asio::const_buffer EndianConverter::getBuffer() const
  {
    return this->buffer;
  }

  boost::asio::const_buffer EndianConverter::setBuffer(boost::asio::const_buffer const &buffer)
  {
    this->buffer = buffer;
  }
}
