#include "Saxana/GDMLEntityResolver.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/framework/URLInputSource.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace xercesc;
using std::string;
using std::vector;
using std::ifstream;
using std::endl;
using std::cout;

GDMLEntityResolver::GDMLEntityResolver()
{
  // Add the current working directory to search path.
  addSearchDir(getCurrentWorkingDir());

  // Add the variable GDML_SCHEMA_DIR to search path.
  char* env;
  env = getenv("GDML_SCHEMA_DIR");
  if (env != NULL) {
    addSearchDir(string(env));
  }
}

GDMLEntityResolver::~GDMLEntityResolver()
{;}

/**
 * A simple implementation of entity resolution that tries to find a matching local resource from
 * a URL's base filename or (secondarily) from the full directory structure after the base address.
 * An absolute URL with the "file:" protocol is returned if the document is found locally.  Otherwise,
 * a null input source is returned, so that Xerces' default entity resolution will be used instead.
 * --JM
 * @return Returns an InputSource pointing to a local copy, if found, or NULL, if no local copy was found.
 */
InputSource* GDMLEntityResolver::resolveEntity( const XMLCh* const, const XMLCh* const systemId)
{

  // Default to a null InputSource.
  InputSource* isrc = 0;

  // Make a string from the systemId.
  string sysIdStr = string( XMLString::transcode(systemId) );

  //std::cout << "resolveEntity - " << sysIdStr << std::endl;

  // Get the current working dir.
  // TODO:  Possible to not limit CWD to PATH_MAX?  --JM
  char ccwd[FILENAME_MAX];
  getcwd(ccwd, FILENAME_MAX);
  string cwd = string(ccwd);

  // Extract the base filename, e.g. all chars after last '/'.
  string::size_type lastSlashIdx = sysIdStr.find_last_of('/');
  string fileName;

  // If a '/' not found, then only the filename is pulled-out, ignoring rest of relative path or URL.
  if ( lastSlashIdx != string::npos ) {
    fileName = string(sysIdStr, lastSlashIdx + 1);
  }
  // If no '/' was found, the systemId is used verbatim.
  else {
    fileName = string(sysIdStr);
  }

  // Try to create an InputSource from this filename.
  isrc = createInputSource(fileName);

  // If a source was not found, try finding it with just the base address stripped out,
  // leaving the directory structure from the URL intact.
  if (isrc == 0) {
    fileName = makePath(sysIdStr);
    isrc = createInputSource(fileName);
  }

  // Print an info mesg if this function redirected to a local copy.
#ifdef GDML_VERBOSE
  if ( isrc != 0 ) {
    cout << "GDML - systemId <" << sysIdStr << "> redirected to <" << XMLString::transcode(isrc->getSystemId()) << ">." << endl;
  }
#endif

  return isrc;
}

bool GDMLEntityResolver::haveSearchDir(std::string dir)
{
  bool fnd = false;
  for (vector<string>::const_iterator iter = m_dirs.begin();
       iter != m_dirs.end();
       iter++) {
    if ((*iter) == dir) {
      fnd = true;
      break;
    }
  }
  return fnd;
}

void GDMLEntityResolver::addSearchDir(string dir)
{
  if (!haveSearchDir(dir)) {

#ifdef GDML_VERBOSE
    cout << "GDML - Adding schema search directory <" << dir << ">." << endl;
#endif

    m_dirs.push_back(dir);
  }
}

/*
 * Get current working dir.
 * FIXME: Arbitrary limit PATH_MAX on size of path. --JM
 */
string GDMLEntityResolver::getCurrentWorkingDir()
{
  char ccwd[FILENAME_MAX];
  getcwd(ccwd, FILENAME_MAX);
  return string(ccwd);
}

InputSource* GDMLEntityResolver::createInputSource(string fname)
{
  InputSource* isrc = 0;

  // Loop over the list of base search directories.
  for (vector<string>::const_iterator iter = m_dirs.begin();
       iter != m_dirs.end();
       iter++) {

    const string& dir = (*iter);

    // Try to open the path -> search_dir + "/" + fname
    string path = dir + string("/") + fname;
    ifstream fin;
    fin.open(path.c_str(), std::ios::in);

    // Open was successful?
    if ( !fin.fail() ) {

      // Setup the "file:" protocol URL pointing to a local copy.
      string urlStr = string("file://") + path;

      // Make a URL from the string.
      const XMLURL url = XMLURL(urlStr.c_str());

      // Make an input source from the URL.
      isrc = new URLInputSource(url);

      // Add the search dir from the local path that was found.
      addSearchDir(path.substr(0, path.find_last_of("/") + 1));

      break;
    }
  }

  return isrc;
}

std::string GDMLEntityResolver::makePath(string url)
{
  std::string path = url;

  size_t i = url.find("://");

  if (i != string::npos) {
    size_t ii = url.find_first_of("/", i + 3);

    if (ii != string::npos) {
      ii += 1;

      path = url.substr(ii);
    }
  }

  //std::cout << "path: " << path << std::endl;

  return path;
}
