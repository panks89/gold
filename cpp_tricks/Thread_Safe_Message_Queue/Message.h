#pragma once

template<typename T>
class Message
{
  T data;
 public:
 Message(const T & d) : data(d) { }
  const T& getData() const { return data; }
};
