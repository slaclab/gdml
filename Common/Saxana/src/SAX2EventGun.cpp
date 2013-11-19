//
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/URLInputSource.hpp>

#include "Saxana/SAXProcessor.h"
#include "Saxana/SAXEvents.h"
#include "Saxana/ASCIIAttributeList.h"
#include "Saxana/ProcessingConfigurator.h"

#include "Saxana/SAX2EventGun.h"
#include "Saxana/GDMLEntityResolver.h"

// // Disable deprecated warnings for usage of strstream on Linux
// // architectures with gcc >= 3.0 release
// //
// #if (__GNUC__==3) && (__GNUC_MINOR__>0)
//   #undef __DEPRECATED
// #endif
// #include <strstream>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace xercesc;

class Pimpl
{
public:
  SAX2XMLReader*          fParser;
  ProcessingConfigurator* fConfig;
};

StatusCode SAX2EventGun::Run()
{
  //  std::cout << "SAX2EventGun::Run()" << std::endl;

  StatusCode sc;

  fPimpl->fParser = XMLReaderFactory::createXMLReader();

  fResolver = new GDMLEntityResolver();
  fPimpl->fParser->setContentHandler( this );
  fPimpl->fParser->setErrorHandler( this );
  fPimpl->fParser->setEntityResolver( fResolver );

  /* Setup schema validation. */
  SetupSchemaValidation();

  const std::string& uri = fPimpl->fConfig->URI();
  const char* xmlfile = uri.c_str();

  try
    {
      fPimpl->fParser->parse( xmlfile );
    }
  catch (const XMLException& e)
    {
      const char* msg = XMLString::transcode( e.getMessage() );

      std::cerr << "\nError during parsing: '" << xmlfile << "'\n"
		<< "Exception message is:  \n"
		<< msg << "\n" << std::endl;
      if( msg != 0 )
	{
	  delete [] msg;
	}
      sc = StatusCode::eError;
    }
  catch (...)
    {
      std::cerr << "\nUnexpected exception during parsing: '" << xmlfile << "'\n";
      sc = StatusCode::eError;
    }

  return sc;
}

void SAX2EventGun::characters( const   XMLCh* const    chars,
			       const unsigned int    length )
  // Receive notification of #PCDATA characters in element content.
{
  char* ascii = 0;

  if( length > 0 ) {
    ascii = XMLString::transcode( chars );
    SAXEventCharacters event( ascii );

    fTarget->ProcessEvent( &event );

    if( ascii != 0 )
      {
	delete [] ascii;
      }
  }
}

void SAX2EventGun::endDocument()
  // Receive notification of the end of the document.
{
  SAXEventEndDocument event;
  fTarget->ProcessEvent( &event );
}

void SAX2EventGun::endElement( const XMLCh* const /*uri*/,
                               const XMLCh* const /*localname*/,
                               const XMLCh* const qname )
  // Receive notification of the end of an element.
{
  // We ignore in this implementation the XML namespaces, for the time being

  const char* ascii = 0;

  ascii = XMLString::transcode( qname );
  SAXEventEndElement event( ascii );
  fTarget->ProcessEvent( &event );

  if( ascii != 0 )
    {
      delete [] ascii;
    }
}

void SAX2EventGun::ignorableWhitespace( const   XMLCh* const    chars
                                        , const unsigned int    length )
  // Receive notification of ignorable whitespace in element content.
{
  char* ascii = 0;

  if( length > 0 ) {
    ascii = XMLString::transcode( chars );
    SAXEventCharacters event( ascii );
    fTarget->ProcessEvent( &event );

    if( ascii != 0 )
      {
	delete [] ascii;
      }
  }
}

void SAX2EventGun::processingInstruction( const   XMLCh* const    target
                                          , const XMLCh* const    data )
  // Receive notification of a processing instruction.
{
  char* ascii_target = 0;
  char* ascii_data   = 0;

  ascii_target = XMLString::transcode( target );
  ascii_data   = XMLString::transcode( data );
  SAXEventPI event( ascii_target, ascii_data );
  fTarget->ProcessEvent( &event );

  if( ascii_target != 0 )
    {
      delete [] ascii_target;
    }
  if( ascii_data   != 0 )
    {
      delete [] ascii_data;
    }
}

void SAX2EventGun::resetDocument()
  // Reset the Docuemnt object on its reuse
{
}

void SAX2EventGun::setDocumentLocator(const Locator* const)
  // Receive a Locator object for document events.
{
  //  fLocator = l;
  return;
}

void SAX2EventGun::startDocument()
  // Receive notification of the beginning of the document.
{
  SAXEventStartDocument event;
  fTarget->ProcessEvent( &event );
}

void SAX2EventGun::startElement( const XMLCh* const /*uri*/,
                                 const XMLCh* const /*localname*/,
                                 const XMLCh* const qname,
                                 const Attributes&  attributes )
  // Receive notification of the start of an element.
{
  // We ignore in this implementation the XML namespaces, for the time being

  char* ascii = 0;
  ASCIIAttributeList attrs;

  ascii = XMLString::transcode( qname );

  for( unsigned int i = 0; i < attributes.getLength(); i++ ) {
    // Let's transcode the attribute list
    char* name  = XMLString::transcode( attributes.getQName(i) );
    char* value = XMLString::transcode( attributes.getValue(i) );
    char* type  = XMLString::transcode( attributes.getType(i) );

    attrs.add( name, value, type );

    delete [] name;
    delete [] value;
    delete [] type;
  }

  SAXEventStartElement event( ascii, attrs );
  fTarget->ProcessEvent( &event );

  if( ascii != 0 )
    {
      delete [] ascii;
    }
}

void SAX2EventGun::error( const SAXParseException& exception )
  // Receive notification of a recoverable parser error.
{
  //   char* publicId = XMLString::transcode( exception.getPublicId() );
  char* systemId = XMLString::transcode( exception.getSystemId() );
  char* msg      = XMLString::transcode( exception.getMessage()  );

  std::stringstream msgstr;

  msgstr    << "error: "
    //             << "publicId: "  << publicId
	    << " systemId: " << systemId
	    << " line: "     << exception.getLineNumber()
	    << " column: "   << exception.getColumnNumber()
	    << "\n"
	    << msg;

  SAXEventError event( msgstr.str() );
  fTarget->ProcessEvent( &event );

  //   if( publicId != 0 )
  //   {
  //     delete [] publicId;
  //   }
  if( systemId != 0 )
    {
      delete [] systemId;
    }
  if( msg != 0 )
    {
      delete [] msg;
    }
}

void SAX2EventGun::fatalError( const SAXParseException& exception )
  // Report a fatal XML parsing error.
{
  //   char* publicId = XMLString::transcode( exception.getPublicId() );
  char* systemId = XMLString::transcode( exception.getSystemId() );
  char* msg      = XMLString::transcode( exception.getMessage()  );

  std::stringstream msgstr;
  msgstr    << "fatal error: "
    //             << "publicId: "  << publicId
	    << " systemId: " << systemId
	    << " line: "     << exception.getLineNumber()
	    << " column: "   << exception.getColumnNumber()
	    << "\n"
	    << msg;

  SAXEventFatalError event( msgstr.str() );
  fTarget->ProcessEvent( &event );

  //   if( publicId != 0 )
  //   {
  //     delete [] publicId;
  //   }
  if( systemId != 0 )
    {
      delete [] systemId;
    }
  if( msg != 0 )
    {
      delete [] msg;
    }
}

void SAX2EventGun::warning( const SAXParseException& exception )
  // Receive notification of a parser warning.
{
  //   char* publicId = XMLString::transcode( exception.getPublicId() );
  char* systemId = XMLString::transcode( exception.getSystemId() );
  char* msg      = XMLString::transcode( exception.getMessage()  );

  std::stringstream msgstr;
  msgstr    << "warning: "
    //             << "publicId: "  << publicId
	    << " systemId: " << systemId
	    << " line: "     << exception.getLineNumber()
	    << " column: "   << exception.getColumnNumber()
	    << "\n"
	    << msg;

  SAXEventWarning event( msgstr.str() );
  fTarget->ProcessEvent( &event );

  //   if( publicId != 0 )
  //   {
  //     delete [] publicId;
  //   }
  if( systemId != 0 )
    {
      delete [] systemId;
    }
  if( msg != 0 )
    {
      delete [] msg;
    }
}

void SAX2EventGun::resetErrors()
  // Reset the Error handler object on its reuse
{
}

void SAX2EventGun::notationDecl( const   XMLCh* const     // name
                                 , const XMLCh* const    // publicId
                                 , const XMLCh* const  ) // systemId
  // Receive notification of a notation declaration.
{
  ;
}

void SAX2EventGun::resetDocType()
  // Reset the DTD object on its reuse
{
  ;
}

void SAX2EventGun::unparsedEntityDecl( const   XMLCh* const    // name
                                       , const XMLCh* const   // publicId
                                       , const XMLCh* const   // systemId
                                       , const XMLCh* const ) // notationName
  // Receive notification of an unparsed entity declaration.
{
  ;
}

SAX2EventGun::SAX2EventGun( SAXProcessor* target )
  // : fTarget( target ), fParser( 0 ), fConfig( 0 )
  : fTarget( target ), fPimpl( new Pimpl() )
{
  fPimpl->fParser = 0;
  fPimpl->fConfig = 0;
}

SAX2EventGun::~SAX2EventGun()
{
  delete fPimpl;
}

const SAXProcessor* SAX2EventGun::Target() const
{
  return fTarget;
}

void SAX2EventGun::SetTarget( SAXProcessor* target )
{
  fTarget = target;
}

void SAX2EventGun::Configure( ProcessingConfigurator* config )
{
  fPimpl->fConfig = config;
}

/**
 * SAX2 options for schema validation.
 *
 * http://xml.apache.org/xerces-c/program-sax2.html
 */
void SAX2EventGun::SetupSchemaValidation()
{
  fPimpl->fParser->setFeature( XMLUni::fgXercesDynamic            , false );
  fPimpl->fParser->setFeature( XMLUni::fgSAX2CoreValidation       , true  );
  fPimpl->fParser->setFeature( XMLUni::fgXercesSchema             , true );
  fPimpl->fParser->setFeature( XMLUni::fgXercesSchemaFullChecking , true );
  fPimpl->fParser->setFeature( XMLUni::fgSAX2CoreNameSpaces       , true );
  fPimpl->fParser->setFeature( XMLUni::fgSAX2CoreNameSpacePrefixes, true );

#ifdef GDML_VERBOSE
  std::cout << "GDML Schema Validation is ENABLED." << std::endl;
#endif
}
