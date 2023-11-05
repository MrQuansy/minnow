#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), _buf(), _pushedBytes( 0 ), _poppedBytes( 0 ), _isError( 0 ), _isClosed( 0 )
{}

void Writer::push( string data )
{
  for ( auto&& i : data ) {
    if ( available_capacity() > 0 ) {
      _buf.push( i );
      _pushedBytes++;
    }
  }
  (void)data;
}

void Writer::close()
{
  _isClosed = true;
}

void Writer::set_error()
{
  _isError = true;
}

bool Writer::is_closed() const
{
  return { _isClosed };
}

uint64_t Writer::available_capacity() const
{
  return { capacity_ - _buf.size() };
}

uint64_t Writer::bytes_pushed() const
{
  return { _pushedBytes };
}

string_view Reader::peek() const
{
  return { string_view( &_buf.front(), 1 ) };
}

bool Reader::is_finished() const
{
  if ( bytes_buffered() == 0 && _isClosed == true )
    return { true };
  else
    return { false };
}

bool Reader::has_error() const
{
  return { _isError };
}

void Reader::pop( uint64_t len )
{
  while ( len-- ) {
    _buf.pop();
    _poppedBytes++;
  }
  (void)len;
}

uint64_t Reader::bytes_buffered() const
{
  return { _buf.size() };
}

uint64_t Reader::bytes_popped() const
{
  return { _poppedBytes };
}
