//
// Created by ayesdie on 30/09/19.
//

#ifndef DOQ_DOCUMENT_HPP
#define DOQ_DOCUMENT_HPP

#include <fstream>
#include <ostream>

namespace doq
{

/**
 * Immutable Document based on standard containers.
 */
class document
{
public:
  /**
   * Imports contents of a file and save it in a string.
   * @param file_location - Location of file
   */
  document(const std::string &file_location);

  /**
   * Copy constructor for document;
   * @param doq - Document
   */
  document(const doq::document& doq);

  auto begin();
  auto end();
  auto &operator[](size_t);

private:
  std::string doc;
};

document::document(const std::string &file_location) {
  std::ifstream fin(file_location);

  if(fin)
  {
    doc = std::string((std::istreambuf_iterator<char>(fin)),
       std::istreambuf_iterator<char>());

    fin.close();
  }
}

document::document(const doq::document &doq) {
  doc = doq.doc;
}

auto &document::operator[](size_t index) {
  return doc[index];
}

auto document::begin() {
  return doc.begin();
}

auto document::end() {
  return doc.end();
}
} // namespace doq

#endif //DOQ_DOCUMENT_HPP
