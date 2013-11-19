#include "Writer/Document.h"
#include "Writer/Element.h"

#include <iostream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    Document::Document( std::ostream& outstream )
      : m_document( 0 ),
				m_stream( outstream ),
				m_initialized( false ),
				m_schemaURL( "gdml_2.0.xsd" )
    {
      Initialize();
    }

    Document::~Document()
    {
      if( m_initialized )
        Release();
    }

    void Document::Initialize()
    {
      if( !m_initialized )
      {
        m_document = new Element( "gdml" );
        m_document->addAttribute( "xmlns:gdml"                    , "http://cern.ch/2001/Schemas/GDML" );
        m_document->addAttribute( "xmlns:xsi"                     , "http://www.w3.org/2001/XMLSchema-instance" );
        m_document->addAttribute( "xsi:noNamespaceSchemaLocation" , m_schemaURL );
        
        // Pre-create the GDML structure
        m_document->appendChild( Element( "define" ) );
        m_document->appendChild( Element( "materials" ) );
        m_document->appendChild( Element( "solids" ) );
        m_document->appendChild( Element( "structure" ) );
        
        m_initialized = true;
      }
    }
    
    void Document::Release()
    {
      // Flush stream buffers
      m_stream << std::flush;
      
      if( m_document != 0 )
        delete m_document;

      m_initialized = false;
    }

    const Element& Document::getDocument() const
    {
      // Make sure the document is in a valid state
      if( !m_initialized )
        const_cast<Document*>(this)->Initialize();
      
      return *m_document;
    }

    Element& Document::getDocument()
    {
      // Make sure the document is in a valid state
      if( !m_initialized )
        Initialize();
      
      return *m_document;
    }

    void Document::Write( bool writeAll ) const
    {
      static std::string xmlDecl = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";

      if( m_initialized )
      {
        // Write out the XML declaration
        m_stream << xmlDecl << std::endl;
        
        if( writeAll )
          m_document->toXml( m_stream, false, true );
        else
          // Serialize the GDML document with ignoring top-level empty tags
          m_document->toXml( m_stream, true, true );

        m_stream << std::endl;
        m_stream << std::flush;
      }
      else
      {
        throw std::logic_error( "Attempt to write non-initialized GDML document!" );
      }
    }

		void Document::setSchemaLocation( const std::string& url )
		{
			m_schemaURL = url;
			// Replace the existing location of the schema file
			m_document->addAttribute( "xsi:noNamespaceSchemaLocation" , m_schemaURL );
		}
  }
}
