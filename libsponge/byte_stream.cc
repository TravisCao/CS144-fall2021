#include "byte_stream.hh"
#include <iostream>

#include <iostream>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : _buffer(), _capacity(capacity), _end_write(false), _written_count(0), _read_count(0) {}

size_t ByteStream::write(const string &data) {
    size_t accepted_count = min(remaining_capacity(), data.size());
    _written_count += accepted_count;
    for (size_t i = 0; i < accepted_count; i++) {
        _buffer.push_back(data[i]);
    }
    return accepted_count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string output;
    size_t available_count = min(buffer_size(), len);
    for (size_t i = 0; i < available_count; i++) {
        output += _buffer.at(i);
    }
    return output;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t remove_count = min(len, buffer_size());
    _read_count += remove_count;
    for (size_t i = 0; i < remove_count; i++) {
        _buffer.pop_front();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string output = ByteStream::peek_output(len);
    ByteStream::pop_output(len);
    return output;
}

void ByteStream::end_input() { ByteStream::_end_write = true; }

bool ByteStream::input_ended() const { return ByteStream::_end_write; }

size_t ByteStream::buffer_size() const { return _buffer.size(); }

bool ByteStream::buffer_empty() const { return _buffer.empty(); }

bool ByteStream::eof() const { return buffer_empty() && _end_write; }

size_t ByteStream::bytes_written() const { return _written_count; }

size_t ByteStream::bytes_read() const { return _read_count; }

size_t ByteStream::remaining_capacity() const { return _capacity - buffer_size(); }