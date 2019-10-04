//
// Created by ayesdie on 30/09/19.
//

#include <fstream>
#include <ostream>

#ifndef DOQ_DOCUMENT_HPP
#define DOQ_DOCUMENT_HPP

namespace doq
{

/**
 * Immutable Document based on standard containers.
 */
class Document
{
public:
  inline Document();

  /**
   * Imports contents of a file and save it in a string.
   * @param file_location - Location of file
   */
  inline Document(const std::string &file_location);

  inline auto begin() const;
  inline auto end() const;
  inline auto size() const;
  inline auto &operator[](size_t);

  /**
   * Returns the file name.
   */
  inline const std::string& getFileName() const;

private:
  std::string doc;
  std::string file_name;
};

Document::Document()
{ /* does nothing */ }

Document::Document(const std::string &file_location)
{
  std::ifstream fin(file_location);

  if(!fin)
  {
    throw std::logic_error("Cannot open file");
  }

  doc = std::string((std::istreambuf_iterator<char>(fin)),
     std::istreambuf_iterator<char>());

  fin.close();

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

auto Document::begin() const
{
  return doc.begin();
}

auto Document::end() const
{
  return doc.end();
}

auto Document::size() const
{
  return doc.size();
}

auto &Document::operator[](size_t index)
{
  return doc[index];
}

const std::string& Document::getFileName() const
{
  return this->file_name;
}

} // namespace doq

#endif //DOQ_DOCUMENT_HPP
