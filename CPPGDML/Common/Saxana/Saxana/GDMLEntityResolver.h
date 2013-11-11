#ifndef GDML_ENTITY_RESOLVER_H
#define GDML_ENTITY_RESOLVER_H 1

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/EntityResolver.hpp>

#if defined( XERCES_HAS_CPP_NAMESPACE )
using namespace xercesc;
#endif

#include <vector>
#include <string>

/**
 * @class GDMLEntityResolver
 * @brief EntityResolver for GDML's SAX2EventGun.
 * @note This class will search in the current directory and in
 *       the directory pointed to by the GDML_SCHEMA_DIR enviroment
 *       varible.
 */
class GDMLEntityResolver : public EntityResolver
{
 public:
  GDMLEntityResolver();
  virtual ~GDMLEntityResolver();

 public:

  /**
   * Resolve an entity to a local source, or return null if not
   * found locally, so that Xerces default resolution will occur.
   */
  InputSource* resolveEntity(const XMLCh* const, const XMLCh* const);

  /**
   * Add a local search path for GDML to look for local entity copies.
   */
  void addSearchDir(std::string dir);

  /**
   * Does GDML already have this search dir?
   */
  bool haveSearchDir(std::string dir);

 private:

  /**
   * Create an input source from the local file path.
   */
  InputSource* createInputSource(std::string fname);

 private:

  /**
   * Get the current working directory.
   */
  std::string getCurrentWorkingDir();

  /**
   * Extract the path part from a URL.
   *
   * http://www.example.com/my/path/someSchema.xsd -> /my/path/someSchema.xsd
   *
   */
  std::string makePath(std::string url);

 private:
  std::vector<std::string> m_dirs;
};

#endif
