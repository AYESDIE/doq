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
  auto size();
  auto &operator[](size_t);

  const std::string &getFileName() const;

private:
  std::string doc;
  std::string file_name;
};

document::document(const std::string &file_location)
{
  std::ifstream fin(file_location);

  if(fin)
  {
    doc = std::string((std::istreambuf_iterator<char>(fin)),
       std::istreambuf_iterator<char>());

    fin.close();
  }

  std::string temp;

  for (auto i = file_location.end(); i != file_location.begin() ; --i)
  {
    if (*i == '/')
      break;

    if (*i == '\0')
      continue;

    temp += *i;
  }
  
  file_name = temp;
  for (int i = 0; file_name[i] != '\0'; i++)
  {
    file_name[i] = temp[temp.size() - 1 - i];
  }
}

document::document(const doq::document &doq)
{
  doc = doq.doc;
}

auto document::begin()
{
  return doc.begin();
}

auto document::end()
{
  return doc.end();
}

auto document::size()
{
  return doc.size();
}

auto &document::operator[](size_t index)
{
  return doc[index];
}

const std::string &document::getFileName() const
{
  return file_name;
}

} // namespace doq

#endif //DOQ_DOCUMENT_HPP
